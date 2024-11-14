#include "coursecontrol.h"
#include "ui_mainwindow.h"
#include "personalcoursedisplay.h"
#include <QPushButton>

CourseControl::CourseControl(Ui::MainWindow *ui) : ui(ui)
{
    ui->stackedWidget_2->setCurrentIndex(0);
    // ui->weekSelect = new WeekSelector();

    QPushButton::connect(ui->btnPersonalCourse, &QPushButton::clicked, ui->stackedWidget_2, [=]
                         { ui->stackedWidget_2->setCurrentIndex(0); }); // 个人课表

    QPushButton::connect(ui->btnSchoolCourse, &QPushButton::clicked, ui->stackedWidget_2, [=]
                         { ui->stackedWidget_2->setCurrentIndex(1); }); // 学校课表

    PersonalCourseDisplay::connect(ui->personalCourseTable, &PersonalCourseDisplay::initFinish, ui->weekSelect, [=]
                                   { ui->weekSelect->setCurrentIndex(ui->personalCourseTable->getCurrentWeek()); }); // 个人课表切换周数

    QComboBox::connect(ui->weekSelect, &QComboBox::currentIndexChanged, ui->personalCourseTable, [=](int currentWeek)
                       { ui->personalCourseTable->init(currentWeek); }); // 课程切换
    setupWeekComboBox(ui->weekSelect);
}

void CourseControl::init()
{
    ui->personalCourseTable->init();
}
void CourseControl::setupWeekComboBox(QComboBox *comboBox)
{
    comboBox->clear();

    // 设置字体
    QFont font = comboBox->font();
    font.setFamily("Microsoft YaHei");                   // 使用微软雅黑
    font.setPixelSize(14);                               // 使用像素大小而不是点大小
    font.setHintingPreference(QFont::PreferFullHinting); // 完整字体微调
    comboBox->setFont(font);

    // 设置样式和最小宽度
    comboBox->setMinimumWidth(120);
    comboBox->setStyleSheet(
        "QComboBox {"
        "    padding: 5px 10px;"
        "    border: 1px solid #ccc;"
        "    border-radius: 4px;"
        "    background: white;"
        "}"
        // 下拉按钮区域
        "QComboBox::drop-down {"
        "    border: none;"
        "    width: 24px;"
        "    border-top-right-radius: 8px;" // 匹配主体圆角
        "    border-bottom-right-radius: 8px;"
        "}"
        "QComboBox::down-arrow {"
        "    image: url(:/icon/img/down-arrow.png);"
        "    width: 12px;"
        "    height: 12px;"
        "}"
        // 下拉列表样式
        "QComboBox QAbstractItemView {"
        "    border: 1px solid #e0e0e0;"
        "    border-radius: 8px;"
        "    padding: 4px;"
        "    margin-top: 4px;" // 添加一点顶部间距
        "    background-color: white;"
        "    selection-background-color: #f0f7ff;" // 非常柔和的蓝色作为选中背景
        "    selection-color: #4a90e2;"            // 选中项的文字颜色
        "    outline: none;"
        "}");

    // 填充周数
    const int totalWeeks = 20; // 根据实际情况调整总周数
    for (int i = 1; i <= totalWeeks; ++i)
    {
        QString weekText = QString("第%1周").arg(i);
        comboBox->addItem(weekText);
    }

    // 设置默认选中项
    comboBox->setCurrentIndex(0);
}
