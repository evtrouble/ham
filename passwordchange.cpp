#include "passwordchange.h"
#include "ui_passwordchange.h"

#include <QMessageBox>
#include <QPushButton>

PassWordChange::PassWordChange(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PassWordChange)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("确定");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");

    QDialogButtonBox::connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [=]{
        if(ui->passwordEdit->text() != ui->passwordConfirm->text())
        {
            QMessageBox::information(this, "注意!", "密码不同！");
            return;
        }

        emit changePassword(ui->oldPassword->text(), ui->passwordEdit->text());
    });//注册

    QDialogButtonBox::connect(ui->buttonBox, &QDialogButtonBox::rejected, this, [=]{
        close();
    });//取消
}

PassWordChange::~PassWordChange()
{
    delete ui;
}
