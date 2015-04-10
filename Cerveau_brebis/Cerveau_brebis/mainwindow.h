#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
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
    void changeDBParam();

private:
    ChildView * childView;
    void createActions();
    void createToolbar();


    /**
     * @brief Bouton "Paramètres" du menu
     */
    QMenu* menu;
    QAction* changeParamDB;

};

#endif // MAINWINDOW_H
