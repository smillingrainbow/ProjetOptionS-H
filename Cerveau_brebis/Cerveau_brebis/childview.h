#ifndef CHILDVIEW_H
#define CHILDVIEW_H

#include <QWidget>

namespace Ui {
class ChildView;
}

class ChildView : public QWidget
{
    Q_OBJECT

public:
    explicit ChildView(QWidget *parent = 0);
    ~ChildView();

private:
    Ui::ChildView *ui;
};

#endif // CHILDVIEW_H
