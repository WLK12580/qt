#include "qlistwidget.h"

#include <QHBoxLayout>

# pragma execution_character_set("utf-8") 
qlistwidget::qlistwidget(QWidget *parent) : QMainWindow(parent), ui(new Ui_qlistwidget) {
  ui->setupUi(this);
  listWidget(this);
}

qlistwidget::~qlistwidget() { delete ui; }

void qlistwidget::listWidget(qlistwidget *listptr) {
  this->setWindowTitle("QListWidgetLearn");
  this->resize(800, 600);
  QListWidget *listObj = new QListWidget(this);  // listObj显示在this窗口
  listObj->resize(600, 600);
  listObj->setFont(QFont("宋体", 14));
  listObj->addItem("helloQListWidget");
  listObj->addItem("http://www.h");
  QIcon icon = QIcon("../icon/image.svg");
  QListWidgetItem *listItemPtr = new QListWidgetItem(icon, "image");
  listObj->addItem(listItemPtr);
  QHBoxLayout *HLayout = new QHBoxLayout(this);  // 布局在当前窗口
  HLayout->addWidget(listObj);

  QLabel *label = new QLabel(this);
  label->setText("select Text");
  label->setParent(this);
  label->resize(200, 50);
  label->move(600, 200);
  label->setAlignment(Qt::AlignCenter);
  HLayout->addWidget(label);
  setLayout(HLayout);
  connect(listObj, &QListWidget::itemClicked, [label](QListWidgetItem *list) { label->setText(list->text()); });
}
void qlistwidget::setText(QListWidgetItem *ptr) {}
