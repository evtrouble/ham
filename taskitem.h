#ifndef TASKITEM_H
#define TASKITEM_H

#include <QCheckBox>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QDateTime>
#include <QJsonObject>

class QListWidgetItem;

class TaskItem : public QWidget
{
    Q_OBJECT

public:
    TaskItem(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* Event) override;

    bool event(QEvent *event) override;

    void init(QDateTime &deadline, QString &text, int priority, QListWidgetItem* item);
    void init(const QJsonObject& json, QListWidgetItem* item);

    void setData(QDateTime &deadline, QString &text, int priority);
    void setWidth(int width) { resize(width, height()); }
    void setId(int id) { this->id = id; }

    QString getText() { return text->text().mid(prefixlen); }
    QDateTime &getDeadline() { return deadline; }
    int getPriority() { return priority; }

    QJsonObject toJson();

private:
    void setText(const QString& text);

private:
    QCheckBox* checkBox = nullptr;//是否完成
    QPushButton* deleteButton = nullptr;
    QDateTime deadline;//截止日期
    bool finish; //是否已完成
    int priority; //优先级 0最低
    QLabel* text = nullptr; //内容
    int id;
    int prefixlen = 0;

    QListWidgetItem *item = nullptr;

signals:
    void remove(QListWidgetItem*);
};

#endif // TASKITEM_H
