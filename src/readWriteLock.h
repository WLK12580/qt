#pragma once
#include "ui_readWriteLock.h"
#include <QMainWindow>
#include "subThread.h"
#include <QAction>
#include <QToolBar>
#include <queue>
#include <QListWidget>
#include <memory>

class readWriteLock : public QMainWindow {
    Q_OBJECT
    
public:
    readWriteLock(QWidget* parent = nullptr);
    ~readWriteLock();

private:
    Ui_readWriteLock* ui;
private:
    void initParamAndObject();
    void connectFunc();
private slots:
    void startWorkThreadFunc();
    void readDataFromWriteThread(const std::queue<std::string> &queStr);
    void pauseThreadFunc();
    void displayGUI();
    void displayData();

private:
    WriteWorkThread *writeThread=nullptr;
    ReadWorkThread *readThread=nullptr;
    DisplayWorkThread *displayThread=nullptr;

    QListWidget *listWidget=nullptr;

    
    QAction *startAct=nullptr;
    QAction *pauseAct=nullptr;
    QToolBar *toolbar=nullptr;
public:
 std::queue<std::string> queData;
 int lastQueSize=0;
};