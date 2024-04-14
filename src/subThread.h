
#pragma once
#include <QObject>
#include <QThread>
#include <queue>
#include <QReadWriteLock>
#include <QMutex>
#include <QRandomGenerator>
#include <iostream>
#include <stdio.h>

//定义一个公共的结构体：用于公共数据的存储

struct SharedData
{
    std::queue<std::string> que;
    int data=0;
    QReadWriteLock RWLock;
    QMutex mtx;
    bool ReadDone=false;
    bool disPlayDone=false;
};

// 工作线程类：用于往公共队列里写入数据
class WriteWorkThread : public QThread {
  Q_OBJECT
 public:
  WriteWorkThread(QWidget *parent = nullptr);

 private:
  void run();
  void generatorData();
  void removeOpt(int dataLength);
  void clearQue(std::queue<std::string> &que);
signals:
  void valueSignal(const std::queue<std::string> &queStr);
public:
  bool startWorkThread=false;
};
// 工作线程类：用于从公共队列里读取数据
class ReadWorkThread : public QThread {
 public:
  ReadWorkThread(QWidget *parent = nullptr);
 private:
  void run();

};
// 工作线程类：用于显示公共队列里中的数据
class DisplayWorkThread : public QThread {
 public:
  DisplayWorkThread(QWidget *parent = nullptr);
 private:
  void run();
};

