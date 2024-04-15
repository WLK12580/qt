#pragma once
#include <QAction>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QtNetwork/QHostInfo>
#include <QtNetwork/QNetworkInterface>
#include <iostream>

#include "ui_QNetworkLearn.h"

class QNetworkLearn : public QMainWindow {
  Q_OBJECT

 public:
  QNetworkLearn(QWidget *parent = nullptr);
  ~QNetworkLearn();

 public:
  void initWidget();
  void displayGUI();
  void connetFunc();

  void onBtnGetHostInfo();
  void onGetIPFromDomainName();
  void onBtnAllInterfaceClicked();
  void onBtnAllAddressClicked();
 private slots:
  void Ipinfo(const QHostInfo &hostinfo);

 protected:
 private:
  QGroupBox *GBox = nullptr;
  QGridLayout *GLayout = nullptr;
  QHostInfo *hostInfo = nullptr;
  QPushButton *btnHostNameIp = nullptr;
  QPushButton *btnIP = nullptr;
  QPushButton *allInterface = nullptr;
  QPushButton *AllAdress=nullptr;
  QLineEdit *lineEdit = nullptr;
  QLabel *label = nullptr;
  QTextEdit *textEdit = nullptr;

 private:
  Ui_QNetworkLearn *ui;
};