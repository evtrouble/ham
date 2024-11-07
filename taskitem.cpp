#include "taskitem.h"

#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QFontMetrics>
#include <QPainterPath>

TaskItem::TaskItem(QWidget *parent) : QWidget(parent), deleteButton(new QPushButton(this))
{
    setAttribute(Qt::WA_StyledBackground);
    deleteButton->setIcon(QIcon(":/more/img/delete.png"));
    deleteButton->setIconSize(QSize(20, 20));
    deleteButton->setStyleSheet("border: 0;");

    QPushButton::connect(deleteButton, &QPushButton::clicked, this, [=]{
        emit remove(item);
    });
}

void TaskItem::paintEvent(QPaintEvent* Event)
{
    QPainter painter(this);

    checkBox->setGeometry(0, height() / 2 - 14, 25, 25);
    checkBox->show();//选框

    if(checkBox->checkState() == Qt::Checked){
        text->setStyleSheet("text-decoration: line-through");

        QColor color;
        color.setRgb(0x88, 0x88, 0x88);
        QPalette pal = text->palette();
        pal.setColor(QPalette::Text, color);
        text->setPalette(pal);
    }
    else text->setStyleSheet("text-decoration: none");
    text->move(25, 3);
    text->show();//待办事项

    deleteButton->move(width() - 30, height() / 2 - 12);
    deleteButton->show();//删除

    painter.drawLine(QPointF(5, height()), QPointF(width() - 5, height()));
    QWidget::paintEvent(Event);
}

bool TaskItem::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::Enter:
        this->setStyleSheet("background-color:#84c4e2;");
        break;
    case QEvent::Leave:
        this->setStyleSheet("background-color:transparent;");
        break;
    default:
        break;
    }
    return QWidget::event(event);
}

void TaskItem::init(QDateTime &deadline, QString &text, int priority, QListWidgetItem* item)
{
    this->item = item;

    this->deadline = deadline;
    this->priority = priority;

    checkBox = new QCheckBox(this);

    setText(text);
    this->text->setFixedWidth(width() - 50);
    this->text->setWordWrap(true);

    this->text->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    this->text->adjustSize();
    resize(width(), this->text->height() + 5);
}

void TaskItem::init(const QJsonObject& json, QListWidgetItem* item)
{
    this->item = item;

    deadline = QDateTime::fromString(json["deadline"].toString(), "yyyy-MM-ddThh:mm:ss.zzzZ");

    priority = json["priority"].toInt();
    id = json["id"].toInt();
    checkBox = new QCheckBox(this);
    if(json["finish"].toBool()) checkBox->setCheckState(Qt::Checked);

    setText(json["content"].toString());
    text->setFixedWidth(width() - 50);
    text->setWordWrap(true);

    text->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    text->adjustSize();
    resize(width(), text->height() + 5);
}

void TaskItem::setData(QDateTime &deadline, QString &text, int priority)
{
    this->deadline = deadline;
    this->priority = priority;
    setText(text);

    this->text->adjustSize();
    resize(width(), this->text->height() + 5);
}

QJsonObject TaskItem::toJson()
{
    QJsonObject json;

    json["deadline"] = deadline.toString("yyyy-MM-ddThh:mm:ss.zzzZ");

    json["id"] = id;
    json["priority"] = priority;
    json["finish"] = (checkBox->checkState() == Qt::Checked);

    json["content"] = getText();
    return json;
}

void TaskItem::setText(const QString& text)
{
    QString prefix = "<font style = 'font-size:10px;'>" +
                     deadline.toString("yyyy-MM-dd hh:mm") + "截止</font> <br/>";
    for(int i = 0; i <= priority; i++)
    {
        prefix += '!';
    }
    prefix += ' ';
    prefixlen = prefix.length();
    if(this->text == nullptr) this->text = new QLabel(prefix + text, this);
    else this->text->setText(prefix + text);
}
