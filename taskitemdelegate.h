#ifndef TASKITEMDELEGATE_H
#define TASKITEMDELEGATE_H

#include <QStyledItemDelegate>

class TaskItemDelegate : QStyledItemDelegate
{
    Q_OBJECT
public:
    TaskItemDelegate(QWidget *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TASKITEMDELEGATE_H
