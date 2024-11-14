#ifndef TASKEDITOR_H
#define TASKEDITOR_H

#include <QListWidgetItem>
#include "hamsystem.h"

class TaskEditor : public QFrame
{
    Q_OBJECT

public:
    TaskEditor(QWidget *parent = nullptr);
    QListWidgetItem* currentItem() { return currentItem_; }

    void itemChange(QListWidgetItem *currentItem);
    void setUi(Ui::MainWindow *ui);
    void showChange();

private:
    void setRetainSize();

private:
    QListWidgetItem *currentItem_ = nullptr;
    Ui::MainWindow *ui = nullptr;
};

#endif // TASKEDITOR_H
