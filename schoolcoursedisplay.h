// schoolcoursedisplay.h
#ifndef SCHOOLCOURSEDISPLAY_H
#define SCHOOLCOURSEDISPLAY_H

#include <QTableWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QDebug>
#include <QHeaderView>
#include "netdataaccess.h"
#include "qpushbutton.h"
#include "qlabel.h"
#include "qlayout.h"
class SchoolCourseDisplay : public QTableWidget {
    Q_OBJECT
public:
    static const int PAGE_SIZE = 10; // Number of rows per page
    int currentPage = 0;
    QJsonArray allCourses;  // Store all courses
    QPushButton *prevButton = nullptr;
    QPushButton *nextButton = nullptr;
    QLabel *pageLabel = nullptr;
    QHBoxLayout *paginationLayout;
    void setPageControls(QPushButton *prev, QPushButton *next, QLabel *label);
    void setupPagination();
    void updatePageDisplay();
    void showCurrentPage();
    explicit SchoolCourseDisplay(QWidget *parent = nullptr);
    void init();
    void performSearch(
        const int academicYear,
        const int semester,
        const QString& instructor,
        const QString& name,
        const QString& department,
        const int hasCapacity
        );
    bool event(QEvent *event) override;


private slots:
    void handleSearchResponse(QNetworkReply *reply);
    void nextPage();
    void previousPage();
private:
    void setupTable();
    void updateTableContent(const QJsonArray &courses);
    void clearTable();
    QString getTimeSlotString(int startSlot, int endSlot) const;
    QString formatTooltipContent(const QString &cellContent) const;

    const QStringList headerLabels = {
        "课程ID", "课程名", "课程教师", "课程地点",
        "学分", "周日", "周一", "周二",
        "周三", "周四", "周五", "周六"
    };
};

#endif // SCHOOLCOURSEDISPLAY_H
