#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <iostream>
#include <QProperty>
#include <QTextCodec>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void displayLayout(QWidget* parent = nullptr);
    void layout(QWidget* parent = nullptr);
    void recvSerialPortData(QWidget* parent = nullptr);
    void sendSerialPortData(QWidget* parent = nullptr);

    void connectFunc();

    void scanPort();
    void OpenSerial();
private:
    QGridLayout* GLayout = nullptr;
    QHBoxLayout* HLayout = nullptr;
    QGroupBox* GBox = nullptr;
    QComboBox* serialPort = nullptr;
    QPushButton* scanPortPub = nullptr;
    QComboBox* baudSpinbox=nullptr;
    QComboBox* stopBitComboBox=nullptr;
    QComboBox* dataBitComboBox=nullptr;
    QComboBox* checkBitComboBox=nullptr;
    QPushButton* openSerial=nullptr;
    QLabel* pilotLamp = nullptr;
    QPlainTextEdit* plainEditRecv=nullptr;
    QSerialPort *serialPortPtr=nullptr;
    QPushButton* sendData=nullptr;
    QPlainTextEdit* plainEditSend=nullptr;
    QPushButton* clearSendDataBtn=nullptr;
    QPushButton* clearRecvDataBtn=nullptr;

    const QString m_red_SheetStyle =
        "min-width: 20px; min-height: 20px;max-width:20px; max-height: 20px;border-radius: 10px; background:red";
    const QString m_green_SheetStyle =
        "min-width: 20px; min-height: 20px;max-width:20px; max-height: 20px;border-radius: 10px; ;background:green";
    const QString m_gray_SheetStyle =
        "min-width: 20px; min-height: 20px;max-width:20px; max-height: 20px;border-radius: 10px;  border:1px solid "
        "black;background:grey";
    const QString m_yellow_SheetStyle =
        "min-width: 20px; min-height: 20px;max-width:20px; max-height: 20px;border-radius: 10px;  border:1px solid "
        "black;background:yellow";


private:
    Ui::Widget *ui;
private:
    void qtSerialPortTest();
    void setSerialPort();
    void sendDataToSerialPort();
    void recvDataFromSerialPort();
    void clearSendDataFunc();
    void clearRecvDataFunc();
};
#endif // WIDGET_H
