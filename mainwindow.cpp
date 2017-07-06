/*
Basic MODBUS communication tool
Copyright (C) 2017 Martin Zúber

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QWidgetData>
#include <QObjectUserData>
#include <QThread>

#include <QDebug>

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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    initializePort();

    ui->teLog->setMaximumBlockCount(1024);

    info(tr("Port defaults OK"));

    connect(&port, SIGNAL(readyRead()), this, SLOT(on_serialPortReadyRead()));
    connect(&port, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(on_serialPortError(QSerialPort::SerialPortError)));

    QAction *actSendData = ui->mainToolBar->addAction(tr("Send data"));

    /*
     * Send data to selected port, the port is always closed and reopen with current settings
     */
    connect(actSendData, &QAction::triggered, [=]() {
        info("Sending data...");
        qDebug() << "Action triggered";
        bool ok;
        bool dataAreValid = true;

        if(!validator()) return;
        info("RTU MODE");

        // output port data
        QByteArray data;

        // add data entered as hexa numbers
        data.append(ui->leAddress1->text().toInt(&ok, 16)); dataAreValid &= ok;
        data.append(ui->leFunction->text().toInt(&ok, 16)); dataAreValid &= ok;

        // address is 1 WORD, needs to be stored byte per byte
        int startAddr = ui->leStartAddress->text().toInt(&ok, 16); dataAreValid &= ok;
        data.append(startAddr >> 8);
        data.append(startAddr & 0xFF);

        // data bytes are entered as hexa values, one value per line
        QStringList dataText = ui->teData->toPlainText().split("\n");
        qDebug() << dataText;

        for(const QString& it : dataText) {
            data.append(it.toInt(&ok, 16)); dataAreValid &= ok;
        }

        // validate data
        if(!ok) {
            QMessageBox::critical(this,
                                  tr("Data error"),
                                  tr("At least one field contains invalid data, please correct the values"),
                                  QMessageBox::Close);
            statusBar()->showMessage(tr("Input data are not valid"));
            return;
        }

        // calculate CRC
        unsigned int crc = crc_chk((unsigned char*) data.data(), data.count());
        info(tr("CRC: %1").arg(QString::number(crc, 16).rightJustified(4, '0')));

        // add CRC, LOW byte goes first
        data.append(crc & 0xFF);
        data.append(crc >> 8);

        // only output to UI
        QString crcText = QString::number(crc, 16).rightJustified(4, '0');
        ui->leCRC->setText(crcText);

        // show the data in log
        QString buff;
        for(unsigned char it: data) {
            buff.append(QString::number(it, 16).toUpper()).rightJustified(2, '0');
            buff.append(" ");
        }
        info(tr("Data: %1").arg(buff));

        // if the port is still open, close it first
        if(port.isOpen()) port.close();

        // if the port was closed, then send data
        if(!port.isOpen()) {
            // do the port setup according to user setup
            port.setPort(QSerialPortInfo(ui->cbPort->currentData().toString()));
            port.setBaudRate(ui->cbPortSpeed->currentData().toInt());
            port.setParity((QSerialPort::Parity) ui->cbParity->currentData().toInt());
            port.setStopBits((QSerialPort::StopBits) ui->cbStopBit->currentData().toInt());
            port.setDataBits((QSerialPort::DataBits) ui->cbDataBit->currentData().toInt());

            // show the settings in the log
            info(tr("Port: %1: %2,%3,%4,%5")
                 .arg(port.portName())
                 .arg(port.baudRate())
                 .arg(port.dataBits())
                 .arg(port.parity())
                 .arg(port.stopBits())
                 );

            // erase the read buffer before the data are send
            readBuffer.clear();

            // open the port, if the operation fails, show the message
            if(!port.open(QIODevice::ReadWrite)) {
                QMessageBox::critical(this,
                                      tr("Cannot open port"),
                                      tr("Error: %1").arg(port.errorString()),
                                      QMessageBox::Close);
                return;
            }

            QThread::msleep(100);

            // write data to the port
            info(tr("Writing data to the selected port..."));
            port.write(data.data(), data.count());
            info(tr("Data sent."));
            statusBar()->showMessage(tr("Data were send, waiting for response (if any)..."), 5000);
        }
    });
}

MainWindow::~MainWindow()
{
    if(port.isOpen()) {
        port.close();
    }
    delete ui;
}

void MainWindow::initializePort()
{
    /*
     * initialize port setup UI, simply clear existing values
     * and store new, the enums from Qt are used
     */
    ui->cbPort->clear();
    for(auto serialPort: QSerialPortInfo::availablePorts()) {
        ui->cbPort->addItem(tr("%1 (%2 %3 %4)")
                            .arg(serialPort.portName())
                            .arg(serialPort.description())
                            .arg(serialPort.serialNumber())
                            .arg(serialPort.productIdentifier())
                            ,
                            serialPort.portName());
    }

    ui->cbPortSpeed->clear();
    ui->cbPortSpeed->addItem(tr("1200"), QSerialPort::Baud1200);
    ui->cbPortSpeed->addItem(tr("2400"), QSerialPort::Baud2400);
    ui->cbPortSpeed->addItem(tr("4800"), QSerialPort::Baud4800);
    ui->cbPortSpeed->addItem(tr("9600"), QSerialPort::Baud9600);
    ui->cbPortSpeed->addItem(tr("19200"), QSerialPort::Baud19200);
    ui->cbPortSpeed->addItem(tr("38400"), QSerialPort::Baud38400);
    ui->cbPortSpeed->addItem(tr("57600"), QSerialPort::Baud57600);
    ui->cbPortSpeed->addItem(tr("115200"), QSerialPort::Baud115200);

    ui->cbPortSpeed->setCurrentIndex(3);

    ui->cbParity->clear();
    ui->cbParity->addItem(tr("None"), QSerialPort::NoParity);
    ui->cbParity->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->cbParity->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->cbParity->addItem(tr("Space"), QSerialPort::SpaceParity);
    ui->cbParity->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->cbParity->addItem(tr("Unknown"), QSerialPort::UnknownParity);

    ui->cbParity->setCurrentIndex(0);

    ui->cbDataBit->clear();
    ui->cbDataBit->addItem(tr("5"), QSerialPort::Data5);
    ui->cbDataBit->addItem(tr("6"), QSerialPort::Data6);
    ui->cbDataBit->addItem(tr("7"), QSerialPort::Data7);
    ui->cbDataBit->addItem(tr("8"), QSerialPort::Data8);

    ui->cbDataBit->setCurrentIndex(2);

    ui->cbStopBit->clear();
    ui->cbStopBit->addItem(tr("1 OneStop"), QSerialPort::OneStop);
    ui->cbStopBit->addItem(tr("1,5 OneAndHalfStop"), QSerialPort::OneAndHalfStop);
    ui->cbStopBit->addItem(tr("2 TwoStop"), QSerialPort::TwoStop);
    ui->cbStopBit->addItem(tr("? UnknownStopBits "), QSerialPort::UnknownStopBits);

    ui->cbStopBit->setCurrentIndex(2);

    statusBar()->showMessage(tr("Application initialized"), 5000);
}

bool MainWindow::validator()
{
    /*
     * GUI validations
     */
    info("Input data validation...");

    QString err;

    // address, function, start address are easy, just check the entered text length
    if (ui->leAddress1->text().length() != 2) err += tr("Address must have 2 digits!\n");
    if (ui->leFunction->text().length() != 2) err += tr("Function must have 2 digits!\n");
    if (ui->leStartAddress->text().length() != 4) err += tr("Start address must have 4 digits!\n");

    // data are stored as pairs, there must be always at least one WORD entered as two bytes
    if (ui->teData->blockCount() < 2) {
        err += tr("The output data must have 2 digit for read mode or 2+ digits for write mode!\n");
    }
    else {
        QStringList lst = ui->teData->toPlainText().split("\n");
        if(lst.size() % 2 != 0) err += tr("The number of send bytes must be even!\n");

        bool exceedLen = false;
        for(const QString& it: lst) {
            if(it.length() > 2) exceedLen = true;
        }

        if(exceedLen) err += tr("The length of the entered byte value must have 2 digits only!\n");
    }


    qDebug() << err;

    // show the message if there is any error and return false
    if(err.length() > 0) {
        QMessageBox::critical(this,
                              tr("Input data error"),
                              tr("Cannot send data to the device:\n\n%1").arg(err),
                              QMessageBox::Close);
        info(tr("Validace selhala"));
        return false;
    }
    statusBar()->showMessage(tr("Input data are valid"), 5000);
    return true;
}

void MainWindow::info(const QString &msg)
{
    ui->teLog->appendPlainText(tr("%1: %2")
                               .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss"))
                               .arg(msg)
                               );
}

void MainWindow::on_serialPortReadyRead()
{
    info(tr("Data received"));
    readBuffer.append(port.readAll());
    ui->teOutput->clear();

    for(unsigned char it : readBuffer) {
        ui->teOutput->appendPlainText(QString::number(it, 16).toUpper().rightJustified(2, '0'));
    }
}

void MainWindow::on_serialPortError(QSerialPort::SerialPortError err)
{
    if(err == QSerialPort::NoError) {
        info("No errors");
        return;
    }
    info(tr("Při přenosu dat došlo k chybě č. %1").arg(err));
    QString errMsg;
    switch(err) {
    case QSerialPort::DeviceNotFoundError: errMsg = tr("Device not found error"); break;
    case QSerialPort::PermissionError: errMsg = tr("An error occurred while attempting to open an already opened device by another process or a user not having enough permission and credentials to open."); break;
    case QSerialPort::OpenError: errMsg = tr("An error occurred while attempting to open an already opened device in this object."); break;
    case QSerialPort::NotOpenError: errMsg = tr("This error occurs when an operation is executed that can only be successfully performed if the device is open."); break;
    case QSerialPort::ParityError: errMsg = tr("Parity error detected by the hardware while reading data."); break;
    case QSerialPort::FramingError: errMsg = tr("Framing error detected by the hardware while reading data."); break;
    case QSerialPort::BreakConditionError: errMsg = tr("Break condition detected by the hardware on the input line."); break;
    case QSerialPort::WriteError: errMsg = tr("An I/O error occurred while writing the data."); break;
    case QSerialPort::ReadError: errMsg = tr("An I/O error occurred while reading the data."); break;
    case QSerialPort::ResourceError: errMsg = tr("An I/O error occurred when a resource becomes unavailable, e.g. when the device is unexpectedly removed from the system."); break;
    case QSerialPort::UnsupportedOperationError: errMsg = tr("The requested device operation is not supported or prohibited by the running operating system."); break;
    case QSerialPort::TimeoutError: errMsg = tr("A timeout error occurred."); break;
    case QSerialPort::UnknownError: errMsg = tr("An unidentified error occurred."); break;
    }
    QMessageBox::critical(this,
                          tr("Error"),
                          tr("Error code is %1:\n\n%2").arg(err).arg(errMsg),
                          QMessageBox::Close);
}

void MainWindow::on_action_Quit_triggered()
{
    close();
}

void MainWindow::on_action_about_triggered()
{
    QString licence;

    QFile f(":/lic/lgpl3");
    qDebug() << f.exists();
    if(f.open(QFile::ReadOnly | QFile::Text)) {
        licence = QString(f.readAll());
    }
    else {
        licence = tr("Base MODBUS communication tool\nCopyright (C) 2017 Martin Zúber.\nLicence: LGPL3");
    }
    f.close();

    QMessageBox::information(this,
                             tr("About"),
                             licence,
                             QMessageBox::Close);
}
