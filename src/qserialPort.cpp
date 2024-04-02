#include "qserialPort.h"

qserialPort::qserialPort(QWidget *parent) : QMainWindow(parent), ui(new Ui_qserialPort) {
  ui->setupUi(this);
  displayLayout(this);
  connectFunc();
}

qserialPort::~qserialPort() { delete ui; }
void qserialPort::displayLayout(QWidget *parent) {
  layout(parent);
  recvSerialPortData(parent);
  sendSerialPortData(parent);
}

void qserialPort::connectFunc(){
    connect(scanPortPub,&QPushButton::clicked,this,&qserialPort::scanPort);
}
void qserialPort::layout(QWidget *w) {
  GBox = new QGroupBox(w);
  GBox->setGeometry(QRect(20, 10, 200, 300));
  GLayout = new QGridLayout(GBox);

  QLabel *label = new QLabel(GBox);
  label->setText("serialPort:");
  label->resize(100, 30);
  label->setAlignment(Qt::AlignRight);

  serialPort = new QComboBox(GBox);
  serialPort->resize(100, 30);

  QLabel *baudRate = new QLabel(GBox);
  baudRate->setText("BaudRate");
  baudRate->resize(100, 30);
  baudRate->setAlignment(Qt::AlignRight);

  QComboBox *baudSpinbox = new QComboBox(GBox);
  baudSpinbox->resize(100, 30);
  baudSpinbox->addItem("4800", 4800);
  baudSpinbox->addItem("9600", 9600);
  baudSpinbox->addItem("19200", 19200);

  QLabel *stopBit = new QLabel(GBox);
  stopBit->setText("StopBits:");
  stopBit->resize(100, 30);
  stopBit->setAlignment(Qt::AlignRight);

  QComboBox *stopBitComboBox = new QComboBox(GBox);
  stopBitComboBox->resize(100, 30);

  stopBitComboBox->addItem("1", 1);
  stopBitComboBox->addItem("1.5", 1.5);
  stopBitComboBox->addItem("2", 2);

  QLabel *dataBit = new QLabel(GBox);
  dataBit->setText("DataBits:");
  dataBit->resize(100, 30);
  dataBit->setAlignment(Qt::AlignRight);

  QComboBox *dataBitComboBox = new QComboBox(GBox);
  dataBitComboBox->resize(100, 30);

  dataBitComboBox->addItem("8", 8);
  dataBitComboBox->addItem("7", 7);
  dataBitComboBox->addItem("6", 6);
  dataBitComboBox->addItem("5", 5);

  QLabel *checkBit = new QLabel(GBox);
  checkBit->setText("CheckBit:");
  checkBit->resize(100, 30);
  checkBit->setAlignment(Qt::AlignRight);

  QComboBox *checkBitComboBox = new QComboBox(GBox);
  checkBitComboBox->resize(100, 30);
  checkBitComboBox->addItem("None", "None");
  checkBitComboBox->addItem("Even", "Even");
  checkBitComboBox->addItem("odd", "odd");
  checkBitComboBox->addItem("space", "space");
  checkBitComboBox->addItem("mark", "mark");

  scanPortPub = new QPushButton(GBox);
  scanPortPub->setText("ScanPort");



  pilotLamp = new QLabel(GBox);
//   pilotLamp->setStyleSheet(m_gray_SheetStyle);
  pilotLamp->setStyleSheet(m_yellow_SheetStyle);
  pilotLamp->setAlignment(Qt::AlignRight);

  QPushButton *openSerial = new QPushButton(GBox);
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

void qserialPort::recvSerialPortData(QWidget *parent) {
  QGroupBox *GpBox = new QGroupBox(parent);
  QGridLayout *GLayout = new QGridLayout(GpBox);
  GpBox->setGeometry(QRect(250, 10, 500, 300));

  QPlainTextEdit *plainEdit = new QPlainTextEdit(GpBox);
  QPushButton *clearPub = new QPushButton(GpBox);
  clearPub->setText("clearPutton");
  GLayout->addWidget(plainEdit, 0, 0);
  GLayout->addWidget(clearPub, 1, 0);
  GpBox->setLayout(GLayout);
}

void qserialPort::sendSerialPortData(QWidget *parent) {
  QGroupBox *GpBox = new QGroupBox(parent);
  QGridLayout *GLayout = new QGridLayout(GpBox);
  GpBox->setGeometry(QRect(20, 350, 730, 200));
  QPlainTextEdit *plainEdit = new QPlainTextEdit(GpBox);
  GLayout->addWidget(plainEdit, 0, 0, 1, 2);

  QPushButton *sendData = new QPushButton(GpBox);
  sendData->setText("SendData");

  QPushButton *clearSendedData = new QPushButton(GpBox);
  clearSendedData->setText("clearData");
  GLayout->addWidget(sendData, 1, 0, 1, 1);
  GLayout->addWidget(clearSendedData, 1, 1, 1, 1);
  GpBox->setLayout(GLayout);
}

void qserialPort::scanPort() {
    serialPort->clear();
    std::cout<<"testConnect\n";
    QList<QSerialPortInfo> serialPortList=QSerialPortInfo::availablePorts();
    
    if(serialPortList.isEmpty()){
        std::cout<<"\n";
        serialPort->addItem(QString("Empty0"));
        serialPort->addItem(QString("Empty1"));
        serialPort->addItem(QString("Empty2"));
        serialPort->addItem(QString("Empty3"));
        serialPort->addItem(QString("Empty4"));
        pilotLamp->setStyleSheet(m_red_SheetStyle);
    }else{
        for(int i=0;i<serialPortList.size();i++){
            if(serialPortList.at(i).portName().isEmpty()){
                std::cout<<"serialPort\n";
            }
        }
        pilotLamp->setStyleSheet(m_green_SheetStyle);
    }
}