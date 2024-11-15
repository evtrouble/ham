#include "homedisplay.h"
#include "ui_hamsystem.h"
#include "netdataaccess.h"
#include "passwordchange.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>

HomeDisplay::HomeDisplay(Ui::MainWindow* ui) : ui(ui)
{
    QImage Image;
    Image.load(":/icon/img/people.png");
    QPixmap pixmap = QPixmap::fromImage(Image);

    QPixmap fitpixmap = pixmap.scaled(ui->userImageDisplay->width(), ui->userImageDisplay->height(),
                                      Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->userImageDisplay->setPixmap(fitpixmap);//头像

    QPushButton::connect(ui->logoutBtn, &QPushButton::clicked, ui->stackedWidget, [=]{
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->count() - 1);//登出
        ui->tab->hide();
    });

    QPushButton::connect(ui->exportLogBtn, &QPushButton::clicked, ui->stackedWidget, [=]{
        QString dir_path=QFileDialog::getExistingDirectory(ui->home,"选择导出目录", QDir::currentPath());
        QFile file(dir_path);
        //bool ok = file.open(QIODevice::ReadWrite);

    });//导出报表

    QPushButton::connect(ui->changePasswordBtn, &QPushButton::clicked, ui->stackedWidget, [=]{
        PassWordChange passwordChange(ui->centralwidget);
        passwordChange.setWindowModality(Qt::ApplicationModal);
        PassWordChange::connect(&passwordChange, &PassWordChange::changePassword, ui->centralwidget, [&](const QString& old_password, const QString& new_password)
                              {
                                  if(!NetDataAccess::instance()->changePassword(old_password, new_password))return;
                                  QMessageBox::information(ui->centralwidget, "注册成功!", "注册成功");
                                  passwordChange.close();
                                  ui->stackedWidget->setCurrentIndex(ui->stackedWidget->count() - 1);//登出
                                  ui->tab->hide();
                              });
        passwordChange.show();
        passwordChange.exec();
    });//更改密码
}

void HomeDisplay::setUsername(const QString& username)
{
    ui->usernameDisplay->setText(username);
}

void HomeDisplay::setuserType(UserType userType)
{
    this->userType = userType;
    switch (userType) {
    case UserType::ADMINISTRATOR:
        ui->exportLogBtn->show();
        break;
    case UserType::ORDINARY:
         ui->exportLogBtn->hide();
        break;
    default:
        QMessageBox::critical(ui->centralwidget, "error!", "用户类型未知！");
        break;
    }
}
