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
        /**
         * @brief Envoi un signal lors qu'un élément est sélectionné
         * @param index Elément sélectionné
         */
        void clicked(QModelIndex index);

public slots:
        /**
         * @brief Affiche la description de l'élément sélectionné.
         * @param index Pointeur sur l'élément sélectionné
         */
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

    /**
     * @brief Cette méhtode permet de remplir le QColumnView.
     *
     * Le widget QColulnView est initialisé avec les données de la base de données.
     * Un clic sur un élément ouvrira une nouvelle colonne avec les élements inclus
     * dans celui sélectionné.
     */
    void initializeColumnView();
    /**
     * @brief Parcours des enfants de l'élement avec l'id idParent
     * @param idParent Id de l'élement à parcourir
     * @param itemParent QStandardItem dans lequel ajouté les élements des enfants
     *
     * Cette fonction récursive parcours tous les enfants de l'élement
     * avec l'id_structure égale à idParent.
     *
     */
    void parcoursDatabase(QString idParent, QStandardItem * itemParent);

};

#endif // CHILDVIEW_H
