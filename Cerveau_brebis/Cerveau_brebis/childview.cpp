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

}

ChildView::~ChildView()
{
}
