#include "qttreewidgetLearn.h"
#include "iostream"

qttreewidgetLearn::qttreewidgetLearn(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_qttreewidgetLearn)
{
    ui->setupUi(this);
    displayDockWidget();
}

qttreewidgetLearn::~qttreewidgetLearn()
{
    delete ui; 
}

void qttreewidgetLearn::displayDockWidget(){
    dockWidget=new QDockWidget(this);
    dockWidget->setWindowTitle("dockerWidget");

    QPalette palette;
    palette.setColor(QPalette::Window,Qt::green);
    dockWidget->setAutoFillBackground(true);
    dockWidget->setPalette(palette);
    dockWidget->setMinimumSize(500,400);
    dockWidget->setMaximumSize(800,600);

    treeWidget=new QTreeWidget(dockWidget);
    treeWidget->setColumnCount(3);
    QTreeWidgetItem *item=new QTreeWidgetItem(treeWidget);
    item->setText(0,"address");
    item->setIcon(0,QIcon("./icon/web.svg"));
    item->setCheckState(0,Qt::Unchecked);
    

    QStringList *strList=new QStringList();
    *strList<<"C语言教程"<<"http://c.biancheng.net/c/"<<"done";
    QTreeWidgetItem childItem(item,*strList);
    
    
    treeWidget->addTopLevelItem(item);
    dockWidget->setWidget(treeWidget);
}
