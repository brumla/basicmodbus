#include "rtudataformatter.h"
#include "modbus_utils.h"

RTUDataFormatter::RTUDataFormatter()
{
    cleanError();
}

IDataFormatter *RTUDataFormatter::address(quint8 addr)
{
    m_address = addr;
    return this;
}

IDataFormatter *RTUDataFormatter::function(quint8 func)
{
    m_function = func;
    return this;
}

IDataFormatter *RTUDataFormatter::write(quint8 highByte, quint8 lowByte)
{
    m_dataBuffer.append(highByte, lowByte);
    return this;
}

IDataFormatter *RTUDataFormatter::write(quint16 word)
{
    return write(word >> 8, word & 0x00FF);
}

IDataFormatter *RTUDataFormatter::readDataCount(quint16 count)
{
    m_isReadOperation = true;
    m_dataCountHigh = count & 0xFF00 >> 8;
    m_dataCountLow = count & 0x00FF;

    return this;
}

IDataFormatter *RTUDataFormatter::appendBytes(quint8 data)
{
    m_temporaryBytes.append((unsigned char) data);

    return this;
}

IDataFormatter *RTUDataFormatter::startAddress(quint8 highByte, quint8 lowByte)
{
    m_startAddressHigh = highByte;
    m_startAddressLow = lowByte;
    return this;
}

IDataFormatter *RTUDataFormatter::startAddress(quint16 addr)
{
    return startAddress(addr >> 8, addr & 0xFF);
}

IDataFormatter *RTUDataFormatter::build()
{
    m_dataToBeSend.clear();
    m_dataToBeSend.append(m_address);
    m_dataToBeSend.append(m_function);
    m_dataToBeSend.append(m_startAddressLow);
    m_dataToBeSend.append(m_startAddressHigh);

    // add expected data count for read operation
    if(m_isReadOperation) {
        m_dataToBeSend.append(m_dataCountHigh);
        m_dataToBeSend.append(m_dataCountLow);
    }

    if(m_temporaryBytes.size() > ) {
        m_dataToBeSend.append(m_temporaryBytes);
    }

    unsigned int crc = crc_chk(m_dataToBeSend.data(), m_dataToBeSend.count());
    m_dataToBeSend.append(crc & 0xFF);
    m_dataToBeSend.append(crc >> 8);

    return this;
}
