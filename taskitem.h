#ifndef TASKITEM_H
#define TASKITEM_H

#include <QCheckBox>
#include <QLabel>
#include <QWidget>
#include <QPushButton>

class TasksControl;
class Task;

class TaskItem : public QWidget
{
    Q_OBJECT
    friend class TasksControl;

public:
    TaskItem(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* Event) override;

    bool event(QEvent *event) override;
    void setData(Task& task, int id);
    void setData(QString &&s);
    void bind(int width, TasksControl* tasksControl);

    int getid() { return id; }
    void setId(int id) { this->id = id; }

private:
    QCheckBox* checkBox = nullptr;
    QPushButton* deleteButton = nullptr;
    QLabel* text = nullptr;
    int id;

signals:
    void remove(int);
};

#endif // TASKITEM_H
