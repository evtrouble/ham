#ifndef COURSECONTROL_H
#define COURSECONTROL_H

#include "mainwindow.h"

class CourseControl
{
public:
    CourseControl(Ui::MainWindow *ui);
    void init();

private:
    Ui::MainWindow *ui;
};

#endif // COURSECONTROL_H
