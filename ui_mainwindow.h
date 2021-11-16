/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Quit;
    QAction *action_about;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_5;
    QLineEdit *leAddress1;
    QPlainTextEdit *teData;
    QLabel *label_4;
    QLineEdit *leStartAddress;
    QLabel *label_2;
    QLineEdit *leFunction;
    QLabel *label_6;
    QLineEdit *leCRC;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QPlainTextEdit *teOutput;
    QLabel *label_7;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QLabel *label_12;
    QComboBox *comboBox;
    QComboBox *cbParity;
    QComboBox *cbPort;
    QComboBox *cbPortSpeed;
    QLabel *label;
    QComboBox *cbDataBit;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_8;
    QComboBox *cbStopBit;
    QPlainTextEdit *teLog;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(800, 611);
        MainWindow->setMinimumSize(QSize(800, 600));
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QStringLiteral("action_about"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1, Qt::AlignTop);

        leAddress1 = new QLineEdit(groupBox);
        leAddress1->setObjectName(QStringLiteral("leAddress1"));
        QFont font;
        font.setFamily(QStringLiteral("Courier"));
        leAddress1->setFont(font);
        leAddress1->setMaxLength(32767);

        gridLayout->addWidget(leAddress1, 0, 1, 1, 1);

        teData = new QPlainTextEdit(groupBox);
        teData->setObjectName(QStringLiteral("teData"));
        teData->setFont(font);

        gridLayout->addWidget(teData, 3, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        leStartAddress = new QLineEdit(groupBox);
        leStartAddress->setObjectName(QStringLiteral("leStartAddress"));
        leStartAddress->setFont(font);
        leStartAddress->setMaxLength(4);

        gridLayout->addWidget(leStartAddress, 2, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        leFunction = new QLineEdit(groupBox);
        leFunction->setObjectName(QStringLiteral("leFunction"));
        leFunction->setFont(font);
        leFunction->setMaxLength(2);

        gridLayout->addWidget(leFunction, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        leCRC = new QLineEdit(groupBox);
        leCRC->setObjectName(QStringLiteral("leCRC"));
        leCRC->setEnabled(false);
        leCRC->setFont(font);
        leCRC->setMaxLength(4);

        gridLayout->addWidget(leCRC, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 2);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        teOutput = new QPlainTextEdit(groupBox_2);
        teOutput->setObjectName(QStringLiteral("teOutput"));
        teOutput->setFont(font);
        teOutput->setReadOnly(true);

        gridLayout_3->addWidget(teOutput, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1, Qt::AlignTop);


        horizontalLayout->addWidget(groupBox_2);


        gridLayout_2->addLayout(horizontalLayout, 3, 0, 1, 2);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_4->addWidget(label_12, 6, 0, 1, 1);

        comboBox = new QComboBox(groupBox_3);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(comboBox, 6, 1, 1, 1);

        cbParity = new QComboBox(groupBox_3);
        cbParity->setObjectName(QStringLiteral("cbParity"));
        sizePolicy.setHeightForWidth(cbParity->sizePolicy().hasHeightForWidth());
        cbParity->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(cbParity, 4, 1, 1, 1);

        cbPort = new QComboBox(groupBox_3);
        cbPort->setObjectName(QStringLiteral("cbPort"));
        sizePolicy.setHeightForWidth(cbPort->sizePolicy().hasHeightForWidth());
        cbPort->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(cbPort, 1, 1, 1, 1);

        cbPortSpeed = new QComboBox(groupBox_3);
        cbPortSpeed->setObjectName(QStringLiteral("cbPortSpeed"));
        sizePolicy.setHeightForWidth(cbPortSpeed->sizePolicy().hasHeightForWidth());
        cbPortSpeed->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(cbPortSpeed, 2, 1, 1, 1);

        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 1, 0, 1, 1);

        cbDataBit = new QComboBox(groupBox_3);
        cbDataBit->setObjectName(QStringLiteral("cbDataBit"));
        sizePolicy.setHeightForWidth(cbDataBit->sizePolicy().hasHeightForWidth());
        cbDataBit->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(cbDataBit, 3, 1, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_4->addWidget(label_9, 3, 0, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_4->addWidget(label_10, 4, 0, 1, 1);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 5, 0, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_4->addWidget(label_8, 2, 0, 1, 1);

        cbStopBit = new QComboBox(groupBox_3);
        cbStopBit->setObjectName(QStringLiteral("cbStopBit"));
        sizePolicy.setHeightForWidth(cbStopBit->sizePolicy().hasHeightForWidth());
        cbStopBit->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(cbStopBit, 5, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_3, 0, 0, 1, 2);

        teLog = new QPlainTextEdit(centralWidget);
        teLog->setObjectName(QStringLiteral("teLog"));
        teLog->setFont(font);
        teLog->setReadOnly(true);

        gridLayout_2->addWidget(teLog, 4, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_help = new QMenu(menuBar);
        menu_help->setObjectName(QStringLiteral("menu_help"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(cbPort, cbPortSpeed);
        QWidget::setTabOrder(cbPortSpeed, cbDataBit);
        QWidget::setTabOrder(cbDataBit, cbParity);
        QWidget::setTabOrder(cbParity, cbStopBit);
        QWidget::setTabOrder(cbStopBit, comboBox);
        QWidget::setTabOrder(comboBox, leAddress1);
        QWidget::setTabOrder(leAddress1, leFunction);
        QWidget::setTabOrder(leFunction, leStartAddress);
        QWidget::setTabOrder(leStartAddress, teData);
        QWidget::setTabOrder(teData, leCRC);
        QWidget::setTabOrder(leCRC, teOutput);
        QWidget::setTabOrder(teOutput, teLog);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_help->menuAction());
        menu_File->addAction(action_Quit);
        menu_help->addAction(action_about);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Basic MODBUS communication tool", Q_NULLPTR));
        action_Quit->setText(QApplication::translate("MainWindow", "&Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_Quit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_about->setText(QApplication::translate("MainWindow", "&About", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Input data (HEX)", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Function:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Data separated by new line:", Q_NULLPTR));
        leAddress1->setInputMask(QString());
        leAddress1->setPlaceholderText(QApplication::translate("MainWindow", "Two hexa digits (2A, 0F...)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        teData->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Data se zad\303\241vaj\303\255 jako byte v hexa (0A, 5F) odd\304\233len\303\251 enterem. Pro re\305\276im \304\215ten\303\255 se zad\303\241vaj\303\255 pouze dva byte (prvn\303\255 HIGH, druh\303\275 LOW) s o\304\215ek\303\241van\303\275m po\304\215tem p\305\231ijat\303\275ch byte nap\305\231.:</p><p><span style=\" font-weight:600;\">00</span></p><p><span style=\" font-weight:600;\">02</span></p><p>pro p\305\231ijet\303\251 2 byte. Maxim\303\241ln\303\255 po\304\215et byte je 20 slov, tj. 40 byte, v re\305\276imu z\303\241pisu na za\305\231\303\255zen\303\255.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        teData->setPlaceholderText(QApplication::translate("MainWindow", "See the tooltip for help", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Start address:", Q_NULLPTR));
        leStartAddress->setPlaceholderText(QApplication::translate("MainWindow", "Four hexa digits (2A0F...)", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Address:", Q_NULLPTR));
        leFunction->setPlaceholderText(QApplication::translate("MainWindow", "Two hexa digits (2A, 0F...)", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "CRC/LRC:", Q_NULLPTR));
        leCRC->setText(QString());
        leCRC->setPlaceholderText(QString());
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Output data (HEX)", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Received data:", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Communication port", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Transfer mode:", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "RTU", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ASCII", Q_NULLPTR)
        );
        label->setText(QApplication::translate("MainWindow", "Port:", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Data bits:", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Parity:", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Stop bit:", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Speed:", Q_NULLPTR));
        teLog->setPlainText(QString());
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", Q_NULLPTR));
        menu_help->setTitle(QApplication::translate("MainWindow", "&Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
