#ifndef COURSECONTROL_H
#define COURSECONTROL_H

#include "hamsystem.h"

#include <QComboBox>

class HamSystem;

class CourseControl
{
public:
    CourseControl(Ui::MainWindow *ui);
    void init();
    void setupWeekComboBox(QComboBox *comboBox);
    void initializeCustomComboBox();
    void initWithoutCourse();
    void reset();

private:
    Ui::MainWindow *ui;



};

#endif // COURSECONTROL_H
