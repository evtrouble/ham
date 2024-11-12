#include "hamsystem.h"
#include "ui_mainwindow.h"
#include "netdataaccess.h"
#include "registeruser.h"

#include <QIcon>
#include <QDebug>
#include <QVBoxLayout>
#include <QMessageBox>

void HamSystem::navConnect(int id)
{
    QToolButton* btn_changed = btns.at(id);
    QToolButton::connect(btn_changed, &QToolButton::clicked, ui->stackedWidget, [=]{
        //切换页面
        if(ui->stackedWidget->currentIndex() < btns.size())
            btns.at(ui->stackedWidget->currentIndex())->setPalette(ui->centralwidget->palette().color(QPalette::Window));

        QColor color;
        color.setRgb(0xff, 0xa5, 0x00);
        QPalette pal = btn_changed->palette();
        pal.setColor(QPalette::ButtonText, color);
        btn_changed->setPalette(pal);

        ui->stackedWidget->setCurrentIndex(id);
    });
}

HamSystem::HamSystem(Ui::MainWindow *ui) : ui(ui), tasksControl(ui), homeDisplay(ui)
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
        navConnect(id);
    }

    ui->buttonBox_2->button(QDialogButtonBox::Ok)->setText("登录");
    ui->buttonBox_2->button(QDialogButtonBox::Cancel)->setText("取消");
    QDialogButtonBox::connect(ui->buttonBox_2, &QDialogButtonBox::accepted, ui->stackedWidget, [=]{
        bool isAdmin = false;
        if(!NetDataAccess::instance()->userLogin(ui->usernameEdit->text(), ui->passwordEdit->text(), isAdmin))return;
        homeDisplay.setUsername(ui->usernameEdit->text());
        if(isAdmin) homeDisplay.setuserType(UserType::ADMINISTRATOR);
        else homeDisplay.setuserType(UserType::ORDINARY);

        QColor color;
        color.setRgb(0xff, 0xa5, 0x00);
        QPalette pal = ui->homeButton->palette();
        pal.setColor(QPalette::ButtonText, color);
        ui->homeButton->setPalette(pal);
        homeDisplay.setUsername(ui->usernameEdit->text());
        ui->stackedWidget->setCurrentIndex(0);
        ui->tab->show();
    });//登录

    QPushButton::connect(ui->registerBtn, &QPushButton::clicked, ui->stackedWidget, [=]{
        RegisterUser userRegister(ui->centralwidget);
        RegisterUser::connect(&userRegister, &RegisterUser::registerUser, ui->centralwidget, [&](const QString& username, const QString& email, const QString& password)
        {
            if(!NetDataAccess::instance()->userRegister(username, password, email))return;
            QMessageBox::information(ui->centralwidget, "注册成功!", "注册成功");
            userRegister.close();
        });
        userRegister.show();
        userRegister.exec();
    });//注册


    ui->tab->hide();
    ui->stackedWidget->setCurrentIndex(btns.size());
}
