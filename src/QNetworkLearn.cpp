#include "QNetworkLearn.h"

QNetworkLearn::QNetworkLearn(QWidget *parent) : QMainWindow(parent), ui(new Ui_QNetworkLearn) {
  ui->setupUi(this);
  initWidget();
  displayGUI();
  connetFunc();
}

QNetworkLearn::~QNetworkLearn() { delete ui; }
void QNetworkLearn::initWidget() {
  GBox = new QGroupBox(this);
  btnHostNameIp = new QPushButton(GBox);
  btnIP = new QPushButton(GBox);
  allInterface = new QPushButton(GBox);
  hostInfo = new QHostInfo();
  textEdit = new QTextEdit(GBox);
  lineEdit = new QLineEdit(GBox);
  GLayout = new QGridLayout(GBox);
  AllAdress=new QPushButton(GBox);
  label = new QLabel(GBox);
}
void QNetworkLearn::displayGUI() {
  GBox->setGeometry(10, 10, 400, 500);
  btnHostNameIp->setText("GetHostNameAndIP");

  GLayout->addWidget(btnHostNameIp, 0, 0);
  label->setText("domainName");
  btnIP->setText("GetIP");
  allInterface->setText("allInterFace");
  AllAdress->setText("allAdress");

  GLayout->addWidget(btnIP, 0, 1, 1, 1);
  GLayout->addWidget(label, 1, 0, 1, 1, Qt::AlignRight);
  GLayout->addWidget(AllAdress,0,2,1,1);
  GLayout->addWidget(allInterface, 1, 2, 1, 1);
  GLayout->addWidget(lineEdit, 1, 1, 1, 1);
  GLayout->addWidget(textEdit, 2, 0, 1, 3);
}

void QNetworkLearn::onBtnGetHostInfo() {
  textEdit->clear();
  QString strHostName = QHostInfo::localHostName();
  QHostInfo hostInfoStr = QHostInfo::fromName(strHostName);
  QList<QHostAddress> address = hostInfoStr.addresses();
  for (auto &elem : address) {
    QString strInfo = "HostName=" + strHostName + "\taddress=" + elem.toString();
    textEdit->append(strInfo);
  }
}

void QNetworkLearn::connetFunc() {
  connect(btnHostNameIp, &QPushButton::clicked, this, &QNetworkLearn::onBtnGetHostInfo);
  connect(btnIP, &QPushButton::clicked, this, &QNetworkLearn::onGetIPFromDomainName);
  connect(allInterface, &QPushButton::clicked, this, &QNetworkLearn::onBtnAllInterfaceClicked);
  connect(AllAdress,&QPushButton::clicked,this,&QNetworkLearn::onBtnAllAddressClicked);
}
void QNetworkLearn::onGetIPFromDomainName() {
  QString strDomainName = lineEdit->text();
  QHostInfo::lookupHost(strDomainName, this, SLOT(Ipinfo(QHostInfo)));
}
void QNetworkLearn::Ipinfo(const QHostInfo &hostinfo) {
  QList<QHostAddress> addrList = hostInfo->addresses();
  if (addrList.size()) {
    return;
  }
  std::cout << "addrListSize=" << addrList.size() << "\n";
}

void QNetworkLearn::onBtnAllInterfaceClicked() {
  auto list = QNetworkInterface::allInterfaces();
  for(auto &elem:list){
    QString strName=elem.humanReadableName();
    QString hardAddr=elem.hardwareAddress();
    auto type=elem.type();
    textEdit->append(QString("name="+strName));
    textEdit->append(QString("hardAddr="+hardAddr));
    textEdit->append(QString("type="+QString::number(type)));
    QList<QNetworkAddressEntry> addEntry=elem.addressEntries();
    for(auto &element:addEntry){
        auto ip=element.ip().toString();
        auto mask=element.netmask().toString();
        auto broadcastAddr=element.broadcast().toString();

        textEdit->append(QString("ip="+ip));
        textEdit->append(QString("mask="+mask));
        textEdit->append(QString("broadcastAddr="+broadcastAddr));
    }

  }
}

void QNetworkLearn::onBtnAllAddressClicked(){
  auto allAddressInfo=QNetworkInterface::allAddresses();
  if(allAddressInfo.empty()){
    return ;
  }
  for(auto &elem:allAddressInfo){
    //std::cout<<elem.protocol()<<std::endl;
    QString  address="Address="+elem.toString();
    textEdit->append(std::move(address));
  }
}