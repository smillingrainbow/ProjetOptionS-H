#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    childView = new ChildView();

    this->setCentralWidget(childView);
}

MainWindow::~MainWindow()
{
}
