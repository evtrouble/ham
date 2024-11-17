#ifndef TASKSCONTROL_H
#define TASKSCONTROL_H
#include <QString>
#include <QVector>
#include <QDateTime>

#include "hamsystem.h"

class TasksControl
{
public:
    TasksControl(Ui::MainWindow* ui);
    void init();
    void reset();

private:
    void connectTaskDisplay();
    void disconnectTaskDisplay();
private:
    Ui::MainWindow *ui;
};

#endif // TASKSCONTROL_H
