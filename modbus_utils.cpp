///
/// \brief CRC calculation
/// \details ** warning ** this code was copied from the manual referenced below and is not part of the sources, the licence is unknown here!!!
///
/// \ref http://www.delta.com.tw/product/em/drive/ac_motor/download/manual/DELTA_IA-MDS_VFD-EL_UM_EN_20140522.pdf
/// \param data data as array
/// \param length of the array
/// \return ModBus CRC
///
unsigned int crc_chk(unsigned char* data, unsigned char length){
    int j;
    unsigned int reg_crc=0xFFFF;
    while(length--){
        reg_crc ^= *data++;
        for(j=0;j<8;j++){
            if(reg_crc & 0x01){ /* LSB(b0)=1 */
                reg_crc=(reg_crc>>1) ^ 0xA001;
            }else{
                reg_crc=reg_crc >>1;
            }
        }
    }
    return reg_crc;
}
// end of code with different licence
