#include "QTcpCommit.h"

QTcpCommit::QTcpCommit(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_QTcpCommit)
{
    ui->setupUi(this);
    initParams();
    displayGUI();
    getLocalIP(localIP);
    connectFunc(); //connect函数；
}

QTcpCommit::~QTcpCommit()
{
    delete ui; 
}
void QTcpCommit::connectFunc(){
    connect(actStartListen,&QAction::triggered,this,&QTcpCommit::onActStartListenTriggered);
    connect(actStopListen,&QAction::triggered,this,&QTcpCommit::onActStopListenTriggered);
    connect(tcpServer,&QTcpServer::newConnection,this,&QTcpCommit::doNewConnect);
    connect(changeWindow,&QPushButton::clicked,this,[=]{
        subwindow_1 *subWin=new subwindow_1(this);
        std::cout<<"窗口切换\n";
        this->close();
        subWin->show();
    });
    connect(closeWindow,&QPushButton::clicked,[=]{
        std::cout<<"窗口关闭\n";
        this->close();
    });
}
void QTcpCommit::initParams(){
    GBox=new QGroupBox(this);
    GLayout=new QGridLayout(GBox);
    tcpServer=new QTcpServer(this);
    tcpSocket=new QTcpSocket(this);

    listenStatus=new QLabel(GBox);
    socketStatus=new QLabel(GBox);
    toolBar=addToolBar("action");

    subGbx=new QGroupBox(this);
    changeWindow=new QPushButton(subGbx);
    changeWindow->setText("changeWindow");
    SubGLayout=new QGridLayout(subGbx);
    closeWindow=new QPushButton(subGbx);
    closeWindow->setText("closeWindow");
    

    actStartListen=new QAction(this);
    actStopListen=new QAction(this);
    actClearText=new QAction(this);
    actCloseConnect=new QAction(this);
    
    btnSendData=new QPushButton(GBox);
    cobAddress=new QComboBox(GBox);
    spbPort=new QSpinBox(GBox);
    spbPort->setMaximum(65535);
    spbPort->setMinimum(1024);
    spbPort->setValue(8086);
    lidInputData=new QLineEdit(GBox);
    listenAddress=new QLabel(GBox);
    listenPort=new QLabel(GBox);
    plainTextEdit=new QPlainTextEdit(this);
    
}

void QTcpCommit::displayGUI(){
    GBox->setGeometry(10,60,400,500);
    subGbx->setGeometry(450,60,300,100);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); //文字显示在图标下
    actStartListen->setText("startListen");
    actStartListen->setIcon(QIcon("./icon/start.svg"));
    actStopListen->setText("stopListen");
    actStopListen->setIcon(QIcon("./icon/pause.svg"));

    actClearText->setText("clearText");
    actClearText->setIcon(QIcon("./icon/clear.svg"));

    actCloseConnect->setText("closeCommit");
    actCloseConnect->setIcon(QIcon("icon/close.svg"));

    listenAddress->setText("listenAddress:");
    listenAddress->setAlignment(Qt::AlignRight);

    listenPort->setText("listenPort");
    listenPort->setAlignment(Qt::AlignRight);

    btnSendData->setText("sendData");

    toolBar->addAction(actStartListen);
    toolBar->addAction(actStopListen);
    toolBar->addAction(actClearText);
    toolBar->addAction(actCloseConnect);

    listenStatus->setText("listenStatus:");
    socketStatus->setText("socketStatus");
    socketStatus->setGeometry(QRect(200,0,100,20));
    ui->statusbar->addWidget(listenStatus);
    ui->statusbar->insertPermanentWidget(0,socketStatus);

    GLayout->addWidget(listenAddress,0,0,1,1);
    GLayout->addWidget(cobAddress,0,1,1,1);
    GLayout->addWidget(listenPort,0,2,1,1);
    GLayout->addWidget(spbPort,0,3,1,1);

    GLayout->addWidget(lidInputData,1,0,1,3);
    GLayout->addWidget(btnSendData,1,3,1,1);
    GLayout->addWidget(plainTextEdit,2,0,1,4);  

    SubGLayout->addWidget(changeWindow,0,0,1,1);
    SubGLayout->addWidget(closeWindow,0,1,1,1);
}
void QTcpCommit::getLocalIP(QString &retLocalIp){
    //获取本机IP
    QString localIPName=QHostInfo::localHostName();
    QHostInfo hostInfo=QHostInfo::fromName(localIPName);
    QList<QHostAddress> hostList=hostInfo.addresses();
    if(hostList.empty()){
        return ;
    }
    for(auto &elem:hostList){
        
        if(QAbstractSocket::IPv4Protocol==elem.protocol()){
            retLocalIp=elem.toString();
            cobAddress->addItem(retLocalIp);
            return ;
        }
    } 
}


void QTcpCommit::onActStartListenTriggered(){
    QString addressIP=cobAddress->currentText();
    uint16_t addressPort=spbPort->value();
    QHostAddress hostAddress;
    hostAddress.setAddress(addressIP);
    tcpServer->listen(hostAddress,addressPort);
    listenStatus->setText("listenStatus:listenning");
    actStartListen->setEnabled(false);
    actStopListen->setEnabled(true);

    std::cout<<"addressIP="<<addressIP.toStdString()<<" addressPort="<<addressPort<<"\n";
}
void QTcpCommit::onActStopListenTriggered(){
    if(tcpServer->isListening()){
        if(tcpServer!=nullptr &&tcpSocket->state()==QAbstractSocket::ConnectingState){
            tcpSocket->disconnectFromHost();
        }
        tcpServer->close();
        actStartListen->setEnabled(true);
        actStopListen->setEnabled(false);

    }
}

void QTcpCommit::doNewConnect(){
    tcpSocket=tcpServer->nextPendingConnection();//检查到客户端链接，创建socket
    //链接成功发出connected()信号
    connect(tcpSocket,&QTcpSocket::connected,this,&QTcpCommit::doClientConnect);
    connect(tcpSocket,&QTcpSocket::readyRead,this,&QTcpCommit::doReadDataFromClient);
    connect(tcpSocket,&QTcpSocket::disconnected,this,&QTcpCommit::doClientDisconnected);

}

void QTcpCommit::doClientConnect(){
        QString strPeerAdress=tcpSocket->peerAddress().toString();
        uint16_t peerPort=tcpSocket->peerPort();
        plainTextEdit->appendPlainText(strPeerAdress+"\t"+QString::number(peerPort));
}

void QTcpCommit::doReadDataFromClient(){
    while(tcpSocket->canReadLine()){
        plainTextEdit->appendPlainText("clientData: "+tcpSocket->readLine());
    }
}

void QTcpCommit::doClientDisconnected(){
    plainTextEdit->appendPlainText("disconnected client");
    tcpSocket->deleteLater();
}

void QTcpCommit::doSocketStateChanged(const QAbstractSocket::SocketState &state){
    switch (state)
    {
    case QAbstractSocket::SocketState::UnconnectedState:
        
        break;
    
    default:
        break;
    }
}