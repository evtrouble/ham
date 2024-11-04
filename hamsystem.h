#ifndef HAMSYSTEM_H
#define HAMSYSTEM_H

#include <QToolButton>

#include "taskscontrol.h"
#include "classcontrol.h"
#include "mainwindow.h"

class HamSystem
{
public:
    HamSystem(Ui::MainWindow *ui);

private:
    void navConnect(int id);

private:
    Ui::MainWindow *ui;
    TasksControl tasksControl;
    ClassControl classControl;

    QVector<QToolButton*> btns;
};

#endif // HAMSYSTEM_H
