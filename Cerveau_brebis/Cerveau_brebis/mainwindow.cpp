#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    childView = new ChildView();

    this->setCentralWidget(childView);
}

MainWindow::~MainWindow()
{
}
