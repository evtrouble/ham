#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDateTime>
#include <QListView>
#include <QListWidgetItem>
#include <QLabel>
#include <QMessageBox>

#include "ui_mainwindow.h"
#include "taskitem.h"
#include "taskscontrol.h"

TasksControl::TasksControl(Ui::MainWindow* ui) : ui(ui)
{
    QFont ft;
    ft.setPointSize(14);
    this->ui->tasksDisplay->setFont(ft); //字体大小

    loadData();
    ui->listWidget->setSpacing(5);//间距

    ui->listWidget->adjustSize();
    for(int id = 0; id < tasks.size(); id++)
    {
        TaskItem* widget = new TaskItem(ui->listWidget);
        widget->bind(ui->listWidget->width(), this);
        widget->setData(tasks[id], id);
        widget->show();

        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(widget->width(), widget->height()));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, widget);
    }

    QSizePolicy sp_retain = ui->editor->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);//false 不占位隐藏
    ui->editor->setSizePolicy(sp_retain);
    ui->editor->hide();

    MyListWidget::connect(ui->listWidget, &MyListWidget::itemClicked, ui->listWidget, [=](QListWidgetItem *item){
        currentItem = item;
        if(item == nullptr)
        {
            // 取消选中
            ui->listWidget->clearSelection();
            ui->editor->hide();
            return;
        }

        ui->editor->show();
        TaskItem* taskItem = static_cast<TaskItem*>(ui->listWidget->itemWidget(item));
        ui->textEdit->setText(taskItem->text->text());
        ui->dateTimeEdit->setDateTime(tasks.at(taskItem->id).deadline);
    });//显示编辑页面

    QPushButton::connect(ui->confirmButton, &QPushButton::clicked, ui->textEdit, [=](){
        auto& list = ui->listWidget;
        if(currentItem == nullptr)//添加新代办
        {
            Task task(ui->textEdit->toPlainText(), ui->dateTimeEdit->text());
            tasks.append(task);

            ui->listWidget->adjustSize();
            TaskItem* widget = new TaskItem(ui->listWidget);
            widget->bind(ui->listWidget->width(), this);

            widget->setData(task, tasks.size() - 1);
            widget->show();

            QListWidgetItem* item = new QListWidgetItem;
            item->setSizeHint(QSize(widget->width(), widget->height()));
            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item, widget);

            ui->editor->hide();
        }
        else
        {
            TaskItem* taskItem = static_cast<TaskItem*>(list->itemWidget(currentItem));
            taskItem->setData(ui->textEdit->toPlainText());
            currentItem->setSizeHint(QSize(taskItem->width(), taskItem->height()));
            tasks[taskItem->id].setDeadline(ui->dateTimeEdit->dateTime());
        }
    });//确认修改

    QPushButton::connect(ui->cancelButton, &QPushButton::clicked, ui->textEdit, [=](){
        auto& list = ui->listWidget;
        if(currentItem == nullptr)//添加新代办
        {
            ui->textEdit->setText("");
            ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
        }
        else
        {
            TaskItem* taskItem = static_cast<TaskItem*>(list->itemWidget(currentItem));
            ui->textEdit->setText(taskItem->text->text());
            ui->dateTimeEdit->setDateTime(tasks.at(taskItem->id).deadline);
        }
    });//取消修改

    ui->addButton->setToolTip("添加新代办");
    QPushButton::connect(ui->addButton, &QPushButton::clicked, ui->textEdit, [=](){
        currentItem = nullptr;
        ui->editor->show();
        ui->textEdit->clear();
        ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    });//添加新代办
}

bool TasksControl::loadData()
{
    QFile file("./user.data");
    bool success = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!success)return success;

    QString value = file.readAll();
    file.close();

    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);

    if(parseJsonErr.error || !document.isArray())return false;

    QJsonObject task_file;
    const auto& arr = document.array();
    for(const auto& task : arr)
    {
        task_file = task.toObject();
        tasks.append(Task(task_file["content"].toString(), task_file["deadline"].toString(),
            task_file["finish"].toBool()));
    }

    return true;
}

bool TasksControl::writeData()
{
    for(int id = 0; id < ui->listWidget->count(); id++)
    {
        TaskItem* item = static_cast<TaskItem*>(ui->listWidget->itemWidget(ui->listWidget->item(id)));
        tasks[id].finish = item->checkBox->isChecked();
        tasks[id].content = item->text->text();
    }

    QJsonObject task_file;
    QJsonArray arr;

    for(auto& task : tasks)
    {
        task_file["content"] = task.content;
        task_file["deadline"] = task.deadline.toString("yyyy/M/d hh:mm");
        task_file["finish"] = task.finish;
        arr.append(task_file);
    }

    QFile file("./user.data");
    bool success = file.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate);
    if(!success)return success;

    QJsonDocument jsonDoc(arr);

    file.write(jsonDoc.toJson());
    file.close();
    return true;
}

void TasksControl::removeTask(int id)
{
    auto& list = ui->listWidget;
    TaskItem* item = static_cast<TaskItem*>(list->itemWidget(list->item(id)));
    int ret = QMessageBox::question(ui->listWidget, "是否删除该待办",
        "待办:" + item->text->text(),
        QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);

    if(ret == QMessageBox::Cancel)return;
    for(int i = id + 1; i < list->count(); i++)
    {
        static_cast<TaskItem*>(list->itemWidget(list->item(i)))->setId(i - 1);
    }

    if(list->item(id) == currentItem)ui->editor->hide();

    tasks.removeAt(id);
    item->deleteLater();
    list->removeItemWidget(list->item(id));
    delete list->takeItem(id);
}

TasksControl::~TasksControl()
{
    writeData();
}
