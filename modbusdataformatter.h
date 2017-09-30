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

#ifndef MODBUSDATAFORMATTER_H
#define MODBUSDATAFORMATTER_H

#include <QObject>
#include <QString>

enum class ModbusDataError {
    NO_ERROR,
    INVALID_ADDRESS_NUMBER,
    INVALID_FUNCTION_NUMBER,
    INVALID_START_ADDRESS_NUMBER,
    DATA_NOT_WORD_ALIGNED,
    INVALID_DATA_NUMBER,
    INPUT_DATA_NOT_BYTE
};

enum class ModbusProtocol {
    BINARY,
    ASCII
};

class ModbusDataFormatter
{
public:
    ModbusDataFormatter(ModbusProtocol protocol);
    ModbusDataError setOutputData(const QString& address,
                       const QString& function,
                       const QString& startAddress,
                       const QString& inputData);
    QByteArray calculateOutputData();

    // properties
    inline unsigned int crc() { return m_crc; }
private:
    quint8                  m_address;
    quint8                  m_function;
    quint16                 m_startAddress;
    QByteArray              m_data;
    unsigned int            m_crc;
    bool                    m_isValid;
    ModbusProtocol          m_protocol;
};

#endif // MODBUSDATAFORMATTER_H
