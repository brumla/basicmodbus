#ifndef RTUDATAFORMATTER_H
#define RTUDATAFORMATTER_H

#include "idataformatter.h"

class RTUDataFormatter : public IDataFormatter
{
public:
    RTUDataFormatter();

    // IDataFormatter interface
    IDataFormatter *address(quint8 addr);
    IDataFormatter *function(quint8 func);
    IDataFormatter *write(quint8 highByte, quint8 lowByte);
    IDataFormatter *write(quint16 word);
    IDataFormatter *readDataCount(quint16 count);
    IDataFormatter *startAddress(quint8 highByte, quint8 lowByte);
    IDataFormatter *startAddress(quint16 addr);
    IDataFormatter *build();
private:
    quint8              m_address;
    quint8              m_function;
    quint16             m_dataCountHigh;
    quint16             m_dataCountLow;
    QByteArray          m_dataBuffer;
    quint16             m_startAddressLow;
    quint16             m_startAddressHigh;
    bool                m_isReadOperation = false;
};

#endif // RTUDATAFORMATTER_H
