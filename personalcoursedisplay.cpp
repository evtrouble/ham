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

PersonalCourseDisplay::PersonalCourseDisplay(QWidget *parent) : QTableWidget(parent), courses_(MAX_DAY * MAX_TIME)
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setMinimumSectionSize(80);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 设置表格样式
    setStyleSheet(
        "QTableWidget { background-color: white; border: none; }"
        "QHeaderView::section { "
        "background-color: #f8f9fa;"
        "padding: 6px;"
        "border: none;"
        "font-weight: bold;"
        "color: #495057;"
        "}");
    // 设置更现代的配色方案
    colors = {
        "#E3F2FD", // 浅蓝
        "#F3E5F5", // 浅紫
        "#E8F5E9", // 浅绿
        "#FFF3E0", // 浅橙
        "#F3E5F5", // 浅粉
        "#E0F7FA", // 浅青
        "#FBE9E7", // 浅红
        "#F1F8E9"  // 浅黄绿
    };
    setMouseTracking(true);
}

void PersonalCourseDisplay::setData(const QJsonObject &data)
{
    QJsonObject innerData = data["data"].toObject(); // 获取 data 对象
    currentWeek = innerData["week"].toInt();         // 从 innerData 获取 week 值

    displayCourse(innerData["courses"].toArray()); // 从 innerData 获取 courses 数组
}

void PersonalCourseDisplay::displayCourse(const QJsonArray &coursesArray)
{
    clearContents();
    courses_.clear();
    courses_.resize(MAX_DAY * MAX_TIME);

    // 初始化所有单元格
    for (int i = 0; i < rowCount(); ++i)
    {
        for (int j = 0; j < columnCount(); ++j)
        {
            if (!item(i, j))
            {
                setItem(i, j, new QTableWidgetItem());
            }
            item(i, j)->setTextAlignment(Qt::AlignCenter);
            item(i, j)->setBackground(QColor("#ffffff"));
        }
    }

    // 课程颜色映射
    QMap<QString, QString> courseColors;
    int colorIndex = 0;

    for (const auto &courseValue : coursesArray)
    {
        QJsonObject courseObj = courseValue.toObject();

        // 获取课程基本信息
        QString courseId = courseObj["courseId"].toString();
        QString name = courseObj["name"].toString();
        QString instructor = courseObj["instructor"].toString();
        int credit = courseObj["credit"].toInt();

        // 为课程分配固定颜色
        if (!courseColors.contains(courseId))
        {
            courseColors[courseId] = colors[colorIndex % colors.size()];
            colorIndex++;
        }
        QString courseColor = courseColors[courseId];

        // 处理多个时间安排
        QJsonArray schedules = courseObj["schedules"].toArray();
        for (const auto &scheduleValue : schedules)
        {
            QJsonObject schedule = scheduleValue.toObject();

            int dayOfWeek = schedule["dayOfWeek"].toInt();
            int startSlot = schedule["startSlot"].toInt() - 1;
            int endSlot = schedule["endSlot"].toInt();
            int weekStart = schedule["weekStart"].toInt();
            int weekEnd = schedule["weekEnd"].toInt();
            QString weekTypeStr = schedule["weekType"].toString();
            QString classroom = schedule["classroom"].toString();
            // 创建课程对象
            Course course;
            course.courseId = courseId;
            course.name = name;
            course.instructor = instructor;
            course.credit = credit;
            course.classroom = classroom;
            course.dayOfWeek = dayOfWeek;
            course.startSlot = startSlot;
            course.weekStart = weekStart;
            course.weekEnd = weekEnd;
            course.slotInterval = endSlot - startSlot;

            // 设置周类型
            switch (weekTypeStr.at(0).toLatin1())
            {
            case 'a':
                course.weekType = WeekType::ALL;
                break;
            case 'o':
                course.weekType = WeekType::ODD;
                break;
            case 'e':
                course.weekType = WeekType::EVEN;
                break;
            default:
                break;
            }

            // 保存课程信息
            int index = dayOfWeek * MAX_TIME + startSlot;
            courses_[index] = course;

            // 合并单元格
            setSpan(startSlot, dayOfWeek, course.slotInterval, 1);

            // 创建并设置单元格
            auto tableItem = item(startSlot, dayOfWeek);
            if (!tableItem)
            {
                tableItem = new QTableWidgetItem();
                setItem(startSlot, dayOfWeek, tableItem);
            }

            // 设置字体
            QFont font = tableItem->font();
            font.setPointSize(9);
            tableItem->setFont(font);

            // 设置背景色
            tableItem->setBackground(QColor(courseColor));
            // 设置显示文本
            QString displayText = QString("%1\n%2\n%3")
                                      .arg(name)
                                      .arg(classroom)
                                      .arg(instructor);
            tableItem->setText(displayText);

            // 设置工具提示
            QString weekType;
            switch (course.weekType)
            {
            case WeekType::ALL:
                weekType = "每周";
                break;
            case WeekType::ODD:
                weekType = "单周";
                break;
            case WeekType::EVEN:
                weekType = "双周";
                break;
            }

            QString tooltipText = QString(
                                      "课程：%1\n"
                                      "教室：%2\n"
                                      "教师：%3\n"
                                      "周次：%4-%5周 (%6)\n"
                                      "学分：%7")
                                      .arg(name)
                                      .arg(classroom)
                                      .arg(instructor)
                                      .arg(course.weekStart)
                                      .arg(course.weekEnd)
                                      .arg(weekType)
                                      .arg(credit);

            tableItem->setToolTip(tooltipText);
        }
    }
}

void PersonalCourseDisplay::init(int week)
{
    NetDataAccess::instance()->getPersonalCourse(week);

    NetDataAccess::connect(NetDataAccess::instance().get(), &NetDataAccess::finish, this, [=](QNetworkReply *reply)
                           {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonParseError parseJsonErr;
            QJsonDocument document = QJsonDocument::fromJson(data, &parseJsonErr);

            if(parseJsonErr.error == QJsonParseError::NoError && document.isObject()) {
                setData(document.object());
            }
        } else {
            QMessageBox::critical(this, "Network error!", reply->errorString());
        }

        reply->deleteLater();
        if(week == -1) emit initFinish();
        NetDataAccess::disconnect(NetDataAccess::instance().get(), &NetDataAccess::finish, this, 0); });
}

void PersonalCourseDisplay::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        auto temp = itemAt(event->pos());
        if (temp != nullptr)
        {
            QMessageBox::about(this, "课程详细信息", courses_[temp->column() * MAX_TIME + temp->row()].toString());
        }
    }
    QTableWidget::mouseDoubleClickEvent(event);
}

Course &PersonalCourseDisplay::setCourseItem(const QJsonObject &course)
{
    const auto &schedule = course["schedules"];

    int i = schedule["startSlot"].toInt() - 1;
    int j = schedule["dayOfWeek"].toInt();
    auto &course_ = courses_[j * MAX_TIME + i];

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

    switch (schedule["weekType"].toString().at(0).toLatin1())
    {
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
