#ifndef PERSONALCOURSEDISPLAY_H
#define PERSONALCOURSEDISPLAY_H

#include <QTableWidget>

class PersonalCourseDisplay : public QTableWidget
{
    Q_OBJECT

public:
    PersonalCourseDisplay(QWidget *parent = nullptr);

    void setData(const QJsonObject& courses);//"data"
    void init(int week = -1);
    int getCurrentWeek() { return currentWeek; }

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVector<QString> colors{"#762E38", "#780C20", "#4C3778", "#133A7A", "#3D2302", "#786E01", "#646464"};
    void displayCourse(const QJsonArray& courses);

    //QString getWeekString();
signals:
    void initFinish();

private:
    int currentWeek = 0;
    bool once = false;
};

#endif // PERSONALCOURSEDISPLAY_H
