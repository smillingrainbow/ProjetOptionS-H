#include "infoview.h"
#include <QVBoxLayout>
#include <QSqlDatabase>
InfoView::InfoView(QWidget *parent) :
    QDialog(parent)
{
    Qt::WindowFlags flags = windowFlags();
    this->setWindowFlags(flags | Qt::WindowStaysOnTopHint);

    QVBoxLayout *vbox = new QVBoxLayout();
    infoColumnView = new QColumnView();
    descriptionText = new QTextEdit();

    vbox->addWidget(infoColumnView);
    vbox->addWidget(descriptionText);

    initializeColumnView();

    connect(infoColumnView, SIGNAL(clicked(QModelIndex)), this, SLOT(updateQColumnView(QModelIndex)));

    this->setLayout(vbox);

     IsOpened=false;
}

InfoView::~InfoView()
{

}

bool InfoView::getIsOpened()
{
    return IsOpened;
}
void InfoView::closeEvent(QCloseEvent *event)
{
    event->accept(); // close window
    this->close();
    IsOpened=false;
}

void InfoView::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );
    IsOpened=true;
}
void InfoView::initializeColumnView()
{
    model = new QStandardItemModel;

    /*Database db;
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

//        descriptionText->setText(result.at(0).at(1));

    }*/
    infoColumnView->setModel(model);
}

void InfoView::parcoursDatabase(QString idParent, QStandardItem *itemParent)
{
    /*QString requete = "SELECT id_structure, nom FROM structure WHERE id_parent='" + idParent + "'";
    Database db;
    QList<QList<QString> > result;
    if(db.db_open_connection())
        result = db.get_result_select(requete);
    db.db_close_connection();

    for(int i=0; i<result.size(); i++){
        QString idInfo = result.at(i).at(0);
        QStandardItem *itemInfo = new QStandardItem(result.at(i).at(1));
        itemParent->appendRow(itemInfo);
        parcoursDatabase(idInfo, itemInfo);
    }*/
}

void InfoView::updateQColumnView(QModelIndex index)
{
    /*QStandardItem *item = model->itemFromIndex(index);
    QString requeteDesc = "SELECT id_structure, description FROM structure WHERE nom='"+item->text() + "'";
    Database db;
    if(db.db_open_connection()){
        QList<QList<QString> > resultDesc = db.get_result_select(requeteDesc);
        db.db_close_connection();
        if(resultDesc.size()>0){
            descriptionText->setText(resultDesc.at(0).at(1));
        }
    }*/
}
