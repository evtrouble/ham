#include "taskdisplay.h"
#include "taskitem.h"
#include "netdataaccess.h"

#include <QJsonDocument>
#include <QListWidget>
#include <QJsonArray>
#include <QMessageBox>
#include <QJsonObject>

TaskDisplay::TaskDisplay(QWidget *parent)
    : QListWidget(parent)
{
    this->setResizeMode(QListView::Adjust);
}

void TaskDisplay::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        auto item = itemAt(event->pos());
        if(item == nullptr)
        {
            emit editorHide();
            clearSelection();
        }
        else emit editorShow(item);
    }
    QListWidget::mousePressEvent(event);
}

void TaskDisplay::init()
{
    //bool success = NetDataAccess::instance()->loadData(value);
    NetDataAccess::instance()->loadData();

    NetDataAccess::connect(NetDataAccess::instance().get(), &NetDataAccess::finish, this, [=](QNetworkReply* reply){
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonParseError parseJsonErr;
            QJsonDocument document = QJsonDocument::fromJson(data, &parseJsonErr);

            if(parseJsonErr.error == QJsonParseError::NoError && document.isArray())
            {
                const auto& arr = document.array();
                for(const auto& task : arr)
                {
                    TaskItem* widget = new TaskItem(this);
                    QListWidgetItem* item = new QListWidgetItem;

                    widget->init(task.toObject(), item);
                    initTaskItem(widget, item);
                }
            }

        } else {
            qWarning() << "Network error:" << reply->errorString();
        }
        reply->deleteLater();
        NetDataAccess::disconnect(NetDataAccess::instance().get(), &NetDataAccess::finish, this, 0);
        once_resize = true;
    });
}

void TaskDisplay::itemChange(QListWidgetItem *currentItem, QDateTime &&deadline, QString &&text, int priority)
{
    if(currentItem == nullptr) addTaskItem(deadline, text, priority);
    else updateTaskItem(currentItem, deadline, text, priority);
}

void TaskDisplay::updateTaskItem(QListWidgetItem *currentItem, QDateTime &deadline, QString &text, int priority)
{
    TaskItem* widget = static_cast<TaskItem*>(itemWidget(currentItem));
    widget->setData(deadline, text, priority);
    currentItem->setSizeHint(QSize(widget->width(), widget->height()));
    NetDataAccess::instance()->updateItem(widget->toJson());
}

void TaskDisplay::addTaskItem(QDateTime &deadline, QString &text, int priority)
{
    TaskItem* widget = new TaskItem(this);
    QListWidgetItem* item = new QListWidgetItem;

    widget->init(deadline, text, priority, item);
    initTaskItem(widget, item);
    emit editorHide();

    int id = 0;
    NetDataAccess::instance()->addItem(widget->toJson(), id);
    widget->setId(id);
}

void TaskDisplay::initTaskItem(TaskItem* widget, QListWidgetItem* item)
{
    widget->setWidth(width() - 15);//内边距
    item->setSizeHint(QSize(widget->width(), widget->height()));
    addItem(item);
    setItemWidget(item, widget);
    widget->show();

    connect(widget, &TaskItem::remove, this, [=](QListWidgetItem* currentItem){
        NetDataAccess::instance()->deleteItem(static_cast<TaskItem*>(itemWidget(currentItem))->toJson());
        removeTask(currentItem);
    });
}

void TaskDisplay::removeTask(QListWidgetItem* currentItem)
{
    TaskItem* item = static_cast<TaskItem*>(itemWidget(currentItem));
    int ret = QMessageBox::question(this, "是否删除该待办",
                                    "待办:" + item->getText(),
                                    QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);

    if(ret == QMessageBox::Cancel)return;

    emit remove(currentItem);
    item->deleteLater();
    removeItemWidget(currentItem);
    delete takeItem(row(currentItem));
}

void TaskDisplay::sortByDeadline()
{
    QVector<QJsonObject> list_set;
    clear_and_get(list_set);
    std::sort(list_set.begin(), list_set.end(), [](const auto& a, const auto& b){
        if(a["deadline"].toString() == b["deadline"].toString()) return a["priority"].toInt() > b["priority"].toInt();
        return a["deadline"].toString() < b["deadline"].toString();
    });

    for(const auto& task : list_set)
    {
        TaskItem* widget = new TaskItem(this);
        QListWidgetItem* item = new QListWidgetItem;

        widget->init(task, item);
        initTaskItem(widget, item);
    }
}

void TaskDisplay::sortByPriority()
{
    QVector<QJsonObject> list_set;
    clear_and_get(list_set);
    std::sort(list_set.begin(), list_set.end(), [](const auto& a, const auto& b){
        if(a["priority"].toInt() == b["priority"].toInt()) return a["deadline"].toString() < b["deadline"].toString();
        return a["priority"].toInt() > b["priority"].toInt();
    });

    for(const auto& task : list_set)
    {
        TaskItem* widget = new TaskItem(this);
        QListWidgetItem* item = new QListWidgetItem;

        widget->init(task, item);
        initTaskItem(widget, item);
    }
}

void TaskDisplay::clear_and_get(QVector<QJsonObject> &list_set)
{
    list_set.resize(count());
    for(int id = 0; id < count(); id++)
    {
        list_set[id] = static_cast<TaskItem*>(itemWidget(item(id)))->toJson();
    }

    clear();
}

void TaskDisplay::resizeEvent(QResizeEvent *event)
{
    if(once_resize)
    {
        for(int id = 0; id < count(); id++){
            TaskItem* widget = static_cast<TaskItem*>(itemWidget(item(id)));
            widget->setWidth(event->size().width() - 15);//内边距
            item(id)->setSizeHint(QSize(widget->width(), widget->height()));
        }
    }

    QListWidget::resizeEvent(event);
}

void TaskDisplay::showEvent(QShowEvent *event)
{
    if(!once_show)
    {
        init();
        once_show = true;
    }

    QListWidget::showEvent(event);
}
