#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H
#include <QListWidget>
#include <QMouseEvent>

class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    MyListWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:

};

#endif // MYLISTWIDGET_H
