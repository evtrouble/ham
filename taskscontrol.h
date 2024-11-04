#ifndef TASKSCONTROL_H
#define TASKSCONTROL_H
#include <QString>
#include <QVector>
#include <QDateTime>
#include "mainwindow.h"

class Task
{
    friend class TasksControl;
    friend class TaskItem;

public:
    Task() = default;
    Task(const QString &content, const QString &deadline, bool finish = false)
        : content(content), finish(finish)
    {
        this->deadline = QDateTime::fromString(deadline, "yyyy/M/d hh:mm");
    }

    void setDeadline(const QDateTime& deadline)  { this->deadline = deadline; }

private:
    QString content; //内容
    QDateTime deadline;//截止日期
    bool finish; //是否已完成
};


class QListWidgetItem;

class TasksControl
{
public:
    TasksControl(Ui::MainWindow* ui);
    ~TasksControl();

public:
    void removeTask(int id);

private:
    bool loadData();
    bool writeData();

private:
    QVector<Task> tasks;
    Ui::MainWindow *ui;
    QListWidgetItem *currentItem = nullptr;
};

#endif // TASKSCONTROL_H
