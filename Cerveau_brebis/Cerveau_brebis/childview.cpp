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
    if(brain!= NULL){
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
    if(db.db_open_connection(userName, userPassword)){
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
    if(db.db_open_connection(userName, userPassword))
        result = db.get_result_select(requete);
    db.db_close_connection();

    for(int i=0; i<result.size(); i++){
        QString idChild = result.at(i).at(0);
        QStandardItem *itemChild = new QStandardItem(result.at(i).at(1));
        itemParent->appendRow(itemChild);
        parcoursDatabase(idChild, itemChild);
    }
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

    userName = name;
    userPassword = password;

    qDebug() << "Childview ";
    qDebug()<< "Name : " << name;
    qDebug() << "Password : " << password;
}


void ChildView::updateQColumnView(QModelIndex index)
{
    QStandardItem *item = model->itemFromIndex(index);
    QString requeteDesc = "SELECT id_structure, description FROM structure WHERE nom='"+item->text() + "'";
    Database db;
    if(db.db_open_connection(userName, userPassword)){
        QList<QList<QString> > resultDesc = db.get_result_select(requeteDesc);
        db.db_close_connection();
        if(resultDesc.size()>0){
            descriptionText->setText(resultDesc.at(0).at(1));
        }
    }
}


