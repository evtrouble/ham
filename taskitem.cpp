#include "taskitem.h"

#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QFontMetrics>
#include <QPainterPath>

TaskItem::TaskItem(QWidget *parent) : QWidget(parent), deleteButton(new QPushButton(this))
{
    setAttribute(Qt::WA_StyledBackground);

    // 设置删除按钮样式
    deleteButton->setIcon(QIcon(":/more/img/delete.png"));
    deleteButton->setIconSize(QSize(20, 20));
    deleteButton->setStyleSheet(R"(
        QPushButton {
            border: none;
            background: transparent;
        }
        QPushButton:hover {
            background-color: rgba(239, 68, 68, 0.1);
            border-radius: 4px;
        }
    )");
    deleteButton->setCursor(Qt::PointingHandCursor);

    // 连接删除信号
    QPushButton::connect(deleteButton, &QPushButton::clicked, this, [=]{
        emit remove(item);
    });
}

void TaskItem::paintEvent(QPaintEvent* Event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 先绘制整体背景
    painter.fillRect(rect(), QColor(232, 245, 253));  // 使用淡蓝色填充整个背景


    // 绘制卡片背景
    QPainterPath path;
    path.addRoundedRect(QRectF(0, 0, width(), height()), 10, 10);
    painter.fillPath(path, QColor(255, 255, 255));


    checkBox->setGeometry(4, height() / 2 - 14, 28, 28);  // 调整整体大小为28x28
    checkBox->setStyleSheet(R"(
        QCheckBox {
            spacing: 0px;         // 将spacing改为0，去除额外间距
        }
        QCheckBox::indicator {
            width: 24px;          // 宽高保持一致
            height: 24px;         // 宽高保持一致
            border: 2px solid #E5E7EB;
            border-radius: 4px;
            background-color: white;
        }
        QCheckBox::indicator:checked {
            background-color: #3B82F6;
            border-color: #3B82F6;
            image: url(:/more/img/check.png);
        }
        QCheckBox::indicator:hover {
            border-color: #3B82F6;
        }
    )");

    checkBox->show();//选框

    if(checkBox->checkState() == Qt::Checked){
        text->setStyleSheet(R"(
            QLabel {
                color: #9CA3AF;
                text-decoration: line-through;
                font-family: "Microsoft YaHei UI";
                padding: 2px;
            }
        )");
        QColor color;
        color.setRgb(0x88, 0x88, 0x88);
        QPalette pal = text->palette();
        pal.setColor(QPalette::Text, color);
        text->setPalette(pal);
    }
    else {
        text->setStyleSheet(R"(
            QLabel {
                color: #1F2937;
                font-family: "Microsoft YaHei UI";
                padding: 4px;
            }
        )");
    }
    text->move(40, 3);
    text->show();//待办事项

    deleteButton->move(width() - 35, height() / 2 - 12);  // 从30改为35，让按钮往右移一点
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
    this->text->setWordWrap(true);

    this->text->setAttribute(Qt::WA_TransparentForMouseEvents, true);
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
    text->setWordWrap(true);

    text->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void TaskItem::setData(QDateTime &deadline, QString &text, int priority)
{
    this->deadline = deadline;
    this->priority = priority;
    setText(text);
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

void TaskItem::setWidth(int width)
{
    text->setFixedWidth(width - 70);  // 从50改为70，给右边留更多空间
    text->adjustSize();
    resize(width, text->height() + 5);
}
