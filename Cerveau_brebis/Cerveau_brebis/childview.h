#ifndef CHILDVIEW_H
#define CHILDVIEW_H

#include <QWidget>
#include <QColumnView>
#include <QLayout>
#include <QTextEdit>
#include <QStandardItem>
#include <QStandardItemModel>
#include <iostream>
#include <QList>
#include <QString>

#include "database.h"

class ChildView : public QWidget
{
    Q_OBJECT

public:
    explicit ChildView(QWidget *parent = 0);
    ~ChildView(){}

signals :
        void clicked(QModelIndex index);

public slots:
        void updateQColumnView(QModelIndex index);

private:
    /**
     * @brief Widget permettant de lister au fur et à mesure les enfants de l'objet selectionné dans la colonne précédente
     */
    QColumnView *childColumnView;
    /**
     * @brief Description de l'objet sélectionné
     */
    QTextEdit *descriptionText;
    QStandardItemModel *model;
//    QStandardItem *item1;
//    QStandardItem *item2;

    void initializeFirstColumn();


};

#endif // CHILDVIEW_H
