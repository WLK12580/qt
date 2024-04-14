#include "subThread.h"


SharedData sharedData;
//写现场的构造
WriteWorkThread::WriteWorkThread(QWidget *parent){}
//读线程的构造
ReadWorkThread::ReadWorkThread(QWidget *parent){}
//显示线程的构造
DisplayWorkThread::DisplayWorkThread(QWidget *parent){}
void WriteWorkThread::run(){
    {
        QWriteLocker WLock(&sharedData.RWLock); //锁住读写锁
        generatorData();
    }
}
void WriteWorkThread::generatorData(){
    if(!startWorkThread){
        return ;
    }
    for(int i=0;i<10;i++){
        sharedData.data+=QRandomGenerator::global()->bounded(0,101);//随机产生0-100的数据
    }
    
    int avgData=sharedData.data/10;
    std::cout<<"writeThreadStartVal="<<avgData<<"\n";
    sharedData.que.emplace(std::to_string(avgData));
    emit valueSignal(sharedData.que);
    clearQue(sharedData.que); //发送数据后队列清空；
    sharedData.data=0; //数据存入队列中后，归零防止干扰下次，计算结果
}
void ReadWorkThread::run(){
    QReadLocker RLock(&sharedData.RWLock);
    if(sharedData.que.empty()){
        return ;
    }
    std::string data=sharedData.que.front(); //注意此处是读锁不修改数据
    std::cout<<"readData="<<data<<"\n";
}

void DisplayWorkThread::run(){
    QReadLocker RLock(&sharedData.RWLock);
    if(sharedData.que.empty()){
        return ;
    }
    std::string data=sharedData.que.front();  
}


void WriteWorkThread::clearQue(std::queue<std::string> &que){
    std::queue<std::string> queTemp;
    swap(que,queTemp);
}