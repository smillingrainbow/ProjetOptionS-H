#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    childView = new ChildView();

    this->setCentralWidget(childView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
