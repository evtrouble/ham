#include "taskeditor.h"
#include "ui_hamsystem.h"
#include "taskitem.h"

#include <QSizePolicy>
#include <QDateTime>

TaskEditor::TaskEditor(QWidget *parent) : QFrame(parent)
{
}

void TaskEditor::itemChange(QListWidgetItem *currentItem)
{
    currentItem_ = currentItem;
    showChange();
}

void TaskEditor::showChange()
{
    if(currentItem_ == nullptr)
    {
        ui->comboBox->setCurrentIndex(0);
        ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
        ui->textEdit->clear();
    }
    else
    {
        TaskItem* task = static_cast<TaskItem*>(ui->listWidget->itemWidget(currentItem_));
        ui->comboBox->setCurrentIndex(task->getPriority());
        ui->dateTimeEdit->setDateTime(task->getDeadline());
        ui->textEdit->setText(task->getText());
    }

    show();
}

void TaskEditor::setRetainSize()
{
    QSizePolicy sp_retain = this->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);//false 不占位隐藏
    setSizePolicy(sp_retain);
    hide();
}

void TaskEditor::setUi(Ui::MainWindow *ui)
{
    this->ui = ui; setRetainSize();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("确定"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));
}
