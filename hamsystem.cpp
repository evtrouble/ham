#include "hamsystem.h"
#include "ui_hamsystem.h"
#include "netdataaccess.h"
#include "registeruser.h"
#include "coursecontrol.h"
#include "taskscontrol.h"
#include "homedisplay.h"
#include "ClockWidget.h"

#include <QIcon>
#include <QDebug>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMenu>

HamSystem::HamSystem(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tasksControl = new TasksControl(ui);
    homeDisplay = new HomeDisplay(ui);
    clockWidget = new ClockWidget(ui);
    courseControl = new CourseControl(ui);

    // 最小化托盘
    QMenu *menu = new QMenu(this);
    QIcon icon(":/icon/img/icon.png");
    SysIcon = new QSystemTrayIcon(this);
    SysIcon->setIcon(icon);
    SysIcon->setToolTip("Ham");
    QAction *restor = new QAction("恢复", this);
    connect(restor, &QAction::triggered, this, &HamSystem::showNormal);
    QAction *quit = new QAction("退出", this);
    connect(quit, &QAction::triggered, qApp, [=]
            {
        this->hide();
        QApplication::quit(); });
    connect(SysIcon, &QSystemTrayIcon::activated, this, &HamSystem::on_activatedSysTrayIcon);

    menu->addAction(restor);
    menu->addSeparator(); // 分割
    menu->addAction(quit);
    SysIcon->setContextMenu(menu);
    SysIcon->show();

    btns.append(ui->homeButton);
    btns.append(ui->classButton);
    btns.append(ui->tasksButton);
    btns.append(ui->clockButton);

    // 按钮均匀分布
    QVBoxLayout *VLayout = new QVBoxLayout;
    for (auto &btn : btns)
        VLayout->addWidget(btn);

    QWidget *widget = new QWidget(ui->tab);
    widget->setLayout(VLayout);
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    ui->tab->addWidget(widget);
    ui->listWidget->setSystemTrayIcon(SysIcon);

    for (int id = 0; id < btns.size(); id++)
    {
        btns.at(id)->setFixedSize(50, 50);
        navConnect(id);
    }

    ui->buttonBox_2->button(QDialogButtonBox::Ok)->setText("登录");
    ui->buttonBox_2->button(QDialogButtonBox::Cancel)->setText("取消");

    QDialogButtonBox::connect(ui->buttonBox_2, &QDialogButtonBox::accepted, ui->stackedWidget, [=]
                              {
        bool isAdmin = false;
        if(!NetDataAccess::instance()->userLogin(ui->usernameEdit->text(), ui->passwordEdit->text(), isAdmin))return;
        homeDisplay->setUsername(ui->usernameEdit->text());
        if(isAdmin) homeDisplay->setuserType(UserType::ADMINISTRATOR);
        else homeDisplay->setuserType(UserType::ORDINARY);

        QColor color;
        color.setRgb(0xff, 0xa5, 0x00);
        QPalette pal = ui->homeButton->palette();
        pal.setColor(QPalette::ButtonText, color);
        ui->homeButton->setPalette(pal);

        homeDisplay->setUsername(ui->usernameEdit->text());
        tasksControl->init();
        // 登录成功后初始化课程控制器并获取课程数据
        courseControl->init();

        ui->stackedWidget->setCurrentIndex(0);
        ui->tab->show();
    });

    QPushButton::connect(ui->registerBtn, &QPushButton::clicked, ui->stackedWidget, [=]
                         {
        RegisterUser userRegister(ui->centralwidget);
        userRegister.setWindowModality(Qt::ApplicationModal);
        RegisterUser::connect(&userRegister, &RegisterUser::registerUser, ui->centralwidget, [&](const QString& username, const QString& email, const QString& password)
                              {
                                  if(!NetDataAccess::instance()->userRegister(username, password, email))return;
                                  QMessageBox::information(ui->centralwidget, "注册成功!", "注册成功");
                                  userRegister.close();
                              });
        userRegister.show();
        userRegister.exec();
    }); // 注册

    ui->tab->hide();
    ui->stackedWidget->setCurrentIndex(btns.size());

    ui->stackedWidget->setCurrentIndex(0);
    ui->tab->show();
    homeDisplay->setuserType(UserType::ORDINARY);

    QColor color;
    color.setRgb(0xff, 0xa5, 0x00);
    QPalette pal = ui->homeButton->palette();
    pal.setColor(QPalette::ButtonText, color);
    ui->homeButton->setPalette(pal);
}

HamSystem::~HamSystem()
{
    delete homeDisplay;
    delete courseControl;
    delete tasksControl;
    delete clockWidget;
    delete ui;
}

void HamSystem::navConnect(int id)
{
    QToolButton *btn_changed = btns.at(id);
    QToolButton::connect(btn_changed, &QToolButton::clicked, ui->stackedWidget, [=]
                         {
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

void HamSystem::closeEvent(QCloseEvent *event)
{
    if (SysIcon->isVisible())
    {
        this->hide();
        SysIcon->showMessage("Ham", "已最小化到托盘");
        event->ignore();
    }
    else
    {
        event->accept();
    }
}

void HamSystem::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {

    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:
        this->show();
        break;
    default:
        break;
    }
}
