#pragma once
#include "ui_QTcpCommit.h"
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLabel>
#include <QGroupBox>
#include <QAction>
#include <QToolBar>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QHostAddress>
#include <QHostInfo>
#include <iostream>
#include "sub_window_1.h"

class QTcpCommit : public QMainWindow {
    Q_OBJECT
    
public:
    QTcpCommit(QWidget* parent = nullptr);
    ~QTcpCommit();
private:
    void initParams();
    void displayGUI();
    void getLocalIP(QString &retLocalIp);

    void connectFunc();
private slots:
    void onActStartListenTriggered();
    void onActStopListenTriggered();
    void doNewConnect();
    void doClientConnect();
    void doReadDataFromClient();
    void doClientDisconnected();
    void doSocketStateChanged(const QAbstractSocket::SocketState &state);
private:
    QTcpServer *tcpServer=nullptr;
    QTcpSocket *tcpSocket=nullptr;

    QLabel *listenStatus=nullptr;
    QLabel *socketStatus=nullptr;
    QLabel *listenAddress=nullptr;
    QLabel *listenPort=nullptr;
    

    QGroupBox *GBox=nullptr;
    QGridLayout *GLayout=nullptr;

    QAction *actStartListen=nullptr;
    QAction *actStopListen=nullptr;
    QAction *actClearText=nullptr;
    QAction *actCloseConnect=nullptr;
    QToolBar *toolBar=nullptr;

    QPushButton *btnSendData=nullptr;
    QComboBox *cobAddress=nullptr;
    QSpinBox *spbPort=nullptr;
    QLineEdit *lidInputData=nullptr;

    QPlainTextEdit *plainTextEdit=nullptr;

    QPushButton *changeWindow=nullptr;
    QPushButton *closeWindow=nullptr;
    QGroupBox *subGbx=nullptr;
    QGridLayout *SubGLayout=nullptr;


private:
    Ui_QTcpCommit* ui;
    QString localIP="";
};