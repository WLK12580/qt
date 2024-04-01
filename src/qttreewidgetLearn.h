#pragma once
#include "ui_qttreewidgetLearn.h"
#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDockWidget>

class qttreewidgetLearn : public QMainWindow {
    Q_OBJECT
    
public:
    qttreewidgetLearn(QWidget* parent = nullptr);
    ~qttreewidgetLearn();

public:
    void displayDockWidget();
    QTreeWidgetItem* getTreeWidgetItem();

private:
    QDockWidget *dockWidget=nullptr;
    QTreeWidget *treeWidget=nullptr;
private:
    Ui_qttreewidgetLearn* ui;
};