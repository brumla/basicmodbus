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
