#ifndef IDATAFORMATTER_H
#define IDATAFORMATTER_H

#include <QByteArray>
#include <QtGlobal>
#include <QString>

///
/// \brief This is data formatter top abstract class
///
class IDataFormatter;
class IDataFormatter
{
public:
    /* Encode data */
    ///
    /// \brief add the address
    /// \param addr 1 byte address in range 0..254 (0 is broadcast)
    /// \return current instance of the data formatter
    ///
    virtual IDataFormatter* address(quint8 addr) = 0;

    ///
    /// \brief add the function code
    /// \param func function code (1 byte)
    /// \return
    ///
    virtual IDataFormatter* function(quint8 func) = 0;

    ///
    /// \brief write one word - the word is saved into the buffer
    /// \param highByte
    /// \param lowByte
    /// \return
    ///
    virtual IDataFormatter* write(quint8 highByte, quint8 lowByte) = 0;
    virtual IDataFormatter* write(quint16 word) = 0;

    ///
    /// \brief add the expected bytes which will be read from the bus (only for read operation)
    /// \param count count of the read bytes as word
    /// \return
    ///
    virtual IDataFormatter* readDataCount(quint16 count) = 0;

    virtual IDataFormatter* startAddress(quint8 highByte, quint8 lowByte) = 0;
    virtual IDataFormatter* startAddress(quint16 addr) = 0;

    virtual IDataFormatter* appendBytes(quint8 data) = 0;

    ///
    /// \brief build the datablock, data are available via dataToBeSend() function
    /// \return
    ///
    virtual IDataFormatter* build() = 0;

    ///
    /// \brief the data buffer contains complete block of dat to be send including CRC
    /// \return bytes to be send to the port, if there is any error, the returned value is empty and lastError is set
    ///
    virtual inline QByteArray dataToBeSend() { return m_dataToBeSend; }

    ///
    /// \brief Return last error if any. If no error was found, empty QString is returned
    ///
    inline QString lastError() {return m_lastError;}

protected:
    QByteArray              m_dataToBeSend;
    QByteArray              m_dataReceived;
    QString                 m_lastError;

private:
    void cleanError();
};

#endif // IDATAFORMATTER_H
