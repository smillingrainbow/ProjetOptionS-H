#include "childview.h"
#include "ui_childview.h"

ChildView::ChildView(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout();
    childColumnView = new QColumnView();
    descriptionText = new QTextEdit();

    hbox->addWidget(childColumnView);
    hbox->addWidget(descriptionText);

    connect(childColumnView, SIGNAL(clicked(QModelIndex)), this, SLOT(updateColumnView(QModelIndex)));


    model = new QStandardItemModel;

    initializeFirstColumn();

//    QStandardItem *name = new QStandardItem("Name");
//    QStandardItem *firstName = new QStandardItem("First Name");
//    QStandardItem *lastName = new QStandardItem("Last Name");

//    name->appendRow(firstName);
//    name->appendRow(lastName);
//    model.appendRow(name);

//    QStandardItem *john = new QStandardItem("John");
//    QStandardItem *smith = new QStandardItem("Smith");

//    firstName->appendRow(john);
//    lastName->appendRow(smith);

//    QStandardItem *address = new QStandardItem("Address");
//    QStandardItem *street = new QStandardItem("Street");
//    QStandardItem *city = new QStandardItem("City");
//    QStandardItem *state = new QStandardItem("State");
//    QStandardItem *country = new QStandardItem("Country");

//    address->appendRow(street);
//    address->appendRow(city);
//    address->appendRow(state);
//    address->appendRow(country);
//    model.appendRow(address);

//    QColumnView columnView;
//    columnView.setModel(&model);
//    columnView.show();

}

void ChildView::initializeFirstColumn(){
    QList<QString> listString;
    listString.append("Name");
    listString.append("Adress");

    item1= new QStandardItem(listString.at(0));
    item2 = new QStandardItem(listString.at(1));
    model->appendRow(item1);
    model->appendRow(item2);

    childColumnView->setModel(model);
}



void ChildView::updateQColumnView(QModelIndex index)
{
}
