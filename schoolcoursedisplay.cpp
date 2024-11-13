#include "schoolcoursedisplay.h"

#include <QHeaderView>

SchoolCourseDisplay::SchoolCourseDisplay(QWidget *parent) : QTableWidget(parent)
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //verticalHeader()->setMinimumSectionSize(80);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
