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
#include <QThread>
#include <QAction>
#include <QFile>
#include <QChar>

#include <QDebug>

#include "modbus_utils.h"
#include "modbusdataformatter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializePort();

    ui->teLog->setMaximumBlockCount(1024);

    connect(&port, SIGNAL(readyRead()), this, SLOT(on_serialPortReadyRead()));
    connect(&port, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(on_serialPortError(QSerialPort::SerialPortError)));

    actSendData = ui->mainToolBar->addAction(tr("Send data"));
    closePort = ui->mainToolBar->addAction(tr("Close port"));

    actSendData->setEnabled(false);
    //closePort->setEnabled(false);

    connect(closePort, &QAction::triggered, [=]() {
        if(port.isOpen()) {
            port.close();
            statusBar()->showMessage(tr("Port closed"), 4000);
        }
    });

    /*
     * Send data to selected port, the port is always closed and reopen with current settings
     */
    connect(actSendData, &QAction::triggered, [=]() {
        info("Sending data...");
        qDebug() << "Action triggered";
        bool ok;

        QByteArray data = prepareData(&ok);
        if(!ok) return;

        qDebug() << "Sending data to selected port, data size=" << data.size();
        sendDataToPort(data);
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
    bool hasPorts = false;
    ui->comboBox->setEnabled(true);

    for(auto serialPort: QSerialPortInfo::availablePorts()) {
        ui->cbPort->addItem(tr("%1 (%2 %3 %4)")
                            .arg(serialPort.portName())
                            .arg(serialPort.description())
                            .arg(serialPort.serialNumber())
                            .arg(serialPort.productIdentifier())
                            ,
                            serialPort.portName());
        hasPorts = true;
    }

    if(!hasPorts) {
        info(tr("No ports available"));
        ui->cbPortSpeed->setEnabled(false);
        ui->cbParity->setEnabled(false);
        ui->cbDataBit->setEnabled(false);
        ui->cbStopBit->setEnabled(false);
        ui->comboBox->setEnabled(false);
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

    ui->cbStopBit->setCurrentIndex(2);

    statusBar()->showMessage(tr("Application initialized"), 5000);
}

void MainWindow::info(const QString &msg)
{
    ui->teLog->appendPlainText(tr("%1: %2")
                               .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss"))
                               .arg(msg)
                               );
}

QByteArray MainWindow::prepareData(bool *isOk) {
    ModbusProtocol protocol = ui->comboBox->currentText() == "RTU" ? ModbusProtocol::BINARY : ModbusProtocol::ASCII;

    ModbusDataFormatter formatter(protocol);
    ModbusDataError result = formatter.setOutputData(ui->leAddress1->text(),
                                                     ui->leFunction->text(),
                                                     ui->leStartAddress->text(),
                                                     ui->teData->toPlainText());
    if(result != ModbusDataError::NO_ERROR) {
        QString err;

        switch (result) {
        case ModbusDataError::DATA_NOT_WORD_ALIGNED:
            err = tr("Output data are not WORD aligned (2 BYTES per WORD)");
            break;
        case ModbusDataError::INPUT_DATA_NOT_BYTE:
            err = tr("Input data are not bytes separated by CR, CRLF or TAB");
            break;
        case ModbusDataError::INVALID_ADDRESS_NUMBER:
            err = tr("Address number is invalid");
            break;
        case ModbusDataError::INVALID_DATA_NUMBER:
            err = tr("Entered data bytes are not valid hexa numbers");
            break;
        case ModbusDataError::INVALID_FUNCTION_NUMBER:
            err = tr("Function number is invalid");
            break;
        case ModbusDataError::INVALID_START_ADDRESS_NUMBER:
            err = tr("Start address is invalid");
            break;
        default:
            break;
        }

        QMessageBox::critical(this,
                              tr("Error"),
                              err);
        *isOk = false;
        return QByteArray();
    }

    *isOk = true;
    QByteArray outputData = formatter.calculateOutputData();
    ui->leCRC->clear();
    if(protocol == ModbusProtocol::BINARY) {
        unsigned int crc = formatter.crc();
        ui->leCRC->setText(QString::number(crc, 16).rightJustified(4, '0'));
    }
    else {
        ui->leCRC->setText(QString(outputData).trimmed().right(2));
    }

    // show the data output in console for RTU and ASCII as bytes
    QString bytesResult = tr("Bytes: ");
    for(char it : outputData) {
        bytesResult.append(QString::number(uchar(it), 16).rightJustified(2, '0'));
        bytesResult.append(" ");
    }
    info(bytesResult);

    // if the protocol is ASCII then show the ASCII output
    bytesResult.clear();
    if(protocol == ModbusProtocol::ASCII) {
        bytesResult.append("ASCII: ");
        for(unsigned char it : outputData) {
            // handle the whitechars correctly
            switch(uchar(it)) {
            case 13:
                bytesResult.append("CR");
                break;
            case 10:
                bytesResult.append("LF");
                break;
            default:
                bytesResult.append(QChar(it));
            }
            bytesResult.append(",");
        }
    }
    info(bytesResult);

    return outputData;
}

void MainWindow::sendDataToPort(const QByteArray &data)
{
    // if the port is still open, close it first
    if(port.isOpen()) port.close();

    // if the port was closed, then send data
    if(!port.isOpen()) {
        // do the port setup according to user setup
        port.setPort(QSerialPortInfo(ui->cbPort->currentData().toString()));
        port.setBaudRate(ui->cbPortSpeed->currentData().toInt());
        port.setParity(static_cast<QSerialPort::Parity>(ui->cbParity->currentData().toInt()));
        port.setStopBits(static_cast<QSerialPort::StopBits>(ui->cbStopBit->currentData().toInt()));
        port.setDataBits(static_cast<QSerialPort::DataBits>(ui->cbDataBit->currentData().toInt()));

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

        // sleep for 100 ms to be sure the bus is ready
        QThread::msleep(100);

        // write data to the port
        info(tr("Writing data to the selected port..."));
        port.write(data.data(), data.count());
        info(tr("Data sent."));
        statusBar()->showMessage(tr("Data were sent, waiting for response (if any)..."), 5000);
    }
}

void MainWindow::on_serialPortReadyRead()
{
    info(tr("Data received"));
    readBuffer.append(port.readAll());
    ui->teOutput->clear();

    QString num;
    QString buff;
    for(char it : readBuffer) {
        num = QString::number(uchar(it), 16).toUpper().rightJustified(2, '0');
        ui->teOutput->appendPlainText(num);
        buff.append(num);
        buff.append(" ");
    }

    info(tr("Data received from MODBUS: %1").arg(buff));
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
    case QSerialPort::WriteError: errMsg = tr("An I/O error occurred while writing the data."); break;
    case QSerialPort::ReadError: errMsg = tr("An I/O error occurred while reading the data."); break;
    case QSerialPort::ResourceError: errMsg = tr("An I/O error occurred when a resource becomes unavailable, e.g. when the device is unexpectedly removed from the system."); break;
    case QSerialPort::UnsupportedOperationError: errMsg = tr("The requested device operation is not supported or prohibited by the running operating system."); break;
    case QSerialPort::TimeoutError: errMsg = tr("A timeout error occurred."); break;
    case QSerialPort::UnknownError: errMsg = tr("An unidentified error occurred."); break;
    case QSerialPort::NoError: break;
        //    case QSerialPort::ParityError: errMsg = tr("Parity error."); break;
        //    case QSerialPort::FramingError: errMsg = tr("Framing error"); break;
        //    case QSerialPort::BreakConditionError: errMsg = tr("Break condition error"); break;
    default: errMsg = tr("Unknown error");
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
        licence = tr("Base MODBUS communication tool\nCopyright (C) 2017-2021 Martin Zúber.\nLicence: LGPL3");
    }
    f.close();

    QMessageBox::information(this,
                             tr("About"),
                             QString("%1\nQt Version: %2")
                             .arg(licence)
                             .arg(QT_VERSION_STR),
                             QMessageBox::Close);
}

void MainWindow::on_cbPort_currentIndexChanged(int index)
{
    actSendData->setEnabled(false);

    if(index >= 0) {
        QString portNumber = ui->cbPort->currentData().toString();
        qDebug() << "Selected port name: " << portNumber;

        if(portNumber.length() > 0) {
            actSendData->setEnabled(true);
        }
    }
}

