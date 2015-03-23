#ifndef CHILDVIEW_H
#define CHILDVIEW_H

#include <QWidget>
#include <QColumnView>
#include <QLayout>
#include <QTextEdit>

class ChildView : public QWidget
{
    Q_OBJECT

public:
    explicit ChildView(QWidget *parent = 0);
    ~ChildView();

private:
    /**
     * @brief Widget permettant de lister au fur et à mesure les enfants de l'objet selectionné dans la colonne précédente
     */
    QColumnView *childColumnView;
    /**
     * @brief Description de l'objet sélectionné
     */
    QTextEdit *descriptionText;
};

#endif // CHILDVIEW_H
