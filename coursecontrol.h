#ifndef COURSECONTROL_H
#define COURSECONTROL_H

#include "mainwindow.h"
#include "QComboBox.h"

class CourseControl
{
public:
    CourseControl(Ui::MainWindow *ui);
    void init();
    void setupWeekComboBox(QComboBox* comboBox) ;

private:
    Ui::MainWindow *ui;
};

#endif // COURSECONTROL_H
