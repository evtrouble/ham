#include "coursecontrol.h"
#include "ui_hamsystem.h"
#include "personalcoursedisplay.h"
#include <QPushButton>
#include "ComboBoxManager.h"
#include <QJsonDocument>
#include <QJsonParseError>
CourseControl::CourseControl(Ui::MainWindow *ui) : ui(ui)
{
    ui->stackedWidget_2->setCurrentIndex(0);

    QPushButton::connect(ui->btnPersonalCourse, &QPushButton::clicked, ui->stackedWidget_2, [=]
                         { ui->stackedWidget_2->setCurrentIndex(0); }); // 个人课表

    QPushButton::connect(ui->btnSchoolCourse, &QPushButton::clicked, ui->stackedWidget_2, [=]
                         { ui->stackedWidget_2->setCurrentIndex(1); }); // 学校课表

    // 在 CourseControl 的构造函数中
    PersonalCourseDisplay::connect(ui->personalCourseTable, &PersonalCourseDisplay::initFinish, ui->weekSelect, [=]
                                   {
                                       // 临时阻止信号
                                       bool oldState = ui->weekSelect->blockSignals(true);
                                       ui->weekSelect->setCurrentIndex(ui->personalCourseTable->getCurrentWeek() - 1);
                                       ui->weekSelect->blockSignals(oldState);
                                   });


    QComboBox::connect(ui->weekSelect, &QComboBox::currentIndexChanged, ui->personalCourseTable, [=](int currentWeek)
                       {
                           ui->personalCourseTable->init(currentWeek + 1);
                       });


    // 查询按钮连接
    QPushButton::connect(ui->btnSearchCourse, &QPushButton::clicked, ui->schoolCourseTable, [=]() {
        qDebug() << "Search button clicked";  // 调试输出

        // 获取搜索条件
        int academicYear = ui->academicYearCombo->currentText().toInt();
        int semester = ui->semesterCombo->currentIndex();
        QString instructor = ui->instructorEdit->text();
        QString courseName = ui->courseNameEdit->text();
        QString department = ui->departmentCombo->currentText();
        QString text = ui->hasCapacityCombo->currentText();
        int hasCapacity;
        if (text == "请选择容量") {
            hasCapacity = -1;
        } else if (text == "有") {
            hasCapacity = 1;
        } else { // text == "无"
            hasCapacity = 0;
        }
        // 检查是否没有选择任何选项
        if (text.isEmpty()) {
            // 处理未选择的情况，例如设置为 false 或者其他逻辑
            hasCapacity = false;  // 默认值
        }


        // 执行搜索
        ui->schoolCourseTable->performSearch(
            academicYear,
            semester,
            instructor,
            courseName,
            department,
            hasCapacity
            );
    });
    setupWeekComboBox(ui->weekSelect);

}

// 保留原有init()方法以保持兼容性
void CourseControl::init()
{
    if (NetDataAccess::instance()->getJwt().isEmpty()) {
        // 未登录，不初始化个人课表
        return;
    }
    ui->personalCourseTable->init(-1);
    initWithoutCourse();
}
// void CourseControl::init()
// {
//     ui->personalCourseTable->init(-1);
//     ui->schoolCourseTable->init();

//     // 使用ComboBoxManager初始化所有下拉框
//     auto& manager = ComboBoxManager::instance();

//     // 初始化学年下拉框
//     manager.initializeComboBox(ui->academicYearCombo, ComboBoxType::AcademicYear);
//     // 初始化学期下拉框
//     manager.initializeComboBox(ui->semesterCombo, ComboBoxType::Semester);
//     manager.initializeComboBox(ui->departmentCombo, ComboBoxType::Department);
//     manager.initializeComboBox(ui->hasCapacityCombo, ComboBoxType::Capacity);
//     // 设置分页控件
//     ui->schoolCourseTable->setPageControls(
//         ui->prevButton,     // 前一页按钮
//         ui->nextButton,     // 后一页按钮
//         ui->pageLabel       // 页码标签
//         );


// }
void CourseControl::initWithoutCourse()
{
    ui->schoolCourseTable->init();

    // 初始化所有下拉框
    auto& manager = ComboBoxManager::instance();
    manager.initializeComboBox(ui->academicYearCombo, ComboBoxType::AcademicYear);
    manager.initializeComboBox(ui->semesterCombo, ComboBoxType::Semester);
    manager.initializeComboBox(ui->departmentCombo, ComboBoxType::Department);
    manager.initializeComboBox(ui->hasCapacityCombo, ComboBoxType::Capacity);

    // 设置分页控件
    ui->schoolCourseTable->setPageControls(
        ui->prevButton,
        ui->nextButton,
        ui->pageLabel
        );
}
// 如果需要添加自定义下拉框，可以这样做：
void CourseControl::initializeCustomComboBox()
{
    auto& manager = ComboBoxManager::instance();

    // 注册自定义初始化函数
    manager.registerCustomInitializer("CustomType", []() -> QList<ComboBoxConfig> {
        return {
            {"选项1", "value1", true},
            {"选项2", "value2", false},
            {"选项3", "value3", false}
        };
    });

    // 更新某个下拉框的数据
    QList<ComboBoxConfig> newData = {
        {"新选项1", "new1", true},
        {"新选项2", "new2", false}
    };
    manager.updateComboBoxData(ComboBoxType::Custom, newData);


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
    // 设置默认选中项，阻止信号
    bool oldState = comboBox->blockSignals(true);
    comboBox->setCurrentIndex(0);
    comboBox->blockSignals(oldState);}
