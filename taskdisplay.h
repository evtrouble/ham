#ifndef TASKDISPLAY_H
#define TASKDISPLAY_H
#include <QListWidget>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <unordered_map>

class QListWidgetItem;
class TaskItem;

class TaskDisplay : public QListWidget
{
    Q_OBJECT
public:
    TaskDisplay(QWidget *parent = nullptr);

    void itemChange(QListWidgetItem *currentItem, QDateTime &&deadline, QString &&text, int priority);
    void sortByDeadline();
    void sortByPriority();
    void init();
    void setSystemTrayIcon (QSystemTrayIcon *SysIcon) { trayIcon = SysIcon; }

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    void updateTaskItem(QListWidgetItem *currentItem, QDateTime &deadline, QString &text, int priority);
    void addTaskItem(QDateTime &deadline, QString &text, int priority);
    void initTaskItem(TaskItem* widget, QListWidgetItem* item);
    void removeTask(QListWidgetItem* currentItem);
    void clear_and_get(QVector<QJsonObject> &list_set);
    void setTimer(TaskItem* widget);

private:
    QSystemTrayIcon *trayIcon;
    std::unordered_map<int, TaskItem*> timerMap;

signals:
    void editorHide();
    void editorShow(QListWidgetItem*);
    void remove(QListWidgetItem*);
};

#endif // TASKDISPLAY_H
