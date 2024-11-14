#ifndef COURSECONTROL_H
#define COURSECONTROL_H

#include "hamsystem.h"

class HamSystem;

class CourseControl
{
public:
    CourseControl(Ui::MainWindow *ui);
    void init();

private:
    Ui::MainWindow *ui;
};

#endif // COURSECONTROL_H
