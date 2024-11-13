#include "coursecontrol.h"
#include "ui_mainwindow.h"

#include <QPushButton>

CourseControl::CourseControl(Ui::MainWindow *ui)
{
    this->ui = ui;
    ui->stackedWidget_2->setCurrentIndex(0);

    QPushButton::connect(ui->btnPersonalCourse, &QPushButton::clicked, ui->stackedWidget_2, [=]{
        ui->stackedWidget_2->setCurrentIndex(0);
    });//个人课表

    QPushButton::connect(ui->btnSchoolCourse, &QPushButton::clicked, ui->stackedWidget_2, [=]{
        ui->stackedWidget_2->setCurrentIndex(1);
    });//学校课表
}
