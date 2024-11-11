#include "registeruser.h"
#include "ui_registeruser.h"

#include <QMessageBox>

RegisterUser::RegisterUser(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterUser)
{
    ui->setupUi(this);

    QDialogButtonBox::connect(ui->buttonBox_2, &QDialogButtonBox::accepted, this, [=]{
        if(ui->passwordEdit->text() != ui->passwordConfirm->text())
        {
            QMessageBox::information(this, "注意!", "密码不同！");
            return;
        }

        emit registerUser(ui->usernameEdit->text(), ui->userEmailEdit->text(), ui->passwordEdit->text());
    });//注册

    QDialogButtonBox::connect(ui->buttonBox_2, &QDialogButtonBox::rejected, this, [=]{
        close();
    });//关闭
}

RegisterUser::~RegisterUser()
{
    delete ui;
}
