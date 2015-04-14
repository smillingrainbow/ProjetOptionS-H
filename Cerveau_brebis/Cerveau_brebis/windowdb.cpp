#include "windowdb.h"

WindowDB::WindowDB(QWidget *parent) :
    QMainWindow(parent)
{
    //QWidget *centralWidget = new QWidget(parent);

    childView = new ChildView();

    createActions();
    createMenubar();

    this->setCentralWidget(childView);

    isOpened = false;
}

void WindowDB::createMenubar(){
    menu = menuBar()->addMenu("Parametres");
    menu->addAction(changeParamDB);
}
QString WindowDB::getNameOfPartBrain() const
{
    return nameOfPartBrain;
}

void WindowDB::setNameOfPartBrain(const QString &value)
{
    qDebug() << "MainWindow : " << value;
    nameOfPartBrain = value;
    childView->setBrain(value);
}


void WindowDB::createActions(){
    changeParamDB = new QAction("Base de données", this);
    connect(changeParamDB, SIGNAL(triggered()), this, SLOT(changeDBParam1()));
}



WindowDB::~WindowDB()
{
}

void WindowDB::changeDBParam1()
{
    Dialog* dialog = new Dialog();
    connect(dialog, SIGNAL(info(QString,QString)), childView, SLOT(receiveNewParam(QString,QString)));
    dialog->show();
}

void WindowDB::receiveNewParamWindow(QString name, QString password)
{
    childView->setUserName(name);
    childView->setUserPassword(password);

    connect(this, SIGNAL(changeParam()), childView, SLOT(receiveParam()));

    emit changeParam();
}

bool WindowDB::getIsOpened(){
    return isOpened;
}

void WindowDB::closeEvent(QCloseEvent *event)
{
    event->accept(); // close window
    this->close();
    isOpened=false;
}

void WindowDB::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );
    isOpened=true;
}
