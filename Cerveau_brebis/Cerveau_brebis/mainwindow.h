#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QCloseEvent>

#include "childview.h"
#include "dialog.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool getIsOpened();

    QString getNameOfPartBrain() const;
    void setNameOfPartBrain(const QString &value);

private slots:
    /**
     * @brief Changement des logs de la bdd
     * Appelé lors du clic dans le menu "Base de donées"
     * Ouvre la fenetre d'identification
     */
    void changeDBParam();

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

#endif // MAINWINDOW_H
