#pragma once
#include <QMainWindow>
#include "ui_sub_window_1.h"
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>

class subwindow_1 : public QMainWindow {
    Q_OBJECT
    
public:
    subwindow_1(QWidget* parent = nullptr);
    ~subwindow_1();
private:
  QPushButton *btnReturnPreWindow=nullptr;
  QPushButton *btnCloseWindow=nullptr;
  QGroupBox *Gbx=nullptr;
  QGridLayout *GLayout=nullptr;
private:
    void initWidget();
private:
    Ui::subwindow_1* ui;
};