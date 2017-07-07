#ifndef IDATAFORMATTER_H
#define IDATAFORMATTER_H

#include <QtGlobal>

///
/// \brief This is data formatter top abstract class
///
class IDataFormatter
{
public:
    IDataFormatter();

    /* Encode data */
    ///
    /// \brief add the address
    /// \param addr 1 byte address in range 0..254 (0 is broadcast)
    /// \return current instance of the data formatter
    ///
    virtual IDataFormatter address(quint8 addr) = 0;

    ///
    /// \brief add the function code
    /// \param func function code (1 byte)
    /// \return
    ///
    virtual IDataFormatter function(quint8 func) = 0;

    ///
    /// \brief write one word - the word is saved into the buffer
    /// \param highByte
    /// \param lowByte
    /// \return
    ///
    virtual IDataFormatter write(quint8 highByte, quint8 lowByte) = 0;

    ///
    /// \brief add the expected bytes which will be read from the bus (only for read operation)
    /// \param count count of the read bytes as word
    /// \return
    ///
    virtual IDataFormatter readDataCount(quint16 count) = 0;

    ///
    /// \brief build the datablock, data are available via dataToBeSend() function
    /// \return
    ///
    virtual IDataFormatter build() = 0;

    ///
    /// \brief the data buffer contains complete block of dat to be send including CRC
    /// \return
    ///
    virtual inline QByteArray dataToBeSend() { return m_dataToBeSend; }

private:
    QByteArray              m_dataToBeSend;
    QByteArray              m_dataToBeWritten;
};

#endif // IDATAFORMATTER_H
