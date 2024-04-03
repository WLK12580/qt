#include "widget.h"
#include "./ui_widget.h"
#include <QtSerialBus/QtSerialBus>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    serialPortPtr=new QSerialPort(this);
    displayLayout(this);
    connectFunc();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::displayLayout(QWidget* parent) {
    layout(parent);
    recvSerialPortData(parent);
    sendSerialPortData(parent);
}

void Widget::connectFunc() {
    connect(scanPortPub, &QPushButton::clicked, this, &Widget::scanPort);

    connect(openSerial,&QPushButton::clicked,this,&Widget::OpenSerial);

    connect(sendData,&QPushButton::clicked,this,&Widget::sendDataToSerialPort);

    connect(serialPortPtr,&QSerialPort::readyRead,this,&Widget::recvDataFromSerialPort);

    connect(clearSendDataBtn,&QPushButton::clicked,this,&Widget::clearSendDataFunc);

    connect(clearRecvDataBtn,&QPushButton::clicked,this,&Widget::clearRecvDataFunc);
}
void Widget::layout(QWidget* w) {
    GBox = new QGroupBox(w);
    GBox->setGeometry(QRect(20, 10, 200, 300));
    GLayout = new QGridLayout(GBox);

    QLabel* label = new QLabel(GBox);
    label->setText("serialPort:");
    label->resize(100, 30);
    label->setAlignment(Qt::AlignRight);

    serialPort = new QComboBox(GBox);
    serialPort->resize(100, 30);

    QLabel* baudRate = new QLabel(GBox);
    baudRate->setText("BaudRate");
    baudRate->resize(100, 30);
    baudRate->setAlignment(Qt::AlignRight);

    baudSpinbox = new QComboBox(GBox);
    baudSpinbox->resize(100, 30);
    QList<qint32> baudList=QSerialPortInfo::standardBaudRates();
    int baudListSize=baudList.size();
    // for(int i=0;i<baudListSize;i++){
    //     baudSpinbox->addItem(QString::number(baudList.at(i)), baudList.at(i));
    // }
    baudSpinbox->addItem("9600", 9600);
    QLabel* stopBit = new QLabel(GBox);
    stopBit->setText("StopBits:");
    stopBit->resize(100, 30);
    stopBit->setAlignment(Qt::AlignRight);

    stopBitComboBox = new QComboBox(GBox);
    stopBitComboBox->resize(100, 30);

    stopBitComboBox->addItem("1", 1);
    stopBitComboBox->addItem("1.5", 1.5);
    stopBitComboBox->addItem("2", 2);

    QLabel* dataBit = new QLabel(GBox);
    dataBit->setText("DataBits:");
    dataBit->resize(100, 30);
    dataBit->setAlignment(Qt::AlignRight);

    dataBitComboBox = new QComboBox(GBox);
    dataBitComboBox->resize(100, 30);

    dataBitComboBox->addItem("8", 8);
    dataBitComboBox->addItem("7", 7);
    dataBitComboBox->addItem("6", 6);
    dataBitComboBox->addItem("5", 5);

    QLabel* checkBit = new QLabel(GBox);
    checkBit->setText("CheckBit:");
    checkBit->resize(100, 30);
    checkBit->setAlignment(Qt::AlignRight);

    checkBitComboBox = new QComboBox(GBox);
    checkBitComboBox->resize(100, 30);
    checkBitComboBox->addItem("None", 0);
    checkBitComboBox->addItem("Even", 2);
    checkBitComboBox->addItem("odd", 3);
    checkBitComboBox->addItem("space", 4);
    checkBitComboBox->addItem("mark", 5);

    scanPortPub = new QPushButton(GBox);
    scanPortPub->setText("ScanPort");



    pilotLamp = new QLabel(GBox);
    pilotLamp->setStyleSheet(m_gray_SheetStyle);

    pilotLamp->setAlignment(Qt::AlignRight);

    openSerial = new QPushButton(GBox);
    openSerial->setText("OpenSerial");

    GLayout->addWidget(label, 0, 0);
    GLayout->addWidget(serialPort, 0, 1);
    GLayout->addWidget(baudRate, 1, 0);
    GLayout->addWidget(baudSpinbox, 1, 1);
    GLayout->addWidget(stopBit, 2, 0);
    GLayout->addWidget(stopBitComboBox, 2, 1);
    GLayout->addWidget(dataBit, 3, 0);
    GLayout->addWidget(dataBitComboBox, 3, 1);
    GLayout->addWidget(checkBit, 4, 0);
    GLayout->addWidget(checkBitComboBox, 4, 1);
    GLayout->addWidget(scanPortPub, 5, 1);
    GLayout->addWidget(pilotLamp, 6, 0);
    GLayout->addWidget(openSerial, 6, 1);

    GBox->setLayout(GLayout);
}

void Widget::recvSerialPortData(QWidget* parent) {
    QGroupBox* GpBox = new QGroupBox(parent);
    QGridLayout* GLayout = new QGridLayout(GpBox);
    GpBox->setGeometry(QRect(250, 10, 500, 300));

    plainEditRecv = new QPlainTextEdit(GpBox);
    clearRecvDataBtn = new QPushButton(GpBox);
    clearRecvDataBtn->setText("clearPutton");
    GLayout->addWidget(plainEditRecv, 0, 0);
    GLayout->addWidget(clearRecvDataBtn, 1, 0);
    GpBox->setLayout(GLayout);
}

void Widget::sendSerialPortData(QWidget* parent) {
    QGroupBox* GpBox = new QGroupBox(parent);
    QGridLayout* GLayout = new QGridLayout(GpBox);
    GpBox->setGeometry(QRect(20, 350, 730, 200));
    plainEditSend = new QPlainTextEdit(GpBox);
    GLayout->addWidget(plainEditSend, 0, 0, 1, 2);

    sendData = new QPushButton(GpBox);
    sendData->setText("SendData");

    clearSendDataBtn = new QPushButton(GpBox);
    clearSendDataBtn->setText("clearData");
    GLayout->addWidget(sendData, 1, 0, 1, 1);
    GLayout->addWidget(clearSendDataBtn, 1, 1, 1, 1);
    GpBox->setLayout(GLayout);
}

void Widget::scanPort() {
    serialPort->clear();
    QList<QSerialPortInfo> serialPortList = QSerialPortInfo::availablePorts();

    if (serialPortList.isEmpty()) {
        serialPort->addItem(QString("Empty"));
        pilotLamp->setStyleSheet(m_red_SheetStyle);
    }
    else {
        QList<QSerialPortInfo> strList=QSerialPortInfo::availablePorts();
        qDebug()<<"strListLen="<<strList.size();
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
           pilotLamp->setStyleSheet(m_yellow_SheetStyle);
           QSerialPort serialPortTemp;
           serialPortTemp.setPort(info);
           if(serialPortTemp.open(QIODevice::ReadWrite) or serialPortTemp.portName()==serialPortPtr->portName()){
               serialPort->addItem(info.portName());
               serialPortTemp.close();
           }
        }
        pilotLamp->setStyleSheet(m_green_SheetStyle);
    }
}
void Widget::setSerialPort(){

    serialPortPtr->setPortName(serialPort->currentText());
    serialPortPtr->setBaudRate(baudSpinbox->currentText().toULong());
    float stopBits=stopBitComboBox->currentText().toFloat();
    QSerialPort::StopBits stopBitsEnum;
    if(qAbs(stopBits-1)<=0.0001){
        stopBitsEnum=QSerialPort::StopBits::OneStop;
    }else if(qAbs(stopBits-1.5)<=0.0001){
        stopBitsEnum=QSerialPort::StopBits::OneAndHalfStop;
    }else if(qAbs(stopBits-2)<=0.0001){
        stopBitsEnum=QSerialPort::StopBits::TwoStop;
    }else{
        qDebug()<<"输出数据错误\n";
        return ;
    }
    qDebug()<<"stopBitsEnum="<<stopBitsEnum;
    serialPortPtr->setStopBits(stopBitsEnum);

    QSerialPort::DataBits dataBitEnum;
    if(dataBitComboBox->currentText().isEmpty()){
        dataBitEnum=QSerialPort::DataBits::Data8;
    } else{
        dataBitEnum=QSerialPort::DataBits(dataBitComboBox->currentText().toInt());
    }
    qDebug()<<"dataBit="<<dataBitEnum;;
    serialPortPtr->setDataBits(dataBitEnum);

    QSerialPort::Parity parity=QSerialPort::Parity(checkBitComboBox->currentData().toUInt());

    serialPortPtr->setParity(parity);
}
void Widget::OpenSerial(){

    if(serialPortPtr->isOpen()){
        serialPortPtr->close();
        openSerial->setText("CloseSerial");
        qDebug()<<"OpenSerial";
    }else{
        setSerialPort();
        serialPortPtr->open(QIODevice::ReadWrite);
        openSerial->setText("OpenSerial");
        qDebug()<<"关闭串口";
    }
}
void Widget::sendDataToSerialPort(){
    if(!serialPortPtr->isOpen()) return ;

    QString strData=plainEditSend->toPlainText();
    qDebug()<<"strData="<<strData;
    QStringList ListData=strData.split("\n");
    for(int i=0;i<ListData.size();i++){
        if(ListData[i].isEmpty()) continue;
        ListData[i]+="\r\n";
        qDebug()<<"ListData="<<ListData;
        plainEditSend->moveCursor(QTextCursor::MoveOperation::End);
        serialPortPtr->write(ListData[i].toLocal8Bit().data());
    }

}
void Widget::recvDataFromSerialPort(){
    QByteArray recvData=serialPortPtr->readAll();
    QTextCodec *codec = QTextCodec::codecForName("GBK");

    QString strData="";
    strData+=codec->toUnicode(recvData);

    plainEditRecv->setPlainText(strData);
    plainEditRecv->moveCursor(QTextCursor::End);
}
void Widget::clearSendDataFunc(){
    plainEditSend->clear();
}
void Widget::clearRecvDataFunc(){
    plainEditRecv->clear();
}
