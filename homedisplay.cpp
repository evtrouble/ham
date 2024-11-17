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
        HamSystem* hamSystem = qobject_cast<HamSystem*>(ui->centralwidget->window());
        if (hamSystem) {
            hamSystem->logout();  // 调用完整的 logout 函数
        }
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->count() - 1);//登出
        ui->tab->hide();
    });

    QPushButton::connect(ui->exportLogBtn, &QPushButton::clicked, ui->stackedWidget, [=] {
        QString dirPath = QFileDialog::getExistingDirectory(ui->home, "选择导出目录", QDir::currentPath());
        if (dirPath.isEmpty()) {
            QMessageBox::information(ui->home, "提示", "未选择目录");
            return;
        }

        QStringList errors;
        if (NetDataAccess::instance()->exportAllTables(dirPath, errors)) {
            QMessageBox::information(ui->home, "导出完成", "所有数据表已成功导出到目录: " + dirPath);
        } else {
            QMessageBox::warning(ui->home, "部分导出失败", "以下表导出失败: " + errors.join(", "));
        }
    });



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
