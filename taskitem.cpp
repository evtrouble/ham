#include "taskitem.h"
#include "taskscontrol.h"

#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QFontMetrics>
#include <QPainterPath>
#include <QDebug>

TaskItem::TaskItem(QWidget *parent) : QWidget(parent), deleteButton(new QPushButton(this))
{
    this->setAttribute(Qt::WA_StyledBackground);
    deleteButton->setIcon(QIcon(":/more/img/delete.png"));
    deleteButton->setIconSize(QSize(20, 20));
    deleteButton->setStyleSheet("background-color: transparent; border: 0;");
    QPushButton::connect(deleteButton, &QPushButton::clicked, this, [=](){
        emit remove(id);
    });
}

void TaskItem::bind(int width, TasksControl* tasksControl)
{
    this->resize(width, 10);
    connect(this, &TaskItem::remove, [=](int id){
        tasksControl->removeTask(id);
    });
}

void TaskItem::paintEvent(QPaintEvent* Event)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::white));

    checkBox->setGeometry(5, this->height() / 2 - 14, 25, 25);
    checkBox->show();//选框

    if(checkBox->checkState() == Qt::Checked){
        text->setStyleSheet("color:Grey; text-decoration: line-through");
    } else text->setStyleSheet("color:White; text-decoration: none");
    text->move(30, 3);
    text->show();//待办事项

    deleteButton->move(this->width() - 22, this->height() / 2 - 12);
    deleteButton->show();//删除

    painter.drawLine(QPointF(0, this->height()), QPointF(this->width(), this->height()));
    QWidget::paintEvent(Event);
}

void TaskItem::setData(Task& task, int id)
{
    checkBox = new QCheckBox(this);
    if(task.finish)checkBox->setCheckState(Qt::Checked);

    text = new QLabel(task.content, this);
    text->setFixedWidth(this->width() - 30);
    text->setWordWrap(true);

    text->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    this->id = id;
    text->adjustSize();
    this->resize(this->width(), text->height() + 10);
}

void TaskItem::setData(QString &&s)
{
    text->setText(s);
    text->adjustSize();
    this->resize(this->width(), text->height() + 10);
}

bool TaskItem::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::Enter:
        this->setStyleSheet("background-color:#473C8B;");
        break;
    case QEvent::Leave:
        this->setStyleSheet("background-color:transparent;");
        break;
    default:
        break;
    }
    return QWidget::event(event);
}


