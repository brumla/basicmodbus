#include "rtudataformatter.h"
#include "modbus_utils.h"

RTUDataFormatter::RTUDataFormatter()
{

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
    return this;
}
