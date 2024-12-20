#include "registeruser.h"
#include "ui_registeruser.h"

#include <QMessageBox>
#include <QPushButton>

RegisterUser::RegisterUser(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterUser)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("注册");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");

    QDialogButtonBox::connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [=]{
        if(ui->passwordEdit->text() != ui->passwordConfirm->text())
        {
            QMessageBox::information(this, "注意!", "密码不同！");
            return;
        }

        emit registerUser(ui->usernameEdit->text(), ui->userEmailEdit->text(), ui->passwordEdit->text());
    });//注册

    QDialogButtonBox::connect(ui->buttonBox, &QDialogButtonBox::rejected, this, [=]{
        close();
    });//取消
}

RegisterUser::~RegisterUser()
{
    delete ui;
}
