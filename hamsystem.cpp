#include "hamsystem.h"
#include "ui_mainwindow.h"

#include <QIcon>
#include <QDebug>
#include <QVBoxLayout>

void HamSystem::navConnect(int id)
{
    QToolButton* btn_changed = btns.at(id);
    QToolButton::connect(btn_changed, &QToolButton::clicked, ui->stackedWidget, [=](){
        //切换页面
        btns.at(ui->stackedWidget->currentIndex())->setStyleSheet("color:white; background-color: transparent; border: 0;");

        btn_changed->setStyleSheet("color:orange; background-color: transparent; border: 0;");
        ui->stackedWidget->setCurrentIndex(id);
    });
}

HamSystem::HamSystem(Ui::MainWindow *ui) : ui(ui), tasksControl(ui)
{
    btns.append(ui->homeButton);
    btns.append(ui->classButton);
    btns.append(ui->tasksButton);
    btns.append(ui->settingsButton);

    //按钮均匀分布
    QVBoxLayout *VLayout = new QVBoxLayout;
    for(auto& btn : btns)
        VLayout->addWidget(btn);

    QWidget *widget = new QWidget(ui->tab);
    widget->setLayout(VLayout);
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    ui->tab->addWidget(widget);

    for (int id = 0; id < btns.size(); id++)
    {
        btns.at(id)->setFixedSize(50, 50);
        btns.at(id)->setStyleSheet("background-color: transparent; border: 0;");
        navConnect(id);
    }
    ui->homeButton->setStyleSheet("color:orange; background-color: transparent; border: 0;");
    ui->stackedWidget->setCurrentIndex(0);
}
