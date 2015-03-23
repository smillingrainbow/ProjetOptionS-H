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
    QColumnView *childColumnView;
    QTextEdit *descriptionText;
};

#endif // CHILDVIEW_H
