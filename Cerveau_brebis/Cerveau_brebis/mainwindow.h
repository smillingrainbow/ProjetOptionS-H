#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "childview.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    ChildView * childView;
};

#endif // MAINWINDOW_H
