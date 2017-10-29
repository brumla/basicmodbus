/*
Basic MODBUS communication tool
Copyright (C) 2017 Martin Zúber

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "modbusdataformatter.h"
#include "modbus_utils.h"
#include "common_utils.h"

#include <QDebug>

ModbusDataFormatter::ModbusDataFormatter(ModbusProtocol protocol) :
    m_isValid(false),
    m_protocol(protocol)
{
}

ModbusDataError ModbusDataFormatter::setOutputData(const QString &address, const QString &function, const QString &startAddress, const QString &inputData)
{
    bool ok;
    m_address = address.toInt(&ok, 16);
    if(!ok) {
        return ModbusDataError::INVALID_ADDRESS_NUMBER;
    }

    m_function = function.toInt(&ok, 16);
    if(!ok) {
        return ModbusDataError::INVALID_FUNCTION_NUMBER;
    }

    m_startAddress = startAddress.toInt(&ok, 16);
    if(!ok) {
        return ModbusDataError::INVALID_START_ADDRESS_NUMBER;
    }

    // unpack the input data
    QStringList bytes = inputData.trimmed().split(QRegExp("[\n\r\t]+"), QString::SkipEmptyParts);
    qDebug() << "Bytes: " << bytes.size();
    if(bytes.size() % 2 != 0) {
        // only even count is allowed
        return ModbusDataError::DATA_NOT_WORD_ALIGNED;
    }

    m_data.clear();
    quint8 tempByte = 0;
    for(const QString& it : bytes ) {
        tempByte = it.toInt(&ok, 16);
        if(!ok) {
            return ModbusDataError::INVALID_DATA_NUMBER;
        }
        m_data.append((unsigned char) tempByte);
    }

    return ModbusDataError::NO_ERROR;
}

QByteArray ModbusDataFormatter::calculateOutputData()
{
    if(m_protocol == ModbusProtocol::BINARY) {
        QByteArray output;
        output.append(m_address);
        output.append(m_function);
        output.append(m_startAddress >> 8);
        output.append(m_startAddress & 0xFF);

        for(const unsigned char it : m_data) {
            output.append(it);
        }

        m_crc = crc_chk((unsigned char *) output.data(), output.count());
        output.append(m_crc & 0xFF);
        output.append(m_crc >> 8);

        return output;
    }
    if(m_protocol == ModbusProtocol::ASCII) {
        QByteArray output;
        output.append((char) 2);
        output.append(':');
        output.append(highQb(m_address));
        output.append(lowQb(m_address));
        output.append(highQb(m_function));
        output.append(lowQb(m_function));

        output.append(lowQb(m_startAddress >> 8));
        output.append(highQb(m_startAddress >> 8));
        output.append(lowQb(m_startAddress & 0xFF));
        output.append(highQb(m_startAddress & 0xFF));

        int lrc_sum = m_address + m_function + (m_startAddress >> 8) + (m_startAddress & 0xFF);

        for(const unsigned char it : m_data) {
            output.append(highQb(it));
            output.append(lowQb(it));
            lrc_sum += it;
        }

        int mod256 = 256 - (lrc_sum % 256);

        output.append(highQb(mod256));
        output.append(lowQb(mod256));

        output.append('\r');
        output.append('\n');
        return output;
    }
    return QByteArray();
}
