#ifndef PERSONALCOURSEDISPLAY_H
#define PERSONALCOURSEDISPLAY_H

#include <QTableWidget>

enum class WeekType
{
    ALL,
    ODD,
    EVEN
};

static QString dayStrings[] = {"星期天", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};

struct Course
{
    QString courseId, name, instructor;
    int credit;
    int dayOfWeek, startSlot, slotInterval;
    QString classroom;
    int weekStart, weekEnd;
    WeekType weekType;

    QString toString()
    {
        QString text = "课程名：" + name + "\n";
        text += "课程id:" + courseId + "\n";
        text += "学分:" + QString::number(credit) + "\n";
        text += "课程教师" + instructor + "\n";
        text += "课程地点" + classroom + "\n";

        text += "课程时间：" + QString::number(weekStart) + "-" + QString::number(weekEnd) + "周，";//周数
        switch (weekType) {
        case WeekType::ALL:
            break;
        case WeekType::ODD:
            text += "单周，";
            break;
        case WeekType::EVEN:
            text += "双周，";
            break;
        default:
            break;
        }

        text += dayStrings[dayOfWeek] + "，" + QString::number(startSlot + 1) + "-" + QString::number(slotInterval + startSlot) + "节";
        return text;
    }

    QString toSimpleString()
    {
        QString text = name + "<br/>";
        text += "<font style = 'font-size:10px;'>" +
                QString::number(weekStart) + "-" + QString::number(weekEnd) + "周，";//周数
        switch (weekType) {
        case WeekType::ALL:
            break;
        case WeekType::ODD:
            text += "单周，";
            break;
        case WeekType::EVEN:
            text += "双周，";
            break;
        default:
            break;
        }
        text += QString::number(slotInterval) + "，" + classroom + "</font> <br/>";
        return text;
    }
};

class PersonalCourseDisplay : public QTableWidget
{
    Q_OBJECT

    constexpr static int MAX_DAY = 7;
    constexpr static int MAX_TIME = 12;

public:
    PersonalCourseDisplay(QWidget *parent = nullptr);

    void setData(const QJsonObject& courses);//"data"
    void init(int week = -1);
    int getCurrentWeek() { return currentWeek; }

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QVector<QString> colors{"#762E38", "#780C20", "#4C3778", "#133A7A", "#3D2302", "#786E01", "#646464"};
    void displayCourse(const QJsonArray& courses);
    Course& setCourseItem(const QJsonObject& course);

signals:
    void initFinish();

private:
    int currentWeek = 0;
    bool once = false;
    QVector<Course> courses;
};

#endif // PERSONALCOURSEDISPLAY_H
