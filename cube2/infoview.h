#ifndef INFOVIEW_H
#define INFOVIEW_H

#include <QDialog>
#include <QColumnView>
#include <QTextEdit>
#include <QStandardItem>
#include <QCloseEvent>
class InfoView : public QDialog
{
    Q_OBJECT

public:
    explicit InfoView(QWidget *parent = 0);
    ~InfoView();
    bool getIsOpened();
protected:
    void initializeColumnView();
    void parcoursDatabase(QString idParent, QStandardItem *itemParent);
    void updateQColumnView(QModelIndex index);
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent* event );
private:
    QColumnView *infoColumnView ;
    QTextEdit *descriptionText;
    QStandardItemModel *model;
    bool IsOpened;
};

#endif // INFOVIEW_H
