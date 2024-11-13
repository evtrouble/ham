#include "personalcoursedisplay.h"

#include <QHeaderView>

PersonalCourseDisplay::PersonalCourseDisplay(QWidget *parent) : QTableWidget(parent)
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setMinimumSectionSize(80);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
