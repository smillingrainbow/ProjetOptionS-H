#include "childview.h"
#include "ui_childview.h"
using namespace std;

ChildView::ChildView(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout();
    childColumnView = new QColumnView();
    descriptionText = new QTextEdit();

    vbox->addWidget(childColumnView);
    vbox->addWidget(descriptionText);

    initializeFirstColumn();

    connect(childColumnView, SIGNAL(clicked(QModelIndex)), this, SLOT(updateQColumnView(QModelIndex)));

    this->setLayout(vbox);
}

void ChildView::initializeFirstColumn(){
    model = new QStandardItemModel;

    Database db;
    QString requete = "SELECT nom, description FROM structure WHERE id_parent IS NULL";
    if(db.db_open_connection()){
        QList<QList<QString> > result = db.get_result_select(requete);
        cout << result.size() << endl;
        cout << result[0].size() << endl;
        for(int i=0; i<result.size(); i++){
            //cout << result[i][0] << endl;
            model->appendRow(new QStandardItem(result.at(i).at(0)));
        }

        descriptionText->setText(result.at(0).at(1));

        db.db_close_connection();
    }


//    QList<QString> listString;
//    listString.append("Name");
//    listString.append("Adress");

//    model->appendRow(new QStandardItem(listString.at(0)));
//    model->appendRow(new QStandardItem(listString.at(1)));

    childColumnView->setModel(model);

}



void ChildView::updateQColumnView(QModelIndex index)
{
    descriptionText->setText("COUCOU");
}
