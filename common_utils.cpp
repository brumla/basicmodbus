#include "common_utils.h"

int hexs2int(const QString& number) {
    bool ok;
    int val = number.toInt(&ok, 16);
    return val;
}

quint8 hexs2byte(const QString& number) {
    return (quint8) (hexs2int(number) & 0xFF);
}

quint16 hexs2word(const QString& number) {
    return (quint8) (hexs2int(number) & 0xFFFF);
}

quint8 lowQb(quint8 byte)
{
    quint8 cipher = byte & 0x0F;
    return (quint8) cipher < 0xA ? cipher + '0' : cipher + 'A' - 0xA;
}

quint8 highQb(quint8 byte)
{
    quint8 cipher = (byte & 0xF0) >> 4;
    return (quint8) cipher < 0xA ? cipher + '0' : cipher + 'A' - 0xA;
}
