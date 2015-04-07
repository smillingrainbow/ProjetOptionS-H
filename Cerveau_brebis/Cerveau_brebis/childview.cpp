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

    initializeColumnView();

    connect(childColumnView, SIGNAL(clicked(QModelIndex)), this, SLOT(updateQColumnView(QModelIndex)));

    this->setLayout(vbox);
}

void ChildView::initializeColumnView(){
    model = new QStandardItemModel;

    Database db;
    QString requete = "SELECT id_structure, nom FROM structure WHERE id_parent IS NULL";
    if(db.db_open_connection()){
        QList<QList<QString> > result = db.get_result_select(requete);
        db.db_close_connection();
        cout << result.size() << endl;
        cout << result[0].size() << endl;
        for(int i=0; i<result.size(); i++){
            QStandardItem *item = new QStandardItem(result.at(i).at(1));
            QString idParent = result.at(i).at(0);

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
    if(db.db_open_connection())
        result = db.get_result_select(requete);
    db.db_close_connection();

    for(int i=0; i<result.size(); i++){
        QString idChild = result.at(i).at(0);
        QStandardItem *itemChild = new QStandardItem(result.at(i).at(1));
        itemParent->appendRow(itemChild);
        parcoursDatabase(idChild, itemChild);
    }
}



void ChildView::updateQColumnView(QModelIndex index)
{
    QStandardItem *item = model->itemFromIndex(index);
    QString requeteDesc = "SELECT id_structure, description FROM structure WHERE nom='"+item->text() + "'";
    Database db;
    if(db.db_open_connection()){
        QList<QList<QString> > resultDesc = db.get_result_select(requeteDesc);
        db.db_close_connection();
        if(resultDesc.size()>0){
            descriptionText->setText(resultDesc.at(0).at(1));
        }
    }
}

