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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    ///
    /// \brief receives data when the data are ready in port buffer
    ///
    void on_serialPortReadyRead();

    ///
    /// \brief executed when any communication error is raised
    /// \param err
    ///
    void on_serialPortError(QSerialPort::SerialPortError err);

    ///
    /// \brief close the application
    ///
    void on_action_Quit_triggered();

    ///
    /// \brief shows the About screen
    ///
    void on_action_about_triggered();

private:
    Ui::MainWindow *ui;

    // serial port instance
    QSerialPort port;

    // buffer for incoming data
    QByteArray readBuffer;

    ///
    /// \brief Initialize list of ports and all the parameters in comboboxes
    ///
    void initializePort();

    ///
    /// \brief add new informative message into the log
    /// \param msg message
    ///
    void info(const QString& msg);

    ///
    /// \brief prepare data which will be send to the selected port
    /// \param ok
    /// \return
    /// \todo Remove business logic, use one of the IDataFormatter implementation
    QByteArray prepareData(bool *isOk);

    ///
    /// \brief send the data to the port
    /// \param data
    ///
    void sendDataToPort(const QByteArray& data);
};

#endif // MAINWINDOW_H
