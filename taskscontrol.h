#ifndef TASKSCONTROL_H
#define TASKSCONTROL_H
#include <QString>
#include <QVector>
#include <QDateTime>

#include "mainwindow.h"

class TasksControl
{
public:
    TasksControl(Ui::MainWindow* ui);

private:
    void connectTaskDisplay();
    void disconnectTaskDisplay();

private:
    Ui::MainWindow *ui;
};

#endif // TASKSCONTROL_H
