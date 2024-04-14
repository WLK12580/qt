#include "readWriteLock.h"

readWriteLock::readWriteLock(QWidget* parent) : QMainWindow(parent), ui(new Ui_readWriteLock) {
  ui->setupUi(this);
 
  initParamAndObject();
  toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  displayGUI();
  connectFunc();
}

readWriteLock::~readWriteLock() { delete ui; }
void readWriteLock::initParamAndObject() {
  writeThread = new WriteWorkThread(this);
  readThread = new ReadWorkThread(this);
  displayThread = new DisplayWorkThread(this);
  toolbar=addToolBar(tr("&file"));
  startAct=new QAction(this);
  pauseAct=new QAction(this);
  listWidget=new QListWidget(this);
}  
void readWriteLock::connectFunc() {
  connect(writeThread, &WriteWorkThread::started,this, [=] { //标识线程启动
    std::cout<<"线程启动\n";
  });
  connect(startAct,&QAction::triggered,this,&readWriteLock::startWorkThreadFunc);
  connect(writeThread,&WriteWorkThread::valueSignal,this,&readWriteLock::readDataFromWriteThread);
  connect(pauseAct,&QAction::triggered,this,&readWriteLock::pauseThreadFunc);
}

void readWriteLock::startWorkThreadFunc(){
    std::cout<<"start\n";
    writeThread->startWorkThread=true;
    writeThread->start();
}

void readWriteLock::readDataFromWriteThread(const std::queue<std::string> &queStr){
    if(queStr.empty()){
        return ;
    }
    std::queue<std::string> que(queStr);
    queData=queStr;
    readThread->start();
    displayThread->start();
    displayData();
  }

void readWriteLock::pauseThreadFunc(){
    std::cout<<"pauseThread\n";
    
    writeThread->startWorkThread=false;
}

void readWriteLock::displayGUI(){
  
  startAct->setText("start");
  startAct->setIcon(QIcon("./icon/开始.svg"));
  pauseAct->setText("pause");
  pauseAct->setIcon(QIcon("./icon/pause.svg"));
  toolbar->addAction(startAct);
  toolbar->addSeparator();
  toolbar->addAction(pauseAct);
  toolbar->addSeparator();
  listWidget->setGeometry(10,70,400,300);
}
void readWriteLock::displayData(){
  int queLength=queData.size();
  std::cout<<"queLength="<<queLength<<"\n";
  for(int i=0;i<queLength;i++){
    listWidget->addItem(QString::fromStdString("RecvData="+queData.front()));
    queData.pop();
  }
}