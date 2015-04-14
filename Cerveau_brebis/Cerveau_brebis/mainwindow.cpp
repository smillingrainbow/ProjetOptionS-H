#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //QWidget *centralWidget = new QWidget(parent);

    childView = new ChildView();

    createActions();
    createMenubar();

    this->setCentralWidget(childView);

    isOpened = false;
}

void MainWindow::createMenubar(){
    menu = menuBar()->addMenu("Parametres");
    menu->addAction(changeParamDB);
}
QString MainWindow::getNameOfPartBrain() const
{
    return nameOfPartBrain;
}

void MainWindow::setNameOfPartBrain(const QString &value)
{
    qDebug() << "MainWindow : " << value;
    nameOfPartBrain = value;
    childView->setBrain(value);
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

bool MainWindow::getIsOpened(){
    return isOpened;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept(); // close window
    this->close();
    isOpened=false;
}

void MainWindow::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );
    isOpened=true;
}
