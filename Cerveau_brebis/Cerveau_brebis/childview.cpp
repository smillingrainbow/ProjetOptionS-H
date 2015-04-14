#include "childview.h"
using namespace std;

ChildView::ChildView(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout();
    childColumnView = new QColumnView();
    descriptionText = new QTextEdit();

    vbox->addWidget(childColumnView);
    vbox->addWidget(descriptionText);
    newLogin = false;
    Database db;
    if(brain!= NULL && db.db_open_connection(userName, userPassword, newLogin)){
        initializeColumnView();
        connect(childColumnView, SIGNAL(clicked(QModelIndex)), this, SLOT(updateQColumnView(QModelIndex)));
    }


//    userName = new QString();
//    userPassword = new QString();

    this->setLayout(vbox);
}

void ChildView::initializeColumnView(){
    model = new QStandardItemModel;

    Database db;
    qDebug()<< brain ;
    QString requete = "SELECT id_structure FROM structure WHERE nom='"+brain + "'";
    if(db.db_open_connection(userName, userPassword, newLogin)){
        QList<QList<QString> > result = db.get_result_select(requete);
        db.db_close_connection();
//        cout << result.size() << endl;
//        cout << result[0].size() << endl;
        if(result.size() > 0){
            QStandardItem *item = new QStandardItem(brain);
            QString idParent = result.at(0).at(0);

            parcoursDatabase(idParent, item);

            model->appendRow(item);
        }
    }
    childColumnView->setModel(model);

}

void ChildView::parcoursDatabase(QString idParent, QStandardItem *itemParent)
{
    QString requete = "SELECT id_structure, nom FROM structure WHERE id_parent='" + idParent + "'";
    Database db;
    QList<QList<QString> > result;
    if(db.db_open_connection(userName, userPassword, newLogin))
        result = db.get_result_select(requete);
    db.db_close_connection();

    for(int i=0; i<result.size(); i++){
        QString idChild = result.at(i).at(0);
        QStandardItem *itemChild = new QStandardItem(result.at(i).at(1));
        itemParent->appendRow(itemChild);
        parcoursDatabase(idChild, itemChild);
    }
}
QString ChildView::getUserName() const
{
    return userName;
}

void ChildView::setUserName(const QString &value)
{
    userName = value;
}

QString ChildView::getUserPassword() const
{
    return userPassword;
}

void ChildView::setUserPassword(const QString &value)
{
    userPassword = value;
}

QString ChildView::getBrain() const
{
    return brain;
}

void ChildView::setBrain(const QString &value)
{
    brain = value;
    initializeColumnView();
    connect(childColumnView, SIGNAL(clicked(QModelIndex)), this, SLOT(updateQColumnView(QModelIndex)));
}


void ChildView::receiveNewParam(QString name, QString password)
{
    //    userName = new QString(name);
    //    userPassword = new QString(password);
    newLogin = true;

    userName = name;
    userPassword = password;

    qDebug() << "Childview ";
    qDebug()<< "Name : " << name;
    qDebug() << "Password : " << password;
    initializeColumnView();
}

void ChildView::receiveParam()
{
    newLogin=true;
    initializeColumnView();
}


void ChildView::updateQColumnView(QModelIndex index)
{
    QStandardItem *item = model->itemFromIndex(index);
    QString requeteDesc = "SELECT id_structure, description FROM structure WHERE nom='"+item->text() + "'";
    Database db;
    if(db.db_open_connection(userName, userPassword, newLogin)){
        QList<QList<QString> > resultDesc = db.get_result_select(requeteDesc);
        db.db_close_connection();
        if(resultDesc.size()>0){
            descriptionText->setText(resultDesc.at(0).at(1));
        }
    }
}


