/*
 * This code is not under LGPL3. Please contact me if you are author of this code!
 */

#ifndef MODBUS_UTILS_H
#define MODBUS_UTILS_H

///
/// \brief calculates CRC for the MODBUS protocol
/// \param data input data as array of unsigned chars
/// \param length length of the array
/// \return
///
unsigned int crc_chk(unsigned char* data, unsigned char length);

#endif // MODBUS_UTILS_H
