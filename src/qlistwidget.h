#pragma once
#include "ui_qlistwidget.h"
#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QListWidgetItem>

class qlistwidget : public QMainWindow {
    Q_OBJECT
    
public:
    qlistwidget(QWidget* parent = nullptr);
    ~qlistwidget();
    void listWidget(qlistwidget *listptr=nullptr);

    void setText(QListWidgetItem *ptr);

private:
    Ui_qlistwidget* ui;
};