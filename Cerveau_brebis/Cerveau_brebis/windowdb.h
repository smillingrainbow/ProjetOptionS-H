#ifndef WINDOWDB_H
#define WINDOWDb_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QCloseEvent>

#include "childview.h"
#include "dialog.h"


class WindowDB : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowDB(QWidget *parent = 0);
    ~WindowDB();
    bool getIsOpened();

    QString getNameOfPartBrain() const;
    void setNameOfPartBrain(const QString &value);
signals:
    void changeParam();
private slots:
    /**
     * @brief Changement des logs de la bdd
     * Appelé lors du clic dans le menu "Base de donées"
     * Ouvre la fenetre d'identification
     */
    void changeDBParam1();
    void receiveNewParamWindow(QString name, QString password);

protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent* event );

private:
    ChildView * childView;
    /**
     * @brief Gestion des actions des boutons du menu
     */
    void createActions();
    /**
     * @brief Création de la barre de menu
     */
    void createMenubar();


    /**
     * @brief Bouton "Paramètres" du menu
     */
    QMenu* menu;
    QAction* changeParamDB;
    bool isOpened;
    QString nameOfPartBrain;
};

#endif // WINDOWDB_H
