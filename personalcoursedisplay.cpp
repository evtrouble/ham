#include "personalcoursedisplay.h"
#include "netdataaccess.h"

#include <QHeaderView>
#include <QJsonObject>
#include <QJsonArray>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonParseError>

PersonalCourseDisplay::PersonalCourseDisplay(QWidget *parent) : QTableWidget(parent)
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
    //"courseId": "CS101",
    // "name": "计算机导论",
    //          "instructor": "张教授",
    //                         "credit": 3,
    //                         "schedules": [
    //                                           {
    //                                               "dayOfWeek": 1,
    //                                               "startSlot": 1,
    //                                               "endSlot": 2,
    //                                               "classroom": "教学楼101",
    //                                               "weekStart": 1,
    //                                               "weekEnd": 16,
    //                                               "weekType": "all"
    //                                           }
    // ]
    clearContents();
    for(const auto& course : courses)
    {
        const auto& obj = course.toObject();
        const auto& schedule = obj["schedules"];

        QString text = obj["name"].toString() + "<br/>";
        int i = schedule["startSlot"].toInt() - 1;
        int i_end = schedule["endSlot"].toInt();
        int j = schedule["dayOfWeek"].toInt();
        setSpan(i, j, i_end - i, 1);
        const QStringView& color = colors[QRandomGenerator::global()->bounded(colors.size())];
        item(i, j)->setBackground(QColor(color.mid(1, 2).toInt(nullptr, 16),
                                         color.mid(3, 2).toInt(nullptr, 16), color.mid(5, 2).toInt(nullptr, 16)));
        text += "<font style = 'font-size:10px;'>" +
                schedule["weekStart"].toString() + "-" + schedule["weekEnd"].toString() + "周, ";//周数
        switch (schedule["weekType"].toString().at(0).toLatin1()) {
        case 'a':
            break;
        case 'o':
            text += "单周, ";
            break;
        case 'e':
            text += "双周, ";
            break;
        default:
            break;
        }
        text += QString::number(i_end - i) + ", " + schedule["classroom"].toString() + "</font> <br/>";
        item(i, j)->setText(text);
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
    QTableWidget::mousePressEvent(event);
}
