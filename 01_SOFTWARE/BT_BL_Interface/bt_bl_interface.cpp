/*
 *
 * BT_BL_Dev mac(hex): 24:0A:C4:1D:55:96 -> { 0x24, 0x0A, 0xC4, 0x1D, 0x55, 0x96 }
 * Slave A4:CF:12:18:A2:AA
 * bl slave pass: sdf5431234h7r6G
 */


#include "bt_bl_interface.h"
#include "ui_bt_bl_interface.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>


// Device descriptor vars //
static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

// Bluetooth vars //
bool bl_connected = false;
bool serialPass = false;

////////////////////////////////////////////////////////////////////////////////////
// Setup Window
////////////////////////////////////////////////////////////////////////////////////
BT_BL_Interface::BT_BL_Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BT_BL_Interface),
    intValidator(new QIntValidator(0, 4000000, this))
{
    ui->setupUi(this);

    serial = new QSerialPort(this);

    setFixedSize(width(), height());
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    connect(ui->serialPortInfoListBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BT_BL_Interface::showPortInfo);
    connect(serial, &QSerialPort::readyRead, this, &BT_BL_Interface::on_read_data);

    fillPortsInfo();
    updateSettings();

    ui->connectDev->setEnabled(false);
    ui->scanBlDev->setEnabled(false);
    ui->clrDev->setEnabled(false);
    ui->macListView->setEnabled(false);
    ui->passLineEdit->setEnabled(false);
    ui->passButton->setEnabled(false);
    ui->stSpBtl->setEnabled(false);
    ui->timeoutBtlSpinBox->setEnabled(false);
    ui->clearData->setEnabled(false);
    ui->serialDataIn->setEnabled(false);

}

BT_BL_Interface::~BT_BL_Interface()
{
    delete ui;
}


////////////////////////////////////////////////////////////////////////////////////
// Serial Configuration
////////////////////////////////////////////////////////////////////////////////////
void BT_BL_Interface::fillPortsInfo()
{
    ui->serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        ui->serialPortInfoListBox->addItem(list.first(), list);
    }
}

void BT_BL_Interface::showPortInfo(int idx)
{
    if (idx == -1)
        return;

    ui->serialPortInfoListBox->itemData(idx).toStringList();

//    const QStringList list = ui->serialPortInfoListBox->itemData(idx).toStringList();
//    ui->descriptionLabel->setText(tr("Description: %1").arg(list.count() > 1 ? list.at(1) : tr(blankString)));
//    ui->manufacturerLabel->setText(tr("Manufacturer: %1").arg(list.count() > 2 ? list.at(2) : tr(blankString)));
//    ui->serialNumberLabel->setText(tr("Serial number: %1").arg(list.count() > 3 ? list.at(3) : tr(blankString)));
//    ui->locationLabel->setText(tr("Location: %1").arg(list.count() > 4 ? list.at(4) : tr(blankString)));
//    ui->vidLabel->setText(tr("Vendor Identifier: %1").arg(list.count() > 5 ? list.at(5) : tr(blankString)));
//    ui->pidLabel->setText(tr("Product Identifier: %1").arg(list.count() > 6 ? list.at(6) : tr(blankString)));
}

void BT_BL_Interface::updateSettings()
{
    currentSettings.name = ui->serialPortInfoListBox->currentText();
    currentSettings.baudRate = QSerialPort::Baud115200;
    currentSettings.dataBits = QSerialPort::Data8;
    currentSettings.parity = QSerialPort::EvenParity;
    currentSettings.stopBits = QSerialPort::OneStop;
    currentSettings.flowControl = QSerialPort::NoFlowControl;
}

void BT_BL_Interface::on_refreshPorts_clicked()
{
    fillPortsInfo();
    updateSettings();
}


////////////////////////////////////////////////////////////////////////////////////
// Serial Connection
////////////////////////////////////////////////////////////////////////////////////
void BT_BL_Interface::on_connectPort_clicked(bool checked)
{
    if(checked)
    {
        ui->connectPort->setText("Disconnect");
        updateSettings();

        qDebug() << "name: " << currentSettings.name;
        qDebug() << "baudRate: " << currentSettings.baudRate;
        qDebug() << "dataBits: " << currentSettings.dataBits;
        qDebug() << "parity: " << currentSettings.parity;
        qDebug() << "stopBits: " << currentSettings.stopBits;
        qDebug() << "flowControl: " << currentSettings.flowControl;

        serial->setPortName(currentSettings.name);
        serial->setBaudRate(currentSettings.baudRate);
        serial->setDataBits(currentSettings.dataBits);
        serial->setParity(currentSettings.parity);
        serial->setStopBits(currentSettings.stopBits);
        serial->setFlowControl(currentSettings.flowControl);

        if (serial->open(QIODevice::ReadWrite))
        {
            serial->write("connect_interface;");
            ui->serialPortInfoListBox->setEnabled(false);
            ui->refreshPorts->setEnabled(false);
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), serial->errorString());
            serial->close();
            ui->connectPort->setText("Connect");
            ui->connectPort->setChecked(false);
            ui->serialPortInfoListBox->setEnabled(true);
            ui->refreshPorts->setEnabled(true);
        }
    }
    else
    {
        if (serial->isOpen())
            serial->close();
        ui->connectPort->setText("Connect");
        ui->connectPort->setChecked(false);
        ui->serialPortInfoListBox->setEnabled(true);
        ui->refreshPorts->setEnabled(true);

        ui->scanBlDev->setEnabled(false);
        ui->clrDev->setEnabled(false);
        ui->connectDev->setEnabled(false);
        ui->passLineEdit->setEnabled(false);
        ui->passButton->setEnabled(false);
        ui->stSpBtl->setEnabled(false);
        ui->timeoutBtlSpinBox->setEnabled(false);
        ui->macListView->setEnabled(false);
        ui->clearData->setEnabled(false);
        ui->serialDataIn->setEnabled(false);
    }
}

////////////////////////////////////////////////////////////////////////////////////
// Serial Read & print on listwidget
////////////////////////////////////////////////////////////////////////////////////
void BT_BL_Interface::on_read_data()
{
    QByteArray data = serial->readAll();
    bool numOk;
//    qDebug() << "Rebut: " << data;
    data.mid(0, 1).toInt(&numOk, 10);

    // Comprova dev serial pass //
    if(data.contains("123gT88eert"))
    {
        serialPass = true;

        if(bl_connected == true)
        {
            ui->connectDev->setText("Disconnect Dev");
            ui->connectDev->setEnabled(true);
            ui->passLineEdit->setEnabled(false);
            ui->passButton->setEnabled(false);
            ui->scanBlDev->setEnabled(false);
            ui->macListView->setEnabled(false);
            ui->clrDev->setEnabled(false);

            ui->clearData->setEnabled(true);
            ui->serialDataIn->setEnabled(true);
            ui->stSpBtl->setEnabled(true);
            ui->timeoutBtlSpinBox->setEnabled(true);
        }
        else
        {
            ui->scanBlDev->setEnabled(true);
            ui->clrDev->setEnabled(true);
            ui->macListView->setEnabled(true);
            ui->connectDev->setEnabled(true);
            ui->passLineEdit->setEnabled(true);
            ui->passButton->setEnabled(true);
            ui->clearData->setEnabled(true);
            ui->serialDataIn->setEnabled(true);
        }

    }
    if(data.contains("Stop bootloader mode"))
    {
        // Printar a texEdit //
        ui->serialDataIn->append(data);
        ui->serialDataIn->append("Restart Serial Port\n\n");
    }
    if(serialPass == true)
    {
        //////////////////////////////
        // Accions al llegir serial //
        // NO printar serial //
        if(data.contains("Address: "))
        {
            ui->macListView->addItem(data.mid(data.indexOf("Address: ") + 9, 17).toUpper());
        }

        // BL Router <> Slave connected //
        else if(data.contains("Connected Successfully!"))
        {
            // Printar a texEdit //
            ui->serialDataIn->append(data);

            ui->blStatus->setStyleSheet("background-color: rgb(0, 255, 0)");

            ui->connectDev->setText("Disconnect Dev");
            ui->connectDev->setEnabled(true);
            ui->passLineEdit->setEnabled(false);
            ui->passButton->setEnabled(false);

            ui->stSpBtl->setEnabled(true);
            ui->timeoutBtlSpinBox->setEnabled(true);

            bl_connected = true;
        }
        // Desconnectar Router i Slave; //
        // No es pot connectar o pass incorrecte; //
        // Dispositiu desconectat o connexio perduda //
        else if(data.contains("Disconnect from: ") || data.contains("Device not connected") || data.contains("BL not connected."))
        {
            // Printar a texEdit //
            ui->serialDataIn->append(data);

            ui->blStatus->setStyleSheet("background-color: rgb(255, 0, 0)");
            ui->connectDev->setChecked(false);
            ui->connectDev->setText("Connect Dev");

            ui->connectDev->setEnabled(true);
            ui->scanBlDev->setEnabled(true);
            ui->macListView->setEnabled(true);
            ui->passLineEdit->setEnabled(true);
            ui->passButton->setEnabled(true);
            ui->clrDev->setEnabled(true);

            ui->clearData->setEnabled(true);
            ui->serialDataIn->setEnabled(true);

            ui->stSpBtl->setEnabled(false);
            ui->timeoutBtlSpinBox->setEnabled(false);

            bl_connected = false;
        }
        // Inicia BTL mode ok //
        else if(data.contains("Start bootloader mode."))
        {
            // Printar a texEdit //
            ui->serialDataIn->append(data);

            serial->write(ui->timeoutBtlSpinBox->text().toUtf8() + ";");
            QTimer::singleShot(300, this, SLOT(check_bootloader()));
        }
        // Printar info autoritzada //
        else if(    data.contains("Serial connected to cXic BL BTL")
                ||  data.contains("Device start!")
                ||  data.contains("Discover start.....")
                ||  data.contains("Scan devices.....")
                ||  data.contains("Connect to:")
                ||  data.contains("Enter BL password")
                ||  data.contains("Stop bootloader mode")
                ||  data.contains("bonded")
                ||  data.contains("Bonded"))

        {
            // Printar a texEdit //
            ui->serialDataIn->append(data);
        }
//        else
//        {
//            // Printar a texEdit //
//            ui->serialDataIn->append(data);
//        }
    }

}

void BT_BL_Interface::on_clearData_clicked()
{
    ui->serialDataIn->clear();
}

////////////////////////////////////////////////////////////////////////////////////
// Bluetooth scan, connect,...
////////////////////////////////////////////////////////////////////////////////////
void BT_BL_Interface::on_scanBlDev_clicked()
{
    ui->macListView->clear();
    serial->write("rest_before_discover;");
    ui->serialDataIn->append("Discover start.....");
    QTimer::singleShot(2000, this, SLOT(discover_devices()));
}

void BT_BL_Interface::discover_devices()
{
    serial->write("discover_blc_devices;");
}

void BT_BL_Interface::on_clrDev_clicked()
{
    ui->macListView->clear();
}

void BT_BL_Interface::on_connectDev_clicked(bool checked)
{
    if(checked)
    {
        if(ui->macListView->currentRow() >= 0  )
        {
                serial->write("connect_device;");

                ui->scanBlDev->setEnabled(false);
                ui->macListView->setEnabled(false);
                ui->clrDev->setEnabled(false);
                ui->connectDev->setEnabled(false);

                serial->write(ui->macListView->currentItem()->text().toUtf8() + ";");

//                qDebug() << "current row: " << ui->macListView->currentRow();
//                QString macAdd = ui->macListView->currentItem()->text();
//                qDebug() << "MAC address: " << macAdd;
//                qDebug() << "MAC nums: "    << macAdd.mid(0, 2).toUInt(NULL, 16)
//                                            << macAdd.mid(3, 2).toUInt(NULL, 16)
//                                            << macAdd.mid(6, 2).toUInt(NULL, 16)
//                                            << macAdd.mid(9, 2).toUInt(NULL, 16)
//                                            << macAdd.mid(12, 2).toUInt(NULL, 16)
//                                            << macAdd.mid(15, 2).toUInt(NULL, 16);
        }
        else
        {
            ui->connectDev->setChecked(false);
            ui->connectDev->setText("Connect Dev");
        }
    }
    else
    {
        serial->write("disconnect_device;");
        ui->connectDev->setText("Connect Dev");
        bl_connected = false;
    }
}

void BT_BL_Interface::on_passButton_clicked()
{
    // ESP32 pass: sdf546bverW1n
    serial->write(ui->passLineEdit->text().toUtf8() + ";");
}


////////////////////////////////////////////////////////////////////////////////////
// Start bootloader
////////////////////////////////////////////////////////////////////////////////////
void BT_BL_Interface::on_stSpBtl_clicked(/*bool checked*/)
{
     serial->write("start_bootloader;");
}

void BT_BL_Interface::check_bootloader()
{
    qDebug() << "putchar 0x7F";
    serial->putChar(0x7f);
    on_connectPort_clicked(false);
    serialPass = false;
}


////////////////////////////////////////////////////////////////////////////////////
// Reset Window status
////////////////////////////////////////////////////////////////////////////////////
void BT_BL_Interface::reset_window_status()
{
    ui->macListView->clear();
    ui->blStatus->setStyleSheet("background-color: rgb(255, 0, 0)");
    ui->connectDev->setChecked(false);
    ui->connectDev->setText("Connect Dev");
    ui->connectDev->setEnabled(true);
    ui->scanBlDev->setEnabled(true);
    ui->clrDev->setEnabled(true);
}






















