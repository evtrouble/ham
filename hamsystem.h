#ifndef HAMSYSTEM_H
#define HAMSYSTEM_H

#include <QToolButton>

#include "taskscontrol.h"
#include "classcontrol.h"
#include "mainwindow.h"
#include "homedisplay.h"

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
    HomeDisplay homeDisplay;

    QVector<QToolButton*> btns;
};

#endif // HAMSYSTEM_H
