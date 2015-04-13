#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>

#include "childview.h"
#include "dialog.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**
     * @brief Changement des logs de la bdd
     * Appelé lors du clic dans le menu "Base de donées"
     * Ouvre la fenetre d'identification
     */
    void changeDBParam();

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

};

#endif // MAINWINDOW_H
