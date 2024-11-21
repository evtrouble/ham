#include "schoolcoursedisplay.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include<QEvent>
#include<QToolTip>
#include <QHelpEvent>


SchoolCourseDisplay::SchoolCourseDisplay(QWidget *parent)
    : QTableWidget(parent)
{
    setupTable();
    // 连接NetDataAccess的响应信号
    connect(&*NetDataAccess::instance(), &NetDataAccess::schoolCourseFinish,
            this, &SchoolCourseDisplay::handleSearchResponse);
}
bool SchoolCourseDisplay::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
        QPoint pos = helpEvent->pos();
        QTableWidgetItem *item = itemAt(pos);

        if (item && !item->text().isEmpty()) {
            // 只对星期几的单元格（第5列开始）显示工具提示
            int column = columnAt(pos.x());
            if (column >= 5) {
                QString tooltipText = formatTooltipContent(item->text());
                if (!tooltipText.isEmpty()) {
                    QToolTip::showText(helpEvent->globalPos(), tooltipText);
                } else {
                    QToolTip::hideText();
                }
            }
        } else {
            QToolTip::hideText();
        }
        return true;
    }
    return QTableWidget::event(event);
}

QString SchoolCourseDisplay::formatTooltipContent(const QString &cellContent) const
{
    if (cellContent.isEmpty()) {
        return QString();
    }

    // 分割多个时间段
    QStringList sections = cellContent.split("---------");
    QStringList formattedSections;

    for (const QString &section : sections) {
        if (section.trimmed().isEmpty()) continue;

        // 分析每个时间段的信息
        QStringList lines = section.trimmed().split('\n');
        if (lines.size() >= 4) {
            QString classroom = lines[0];
            QString timeSlot = lines[1];
            QString weeks = lines[2];
            QString weekType = lines[3];

            // 格式化显示
            QString formattedSection = QString(
                                           "<div style='margin-bottom: 5px;'>"
                                           "<b>教室：</b>%1<br>"
                                           "<b>时间：</b>%2<br>"
                                           "<b>周次：</b>%3<br>"
                                           "<b>类型：</b>%4"
                                           "</div>")
                                           .arg(classroom)
                                           .arg(timeSlot)
                                           .arg(weeks)
                                           .arg(weekType);

            formattedSections.append(formattedSection);
        }
    }

    // 如果有多个时间段，用分隔线分开
    return QString("<div style='color: black; background-color: white; padding: 5px;'>%1</div>")
        .arg(formattedSections.join("<hr style='margin: 5px 0;'>"));
}

void SchoolCourseDisplay::setupTable()
{
    setColumnCount(headerLabels.size());
    setHorizontalHeaderLabels(headerLabels);
    // 设置表格属性
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setAlternatingRowColors(true);
}

void SchoolCourseDisplay::setPageControls(QPushButton *prev, QPushButton *next, QLabel *label)
{
    prevButton = prev;
    nextButton = next;
    pageLabel = label;

    // 连接信号和槽
    connect(prevButton, &QPushButton::clicked, this, &SchoolCourseDisplay::previousPage);
    connect(nextButton, &QPushButton::clicked, this, &SchoolCourseDisplay::nextPage);

    // 初始化页码显示
    updatePageDisplay();
}
void SchoolCourseDisplay::updateTableContent(const QJsonArray &courses)
{
    allCourses = courses;  // Store all courses
    currentPage = 0;      // Reset to first page
    showCurrentPage();    // Show first page of results
    updatePageDisplay();  // Update pagination controls
}
void SchoolCourseDisplay::showCurrentPage()
{
    clearTable();

    int startIndex = currentPage * PAGE_SIZE;
    int endIndex = qMin(startIndex + PAGE_SIZE, allCourses.size());
    int rowCount = endIndex - startIndex;

    setRowCount(rowCount);

    for(int i = 0; i < rowCount; ++i) {
        QJsonObject course = allCourses[startIndex + i].toObject();
        QJsonArray schedules = course["schedules"].toArray();

        // 设置基本课程信息
        setItem(i, 0, new QTableWidgetItem(course["courseId"].toString()));
        setItem(i, 1, new QTableWidgetItem(course["name"].toString()));
        setItem(i, 2, new QTableWidgetItem(course["instructor"].toString()));
        setItem(i, 3, new QTableWidgetItem(""));  // 课程地点待填充
        setItem(i, 4, new QTableWidgetItem(QString::number(course["credit"].toDouble())));

        // 初始化周一到周日的单元格
        for(int day = 0; day < 7; day++) {
            setItem(i, 5 + day, new QTableWidgetItem(""));
        }

        // 处理每个时间段
        QString allClassrooms;  // 用于收集所有教室信息
        for(const QJsonValue &scheduleValue : schedules) {
            QJsonObject schedule = scheduleValue.toObject();
            int dayOfWeek = schedule["dayOfWeek"].toInt();
            QString classroom = schedule["classroom"].toString();

            // 收集教室信息
            if(!allClassrooms.contains(classroom)) {
                if(!allClassrooms.isEmpty()) {
                    allClassrooms += ", ";
                }
                allClassrooms += classroom;
            }

            // 构建时间信息字符串
            QString timeInfo = QString("%1\n%2\n%3-%4周\n%5")
                                   .arg(classroom, getTimeSlotString(schedule["startSlot"].toInt(), schedule["endSlot"].toInt()),
                                   schedule["weekStart"].toString(), schedule["weekEnd"].toString(),
                                   schedule["weekType"].toString() == "all" ? "每周" :
                                            schedule["weekType"].toString() == "odd" ? "单周" : "双周");

            // 更新对应星期的单元格
            QTableWidgetItem *tableItem = item(i, 5 + dayOfWeek);
            if(tableItem) {
                QString currentContent = tableItem->text();
                if(!currentContent.isEmpty()) {
                    currentContent += "\n---------\n";  // 添加分隔线
                }
                tableItem->setText(currentContent + timeInfo);
                tableItem->setTextAlignment(Qt::AlignLeft | Qt::AlignTop);
            }
        }

        // 更新教室列
        if(item(i, 3)) {
            item(i, 3)->setText(allClassrooms);
        }

        // 设置所有单元格自动换行和对齐方式
        for(int col = 0; col < columnCount(); col++) {
            if(item(i, col)) {
                item(i, col)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                if(QTableWidgetItem *tableItem = item(i, col)) {
                    // 启用工具提示
                    tableItem->setToolTip("");  // 设置空工具提示以启用工具提示事件
                }
            }
        }
    }

    // 自动调整行高
    for(int i = 0; i < rowCount; i++) {
        resizeRowToContents(i);
    }
}

void SchoolCourseDisplay::updatePageDisplay()
{
    int totalPages = (allCourses.size() + PAGE_SIZE - 1) / PAGE_SIZE;
    pageLabel->setText(QString("第 %1/%2 页").arg(currentPage + 1).arg(qMax(1, totalPages)));

    prevButton->setEnabled(currentPage > 0);
    nextButton->setEnabled(currentPage < totalPages - 1);
}

void SchoolCourseDisplay::nextPage()
{
    int totalPages = (allCourses.size() + PAGE_SIZE - 1) / PAGE_SIZE;
    if (currentPage < totalPages - 1) {
        currentPage++;
        showCurrentPage();
        updatePageDisplay();
    }
}
void SchoolCourseDisplay::previousPage()
{
    if (currentPage > 0) {
        currentPage--;
        showCurrentPage();
        updatePageDisplay();
    }
}
void SchoolCourseDisplay::init()
{
    clearTable();
}

void SchoolCourseDisplay::performSearch(
    const int academicYear,
    const int semester,
    const QString& instructor,
    const QString& name,
    const QString& department,
    const int hasCapacity
    )
{
    qDebug()<<"hasCapacity"<<" "<<hasCapacity;
    // Get combobox values but don't pass them if they are default values
    NetDataAccess::instance()->searchCourse(
        academicYear,  // Will only be passed if != -1
        semester,      // Will only be passed if != -1
        instructor.trimmed(),
        name.trimmed(),
        department.trimmed(),
        hasCapacity
        );
}

void SchoolCourseDisplay::handleSearchResponse(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();

        if(obj["success"].toBool()) {
            QJsonArray courses = obj["data"].toObject()["courses"].toArray();
            updateTableContent(courses);
        } else {
            qDebug() << "Search failed:" << obj["error"].toString();
        }
    }

    reply->deleteLater();
}



void SchoolCourseDisplay::clearTable()
{
    setRowCount(0);
}

QString SchoolCourseDisplay::getTimeSlotString(int startSlot, int endSlot) const
{
    QStringList timeSlots = {
        "08:00", "08:50", "09:50", "10:40",
        "13:30", "14:20", "15:20", "16:10",
        "18:30", "19:20", "20:20", "21:10"
    };

    if(startSlot >= 1 && startSlot <= timeSlots.size() &&
        endSlot >= 1 && endSlot <= timeSlots.size() &&
        startSlot <= endSlot) {
        return QString("%1-%2").arg(timeSlots[startSlot-1], timeSlots[endSlot-1]);
    }

    return "";
}
