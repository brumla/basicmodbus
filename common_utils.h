#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

#include <QtGlobal>
#include <QString>

///
/// \brief converts hexadecimal number stored as string to integer, use for the data exchange from GUI
/// \param number as hexadecimal string, only digits 0-9A-F are allowed
/// \return converted number as integer
///
int hexs2int(const QString& number);

///
/// \brief converts hexadecimal number stored as string to byte, use for the data exchange from GUI
/// \param number as hexadecimal string, only digits 0-9A-F are allowed
/// \return converted number as byte
///
quint8 hexs2byte(const QString& number);

/// \brief converts hexadecimal number stored as string to word, use for the data exchange from GUI
/// \param number as hexadecimal string, only digits 0-9A-F are allowed
/// \return converted number as word
quint16 hexs2word(const QString& number);

quint8 lowQb(quint8 byte);

quint8 highQb(quint8 byte);

#endif // COMMON_UTILS_H
