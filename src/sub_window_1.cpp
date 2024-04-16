#include "sub_window_1.h"
#include "ui_sub_window_1.h"
#include "QTcpCommit.h"

subwindow_1::subwindow_1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::subwindow_1)
{
    ui->setupUi(this);
    initWidget();
}

subwindow_1::~subwindow_1()
{
    delete ui;
}
void subwindow_1::initWidget(){
    Gbx=new QGroupBox(this);
    GLayout=new QGridLayout(Gbx);
    btnReturnPreWindow=new QPushButton(Gbx);
    btnCloseWindow=new QPushButton(Gbx);
    btnReturnPreWindow->setText("returnLastWindow");
    btnCloseWindow->setText("close");
    Gbx->setGeometry(100,60,300,50);
    GLayout->addWidget(btnCloseWindow,0,1,1,1);
    GLayout->addWidget(btnReturnPreWindow,0,0,1,1);
    connect(btnReturnPreWindow,&QPushButton::clicked,[=]{
        QTcpCommit *mianWindow=new QTcpCommit(this);
        this->close();
        std::cout<<"返回主窗口\n";
        mianWindow->show();
    });
    connect(btnCloseWindow,&QPushButton::clicked,[=]{
        std::cout<<"关闭子窗口\n";
        this->close();
    });
}