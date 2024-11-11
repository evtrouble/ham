#include "homedisplay.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
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

    });//导出报表



}
