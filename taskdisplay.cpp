#include "taskdisplay.h"
#include "taskitem.h"
#include "netdataaccess.h"

#include <QJsonDocument>
#include <QListWidget>
#include <QJsonArray>
#include <QMessageBox>
#include <QApplication>
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
    clear();

    //bool success = NetDataAccess::instance()->loadData(value);
    NetDataAccess::instance()->loadTaskData();

    NetDataAccess::connect(NetDataAccess::instance().get(), &NetDataAccess::TaskFinish, this, [=](QNetworkReply* reply){
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
            QMessageBox::critical(this, "Network error!", reply->errorString());
        }
        reply->deleteLater();
        NetDataAccess::disconnect(NetDataAccess::instance().get(), &NetDataAccess::TaskFinish, this, 0);
    });
}

void TaskDisplay::itemChange(QListWidgetItem *currentItem, QDateTime &&deadline, QString &&text, int priority)
{
    if(text == "")
    {
        QMessageBox::information(this, "注意!", "待办事项不能为空！");
        return;
    }
    if(deadline < QDateTime::currentDateTime())
    {
        QMessageBox::information(this, "注意!", "截止时间不能早于当前时间！");
        return;
    }
    if(currentItem == nullptr) addTaskItem(deadline, text, priority);
    else updateTaskItem(currentItem, deadline, text, priority);
}

void TaskDisplay::updateTaskItem(QListWidgetItem *currentItem, QDateTime &deadline, QString &text, int priority)
{
    TaskItem* widget = static_cast<TaskItem*>(itemWidget(currentItem));
    widget->setData(deadline, text, priority);
    currentItem->setSizeHint(QSize(widget->width(), widget->height()));
    NetDataAccess::instance()->updateTaskItem(widget->toJson());
}

void TaskDisplay::addTaskItem(QDateTime &deadline, QString &text, int priority)
{
    TaskItem* widget = new TaskItem(this);
    QListWidgetItem* item = new QListWidgetItem;

    widget->init(deadline, text, priority, item);
    initTaskItem(widget, item);
    emit editorHide();

    int id = 0;
    NetDataAccess::instance()->addTaskItem(widget->toJson(), id);
    widget->setId(id);
}

void TaskDisplay::initTaskItem(TaskItem* widget, QListWidgetItem* item)
{
    widget->setWidth(width() - 15);//内边距
    item->setSizeHint(QSize(widget->width(), widget->height()));
    addItem(item);
    setItemWidget(item, widget);
    widget->show();

    setTimer(widget);

    connect(widget, &TaskItem::remove, this, [=](QListWidgetItem* currentItem){
        NetDataAccess::instance()->deleteTaskItem(static_cast<TaskItem*>(itemWidget(currentItem))->toJson());
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

    int id = item->getTimerId();
    if(id != -1)
    {
        killTimer(id);
        timerMap.erase(id);
    }

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

    for(auto& [id, temp] : timerMap)
    {
        killTimer(id);
    }
    timerMap.clear();
    clear();
}

void TaskDisplay::resizeEvent(QResizeEvent *event)
{
    for(int id = 0; id < count(); id++){
        TaskItem* widget = static_cast<TaskItem*>(itemWidget(item(id)));
        if(widget == nullptr)continue;

        widget->setWidth(event->size().width() - 15);//内边距
        item(id)->setSizeHint(QSize(widget->width(), widget->height()));
    }

    QListWidget::resizeEvent(event);
}

void TaskDisplay::timerEvent(QTimerEvent *event)
{
    auto iter = timerMap.find(event->timerId());
    if(iter != timerMap.end())
    {
        killTimer(iter->first);

        if(!iter->second->isfinish()){
            QString title = "距离截止日期还有";

            int minutes = QDateTime::currentDateTime().secsTo(iter->second->getDeadline()) / 60;

            title += QString::number(minutes) + "分钟！";
            trayIcon->showMessage(title, iter->second->getText());
        }

        timerMap.erase(iter);
    }
    QListWidget::timerEvent(event);
}

void TaskDisplay::setTimer(TaskItem* widget)
{
    qint64 startSec = QDateTime::currentDateTime().toMSecsSinceEpoch();
    qint64 endSec = widget->getDeadline().toMSecsSinceEpoch();

    if(startSec < endSec && !widget->isfinish())
    {
        int id = startTimer(std::max(endSec - startSec - 3600000, 1000LL));
        timerMap.emplace(id, widget);
        widget->setTimerId(id);
    }
}
