#ifndef COURSECONTROL_H
#define COURSECONTROL_H

#include "hamsystem.h"
#include "qcombobox.h"
class HamSystem;

class CourseControl
{
public:
    CourseControl(Ui::MainWindow *ui);
    void init();
    void setupWeekComboBox(QComboBox *comboBox);

private:
    Ui::MainWindow *ui;
};

#endif // COURSECONTROL_H
