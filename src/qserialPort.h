#pragma once
#include "ui_qserialPort.h"
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPushButton>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QGroupBox>
#include <QComboBox>

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

private:
 QGridLayout *GLayout=nullptr;
 QHBoxLayout *HLayout=nullptr;
 QGroupBox *GBox=nullptr;

private:
    Ui_qserialPort* ui;
};