#ifndef BT_BL_INTERFACE_H
#define BT_BL_INTERFACE_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

class QIntValidator;

namespace Ui {
class BT_BL_Interface;
}

class BT_BL_Interface : public QMainWindow
{
    Q_OBJECT

public:

    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    explicit BT_BL_Interface(QWidget *parent = nullptr);
    ~BT_BL_Interface();

    Settings settings() const;

private:
    Ui::BT_BL_Interface *ui;

    void fillPortsInfo();
    void updateSettings();

    QIntValidator *intValidator;
    Settings currentSettings;

    QSerialPort *serial;

private slots:
    void showPortInfo(int idx);
    void on_refreshPorts_clicked();
    void on_connectPort_clicked(bool checked);
    void on_read_data();
    void on_clearData_clicked();
    void on_scanBlDev_clicked();
    void discover_devices();
    void on_clrDev_clicked();
    void on_connectDev_clicked(bool checked);
    void on_stSpBtl_clicked();
    void check_bootloader();
    void reset_window_status();
    void on_passButton_clicked();
};

#endif // BT_BL_INTERFACE_H
