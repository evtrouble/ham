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
#include <QFile>

HamSystem::HamSystem(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    tasksControl = new TasksControl(ui);
    homeDisplay = new HomeDisplay(ui);
    clockWidget = new ClockWidget(ui);
    courseControl = new CourseControl(ui);

    initializeSystem();
    this->setWindowIcon(QIcon(":/img/logo.png"));

}

void HamSystem::initializeSystem()
{
    setupTrayIcon();
    setupNavigationButtons();
    setupLoginUI();
}

void HamSystem::setupTrayIcon()
{
    QMenu *menu = new QMenu(this);
    QIcon icon(":/img/logo.png");
    SysIcon = new QSystemTrayIcon(this);
    SysIcon->setIcon(icon);
    SysIcon->setToolTip("Ham");

    QAction *restor = new QAction("恢复", this);
    connect(restor, &QAction::triggered, this, &HamSystem::showNormal);

    QAction *quit = new QAction("退出", this);
    connect(quit, &QAction::triggered, qApp, [=] {
        this->hide();
        QApplication::quit();
    });

    connect(SysIcon, &QSystemTrayIcon::activated, this, &HamSystem::on_activatedSysTrayIcon);

    menu->addAction(restor);
    menu->addSeparator();
    menu->addAction(quit);
    SysIcon->setContextMenu(menu);
    SysIcon->show();

    ui->listWidget->setSystemTrayIcon(SysIcon);
}

void HamSystem::setupNavigationButtons()
{
    btns.clear();  // 清空现有按钮列表
    btns.append(ui->homeButton);
    btns.append(ui->classButton);
    btns.append(ui->tasksButton);
    btns.append(ui->clockButton);

    // 按钮均匀分布
    QVBoxLayout *VLayout = new QVBoxLayout;
    for (auto &btn : btns) {
        VLayout->addWidget(btn);
    }


    QWidget *widget = new QWidget(ui->tab);
    widget->setLayout(VLayout);
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    ui->tab->addWidget(widget);

    for (int id = 0; id < btns.size(); id++) {
        btns.at(id)->setFixedSize(50, 50);
        navConnect(id);
    }
}

void HamSystem::setupLoginUI()
{
    ui->buttonBox_2->button(QDialogButtonBox::Ok)->setText("登录");
    ui->buttonBox_2->button(QDialogButtonBox::Cancel)->setText("取消");

    // 断开之前的连接（如果有的话）
    QDialogButtonBox::disconnect(ui->buttonBox_2, &QDialogButtonBox::accepted, nullptr, nullptr);
    QPushButton::disconnect(ui->registerBtn, &QPushButton::clicked, nullptr, nullptr);

    // 重新建立登录连接
    QDialogButtonBox::connect(ui->buttonBox_2, &QDialogButtonBox::accepted, ui->stackedWidget, [=] {
        bool isAdmin = false;
        if(!NetDataAccess::instance()->userLogin(ui->usernameEdit->text(), ui->passwordEdit->text(), isAdmin))
            return;


        this->setStyleSheet("#MainWindow { background-image: none; background-color: white; }");

        homeDisplay->setUsername(ui->usernameEdit->text());
        if(isAdmin)
            homeDisplay->setuserType(UserType::ADMINISTRATOR);
        else
            homeDisplay->setuserType(UserType::ORDINARY);

        QColor color;
        color.setRgb(0xff, 0xa5, 0x00);
        QPalette pal = ui->homeButton->palette();
        pal.setColor(QPalette::ButtonText, color);
        ui->homeButton->setPalette(pal);
        this->showMaximized();

        homeDisplay->setUsername(ui->usernameEdit->text());
        tasksControl->init();
        courseControl->init();

        ui->stackedWidget->setCurrentIndex(0);
        ui->tab->show();
    });

    // 重新建立注册连接
    QPushButton::connect(ui->registerBtn, &QPushButton::clicked, ui->stackedWidget, [=] {
        RegisterUser userRegister(ui->centralwidget);
        userRegister.setWindowModality(Qt::ApplicationModal);
        RegisterUser::connect(&userRegister, &RegisterUser::registerUser, ui->centralwidget,
                              [&](const QString& username, const QString& email, const QString& password) {
                                  if(!NetDataAccess::instance()->userRegister(username, password, email))
                                      return;
                                  QMessageBox::information(ui->centralwidget, "注册成功!", "注册成功");
                                  userRegister.close();
                              });
        userRegister.show();
        userRegister.exec();
    });

    // 重置UI状态
    ui->tab->hide();
    ui->stackedWidget->setCurrentIndex(btns.size());
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();

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
        SysIcon->showMessage("Ham", "已最小化到托盘",QIcon(":/img/logo.png"));
        event->ignore();
    }
    else
    {
        event->accept();
    }
}
void HamSystem::logout()
{
    // 清除用户登录状态
    NetDataAccess::instance()->clearJwt();

    // 重置控制器状态
    resetControllers();

    // 重置UI状态
    resetUIState();
    this->showNormal();  // 添加这一行

    this->setStyleSheet("#MainWindow { background-image: url(:/img/reg_bg_min.jpg); }");

    // 切换到登录页面
    ui->stackedWidget->setCurrentIndex(btns.size());
    ui->tab->hide();

    // 清空登录表单
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
    // initializeSystem();
}
void HamSystem::resetUIState()
{
    // 重置所有导航按钮的样式
    for (auto& btn : btns) {
        btn->setPalette(ui->centralwidget->palette());
    }

    // 清空用户输入相关的字段
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
}
void HamSystem::resetControllers()
{
    // 重置各个控制器
    // homeDisplay->reset();
    courseControl->reset();
    tasksControl->reset();
    // clockWidget->reset();
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
