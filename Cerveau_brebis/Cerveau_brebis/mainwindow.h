#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "childview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ChildView * childView;
};

#endif // MAINWINDOW_H
