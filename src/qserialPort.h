#pragma once
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

#include "ui_qserialPort.h"

class qserialPort : public QMainWindow {
  Q_OBJECT

 public:
  qserialPort(QWidget* parent = nullptr);
  ~qserialPort();

 private:
  void displayLayout(QWidget* parent = nullptr);
  void layout(QWidget* parent = nullptr);
  void recvSerialPortData(QWidget* parent = nullptr);
  void sendSerialPortData(QWidget* parent = nullptr);

  void connectFunc();

  void scanPort();

 private:
  QGridLayout* GLayout = nullptr;
  QHBoxLayout* HLayout = nullptr;
  QGroupBox* GBox = nullptr;
  QComboBox* serialPort = nullptr;
  QPushButton* scanPortPub = nullptr;
  QLabel* pilotLamp = nullptr;

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
  Ui_qserialPort* ui;
};