#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget *parent)
    : QListWidget(parent) {}

void MyListWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        auto item = itemAt(event->pos());
        emit itemClicked(item);
    }
    QListWidget::mousePressEvent(event);
}
