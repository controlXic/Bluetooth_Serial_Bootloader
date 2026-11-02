/********************************************************************************
** Form generated from reading UI file 'bt_bl_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BT_BL_INTERFACE_H
#define UI_BT_BL_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BT_BL_Interface
{
public:
    QWidget *centralWidget;
    QTextEdit *serialDataIn;
    QPushButton *clearData;
    QFrame *frame;
    QLabel *label;
    QPushButton *stSpBtl;
    QSpinBox *timeoutBtlSpinBox;
    QFrame *frame_2;
    QLabel *blStatus;
    QPushButton *scanBlDev;
    QPushButton *clrDev;
    QListWidget *macListView;
    QPushButton *connectDev;
    QLineEdit *passLineEdit;
    QPushButton *passButton;
    QFrame *frame_3;
    QComboBox *serialPortInfoListBox;
    QPushButton *refreshPorts;
    QLabel *portInfo;
    QPushButton *connectPort;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QMainWindow *BT_BL_Interface)
    {
        if (BT_BL_Interface->objectName().isEmpty())
            BT_BL_Interface->setObjectName(QStringLiteral("BT_BL_Interface"));
        BT_BL_Interface->resize(630, 321);
        centralWidget = new QWidget(BT_BL_Interface);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        serialDataIn = new QTextEdit(centralWidget);
        serialDataIn->setObjectName(QStringLiteral("serialDataIn"));
        serialDataIn->setGeometry(QRect(330, 40, 241, 261));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(8);
        serialDataIn->setFont(font);
        serialDataIn->setReadOnly(true);
        clearData = new QPushButton(centralWidget);
        clearData->setObjectName(QStringLiteral("clearData"));
        clearData->setGeometry(QRect(580, 280, 31, 21));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(20, 257, 291, 41));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 13, 101, 16));
        label->setStyleSheet(QStringLiteral(""));
        label->setFrameShape(QFrame::NoFrame);
        label->setAlignment(Qt::AlignCenter);
        stSpBtl = new QPushButton(frame);
        stSpBtl->setObjectName(QStringLiteral("stSpBtl"));
        stSpBtl->setGeometry(QRect(10, 10, 111, 21));
        stSpBtl->setCheckable(false);
        timeoutBtlSpinBox = new QSpinBox(frame);
        timeoutBtlSpinBox->setObjectName(QStringLiteral("timeoutBtlSpinBox"));
        timeoutBtlSpinBox->setGeometry(QRect(240, 10, 43, 22));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
        timeoutBtlSpinBox->setPalette(palette);
        timeoutBtlSpinBox->setFocusPolicy(Qt::NoFocus);
        timeoutBtlSpinBox->setContextMenuPolicy(Qt::NoContextMenu);
        timeoutBtlSpinBox->setFrame(true);
        timeoutBtlSpinBox->setReadOnly(false);
        timeoutBtlSpinBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        timeoutBtlSpinBox->setAccelerated(false);
        timeoutBtlSpinBox->setKeyboardTracking(true);
        timeoutBtlSpinBox->setProperty("showGroupSeparator", QVariant(false));
        timeoutBtlSpinBox->setMinimum(10);
        timeoutBtlSpinBox->setMaximum(90);
        timeoutBtlSpinBox->setSingleStep(10);
        timeoutBtlSpinBox->setValue(10);
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(20, 110, 291, 121));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Sunken);
        blStatus = new QLabel(frame_2);
        blStatus->setObjectName(QStringLiteral("blStatus"));
        blStatus->setGeometry(QRect(160, 40, 121, 16));
        blStatus->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));
        blStatus->setFrameShape(QFrame::Box);
        blStatus->setAlignment(Qt::AlignCenter);
        scanBlDev = new QPushButton(frame_2);
        scanBlDev->setObjectName(QStringLiteral("scanBlDev"));
        scanBlDev->setGeometry(QRect(160, 10, 80, 21));
        clrDev = new QPushButton(frame_2);
        clrDev->setObjectName(QStringLiteral("clrDev"));
        clrDev->setGeometry(QRect(250, 10, 31, 21));
        macListView = new QListWidget(frame_2);
        macListView->setObjectName(QStringLiteral("macListView"));
        macListView->setGeometry(QRect(10, 10, 131, 71));
        macListView->setFont(font);
        connectDev = new QPushButton(frame_2);
        connectDev->setObjectName(QStringLiteral("connectDev"));
        connectDev->setGeometry(QRect(160, 60, 121, 21));
        connectDev->setCheckable(true);
        passLineEdit = new QLineEdit(frame_2);
        passLineEdit->setObjectName(QStringLiteral("passLineEdit"));
        passLineEdit->setGeometry(QRect(10, 90, 131, 21));
        passLineEdit->setMaxLength(15);
        passButton = new QPushButton(frame_2);
        passButton->setObjectName(QStringLiteral("passButton"));
        passButton->setGeometry(QRect(160, 90, 121, 21));
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(20, 40, 291, 41));
        frame_3->setFrameShape(QFrame::Box);
        frame_3->setFrameShadow(QFrame::Sunken);
        serialPortInfoListBox = new QComboBox(frame_3);
        serialPortInfoListBox->setObjectName(QStringLiteral("serialPortInfoListBox"));
        serialPortInfoListBox->setGeometry(QRect(70, 10, 71, 22));
        refreshPorts = new QPushButton(frame_3);
        refreshPorts->setObjectName(QStringLiteral("refreshPorts"));
        refreshPorts->setGeometry(QRect(150, 10, 21, 21));
        portInfo = new QLabel(frame_3);
        portInfo->setObjectName(QStringLiteral("portInfo"));
        portInfo->setGeometry(QRect(10, 13, 61, 16));
        connectPort = new QPushButton(frame_3);
        connectPort->setObjectName(QStringLiteral("connectPort"));
        connectPort->setGeometry(QRect(179, 10, 101, 21));
        connectPort->setCheckable(true);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 240, 161, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 90, 131, 16));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 20, 241, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(330, 20, 91, 21));
        BT_BL_Interface->setCentralWidget(centralWidget);
        frame->raise();
        frame_2->raise();
        frame_3->raise();
        serialDataIn->raise();
        clearData->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();

        retranslateUi(BT_BL_Interface);

        QMetaObject::connectSlotsByName(BT_BL_Interface);
    } // setupUi

    void retranslateUi(QMainWindow *BT_BL_Interface)
    {
        BT_BL_Interface->setWindowTitle(QApplication::translate("BT_BL_Interface", "Control Xic. Bluetooth bootloader", Q_NULLPTR));
        clearData->setText(QApplication::translate("BT_BL_Interface", "Clr", Q_NULLPTR));
        label->setText(QApplication::translate("BT_BL_Interface", "Bootloader timeout", Q_NULLPTR));
        stSpBtl->setText(QApplication::translate("BT_BL_Interface", "START Bootloader", Q_NULLPTR));
        blStatus->setText(QApplication::translate("BT_BL_Interface", "BL Status", Q_NULLPTR));
        scanBlDev->setText(QApplication::translate("BT_BL_Interface", "Scan BL Dev", Q_NULLPTR));
        clrDev->setText(QApplication::translate("BT_BL_Interface", "Clr", Q_NULLPTR));
        connectDev->setText(QApplication::translate("BT_BL_Interface", "Connect Dev", Q_NULLPTR));
        passButton->setText(QApplication::translate("BT_BL_Interface", "Send Password", Q_NULLPTR));
        refreshPorts->setText(QApplication::translate("BT_BL_Interface", "R", Q_NULLPTR));
        portInfo->setText(QApplication::translate("BT_BL_Interface", "Serial Port:", Q_NULLPTR));
        connectPort->setText(QApplication::translate("BT_BL_Interface", "Connect", Q_NULLPTR));
        label_2->setText(QApplication::translate("BT_BL_Interface", "Start bootloader mode", Q_NULLPTR));
        label_3->setText(QApplication::translate("BT_BL_Interface", "Select  device to Flash", Q_NULLPTR));
        label_4->setText(QApplication::translate("BT_BL_Interface", "Connect to C_X_BL_BTL Flasher Router", Q_NULLPTR));
        label_5->setText(QApplication::translate("BT_BL_Interface", "Debug console", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BT_BL_Interface: public Ui_BT_BL_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BT_BL_INTERFACE_H
