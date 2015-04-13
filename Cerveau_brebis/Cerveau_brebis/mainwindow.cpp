#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //QWidget *centralWidget = new QWidget(parent);

    childView = new ChildView();

    createActions();
    createMenubar();

    this->setCentralWidget(childView);

}

void MainWindow::createMenubar(){
    menu = menuBar()->addMenu("Parametres");
    menu->addAction(changeParamDB);
}

void MainWindow::createActions(){
    changeParamDB = new QAction("Base de données", this);
    connect(changeParamDB, SIGNAL(triggered()), this, SLOT(changeDBParam()));
}



MainWindow::~MainWindow()
{
}

void MainWindow::changeDBParam()
{
    Dialog* dialog = new Dialog();
    connect(dialog, SIGNAL(info(QString,QString)), childView, SLOT(receiveNewParam(QString,QString)));
    dialog->show();
}


