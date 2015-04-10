#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(parent);

    childView = new ChildView();

    createToolbar(centralWidget);
    createActions();


    this->setCentralWidget(childView);

}

void MainWindow::createToolbar(QWidget* centralWidget){

    menubar = new QMenuBar(centralWidget);

    menu = new QMenu("PARAMETRES");
    menu->addMenu(new QMenu("Base de données"));

    menubar->addMenu(menu);
}

void MainWindow::createActions(){

}



MainWindow::~MainWindow()
{
}
