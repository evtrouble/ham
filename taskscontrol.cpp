#include <QWidget>
#include <QFile>
#include <QDateTime>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QListWidgetItem>
#include <QLabel>

#include "ui_mainwindow.h"
#include "taskitem.h"
#include "taskscontrol.h"

TasksControl::TasksControl(Ui::MainWindow* ui) : ui(ui)
{
    ui->editor->setUi(ui);

    connectTaskDisplay();

    QDialogButtonBox::connect(ui->buttonBox, &QDialogButtonBox::rejected, ui->editor, [=]{
        ui->editor->showChange();
    });//取消修改

    ui->addButton->setToolTip("添加新代办");
}

void TasksControl::connectTaskDisplay()
{
    TaskDisplay::connect(ui->listWidget, &TaskDisplay::editorHide, ui->editor, &QFrame::hide);//隐藏编辑页面

    QDialogButtonBox::connect(ui->buttonBox, &QDialogButtonBox::accepted, ui->listWidget, [=]{
        ui->listWidget->itemChange(ui->editor->currentItem(), ui->dateTimeEdit->dateTime(),
                                   ui->textEdit->toPlainText(), ui->comboBox->currentIndex());
    });//确认修改

    TaskDisplay::connect(ui->listWidget, &TaskDisplay::editorShow, ui->editor, [=](QListWidgetItem *currentItem){
        ui->editor->itemChange(currentItem);
    });//显示编辑页面

    TaskDisplay::connect(ui->listWidget, &TaskDisplay::remove, ui->editor, [=](QListWidgetItem* currentItem){
        if(currentItem == ui->editor->currentItem())
            ui->editor->hide();
    });//删除

    QPushButton::connect(ui->sortByDeadlineBtn, &QPushButton::clicked, ui->listWidget, [=]{
        disconnectTaskDisplay();
        ui->listWidget->sortByDeadline();
        connectTaskDisplay();
    });//按截止时间排序

    QPushButton::connect(ui->sortByPriorityBtn, &QPushButton::clicked, ui->listWidget, [=]{
        disconnectTaskDisplay();
        ui->listWidget->sortByPriority();
        connectTaskDisplay();
    });//按优先级排序

    QPushButton::connect(ui->addButton, &QPushButton::clicked, ui->textEdit, [=]{
        emit ui->listWidget->editorShow(nullptr);
    });//添加新代办
}

void TasksControl::disconnectTaskDisplay()
{
    ui->listWidget->disconnect();

    QDialogButtonBox::disconnect(ui->buttonBox, 0, ui->listWidget, 0);//确认修改

    QPushButton::disconnect(ui->sortByDeadlineBtn, 0, ui->listWidget, 0);//按截止时间排序

    QPushButton::disconnect(ui->sortByPriorityBtn, 0, ui->listWidget, 0);//按优先级排序

    QPushButton::disconnect(ui->addButton, 0, ui->textEdit, 0);//添加新代办
}
