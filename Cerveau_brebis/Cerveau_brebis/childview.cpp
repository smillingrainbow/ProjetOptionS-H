#include "childview.h"
#include "ui_childview.h"

ChildView::ChildView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildView)
{
    ui->setupUi(this);
}

ChildView::~ChildView()
{
    delete ui;
}
