#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QMenuBar>

#include "childview.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /**
     * @brief Bouton "Paramètres" du menu
     */
    QMenu* menu;
    /**
     * @brief Barre de menu
     */
    QMenuBar* menubar;

private:
    ChildView * childView;
    void createActions();
    void createToolbar(QWidget* centralWidget);

};

#endif // MAINWINDOW_H
