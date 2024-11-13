#include "personalcoursedisplay.h"
#include "netdataaccess.h"

#include <QHeaderView>
#include <QJsonObject>
#include <QJsonArray>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonParseError>
#include <QMouseEvent>
#include <QMessageBox>

PersonalCourseDisplay::PersonalCourseDisplay(QWidget *parent) : QTableWidget(parent), courses(MAX_DAY * MAX_TIME)
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setMinimumSectionSize(80);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void PersonalCourseDisplay::setData(const QJsonObject& data)
{
    currentWeek = data["week"].toInt();
    displayCourse(data["courses"].toArray());
}

void PersonalCourseDisplay::displayCourse(const QJsonArray& courses)
{
    clearContents();
    for(const auto& course : courses)
    {
        auto& course_ = setCourseItem(course.toObject());
        const QStringView& color = colors[QRandomGenerator::global()->bounded(colors.size())];

        setSpan(course_.startSlot, course_.dayOfWeek, course_.slotInterval, 1);

        const auto& temp = item(course_.startSlot, course_.dayOfWeek);
        temp->setBackground(QColor(color.mid(1, 2).toInt(nullptr, 16),
                    color.mid(3, 2).toInt(nullptr, 16), color.mid(5, 2).toInt(nullptr, 16)));
        temp->setText(course_.toSimpleString());
    }
}

void PersonalCourseDisplay::init(int week)
{
    //bool success = NetDataAccess::instance()->loadData(value);
    NetDataAccess::instance()->getPersonalCourse(week);

    NetDataAccess::connect(NetDataAccess::instance().get(), &NetDataAccess::finish, this, [=](QNetworkReply* reply){
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonParseError parseJsonErr;
            QJsonDocument document = QJsonDocument::fromJson(data, &parseJsonErr);

            if(parseJsonErr.error == QJsonParseError::NoError && document.isObject())
            {
                setData(document.object());
            }
        } else {
            QMessageBox::critical(this, "Network error!", reply->errorString());
        }
        reply->deleteLater();
        if(week == -1)emit initFinish();
        NetDataAccess::disconnect(NetDataAccess::instance().get(), &NetDataAccess::finish, this, 0);
    });
}

void PersonalCourseDisplay::mousePressEvent(QMouseEvent *event)
{
    auto temp = itemAt(event->pos());
    if(temp != nullptr)
    {
        QMessageBox::about(this, "课程详细信息", courses[temp->column() * MAX_TIME + temp->row()].toString());
    }
    QTableWidget::mousePressEvent(event);
}

Course& PersonalCourseDisplay::setCourseItem(const QJsonObject& course)
{
    const auto& schedule = course["schedules"];
    int i = schedule["startSlot"].toInt() - 1;
    int j = schedule["dayOfWeek"].toInt();
    auto& course_ = courses[j * MAX_TIME + i];

    course_.courseId = course["courseId"].toString();
    course_.name = course["name"].toString();
    course_.instructor = course["instructor"].toString();
    course_.credit = course["credit"].toInt();
    course_.dayOfWeek = j;
    course_.weekStart = course["weekStart"].toInt();
    course_.weekEnd = course["weekEnd"].toInt();
    course_.slotInterval = course["endSlot"].toInt() - i;
    course_.startSlot = course["startSlot"].toInt();
    course_.classroom = course["classroom"].toString();

    switch (schedule["weekType"].toString().at(0).toLatin1()) {
    case 'a':
        course_.weekType = WeekType::ALL;
        break;
    case 'o':
        course_.weekType = WeekType::ODD;
        break;
    case 'e':
        course_.weekType = WeekType::EVEN;
        break;
    default:
        break;
    }

    return course_;
}
