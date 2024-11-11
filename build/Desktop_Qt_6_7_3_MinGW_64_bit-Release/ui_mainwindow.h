/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "taskdisplay.h"
#include "taskeditor.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QToolButton *tasksButton;
    QToolButton *classButton;
    QToolButton *homeButton;
    QToolButton *settingsButton;
    QStackedWidget *stackedWidget;
    QWidget *home;
    QVBoxLayout *verticalLayout_6;
    QFrame *frame_6;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *exportLogBtn;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *verticalSpacer_12;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *changePasswordBtn;
    QSpacerItem *horizontalSpacer_11;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_10;
    QLabel *userImageDisplay;
    QLabel *usernameDisplay;
    QSpacerItem *horizontalSpacer_16;
    QSpacerItem *verticalSpacer_11;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *logoutBtn;
    QSpacerItem *horizontalSpacer_12;
    QWidget *timetable;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btnPersonalCourse;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *btnSchoolCourse;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget_2;
    QWidget *PersonalCourse;
    QWidget *SchoolCourse;
    QWidget *tasks;
    QGridLayout *gridLayout_6;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout_7;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *tasksDisplay;
    QPushButton *addButton;
    QSpacerItem *verticalSpacer_1;
    QHBoxLayout *horizontalLayout_1;
    QSpacerItem *horizontalSpacer_1;
    QPushButton *sortByDeadlineBtn;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *sortByPriorityBtn;
    QSpacerItem *horizontalSpacer_6;
    TaskDisplay *listWidget;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QSpacerItem *horizontalSpacer_3;
    TaskEditor *editor;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_4;
    QTextEdit *textEdit;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QDateTimeEdit *dateTimeEdit;
    QSpacerItem *verticalSpacer_7;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *horizontalSpacer_4;
    QWidget *setting;
    QGridLayout *gridLayout_4;
    QLabel *settingsDisplay;
    QWidget *login;
    QGridLayout *gridLayout_8;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_7;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *usernameEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLineEdit *passwordEdit;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_18;
    QLabel *label_7;
    QPushButton *registerBtn;
    QSpacerItem *horizontalSpacer_17;
    QDialogButtonBox *buttonBox_2;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *horizontalSpacer_8;
    QToolBar *tab;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(799, 573);
        MainWindow->setMinimumSize(QSize(600, 0));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/img/icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(300, 0));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tasksButton = new QToolButton(centralwidget);
        tasksButton->setObjectName("tasksButton");
        tasksButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 0;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/tab/img/tasks.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tasksButton->setIcon(icon1);
        tasksButton->setIconSize(QSize(30, 30));
        tasksButton->setAutoExclusive(true);
        tasksButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(tasksButton, 0, 0, 1, 1);

        classButton = new QToolButton(centralwidget);
        classButton->setObjectName("classButton");
        classButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 0;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/tab/img/class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        classButton->setIcon(icon2);
        classButton->setIconSize(QSize(30, 30));
        classButton->setAutoExclusive(true);
        classButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(classButton, 0, 1, 1, 1);

        homeButton = new QToolButton(centralwidget);
        homeButton->setObjectName("homeButton");
        homeButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 0;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/tab/img/home.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        homeButton->setIcon(icon3);
        homeButton->setIconSize(QSize(30, 30));
        homeButton->setAutoExclusive(true);
        homeButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(homeButton, 0, 2, 1, 1);

        settingsButton = new QToolButton(centralwidget);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 0;"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/tab/img/settings.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        settingsButton->setIcon(icon4);
        settingsButton->setIconSize(QSize(30, 30));
        settingsButton->setAutoExclusive(true);
        settingsButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(settingsButton, 0, 3, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(300, 0));
        home = new QWidget();
        home->setObjectName("home");
        verticalLayout_6 = new QVBoxLayout(home);
        verticalLayout_6->setObjectName("verticalLayout_6");
        frame_6 = new QFrame(home);
        frame_6->setObjectName("frame_6");
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_3 = new QGridLayout(frame_6);
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_14);

        exportLogBtn = new QPushButton(frame_6);
        exportLogBtn->setObjectName("exportLogBtn");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(exportLogBtn->sizePolicy().hasHeightForWidth());
        exportLogBtn->setSizePolicy(sizePolicy1);
        exportLogBtn->setMinimumSize(QSize(0, 30));
        exportLogBtn->setStyleSheet(QString::fromUtf8("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;font-size: 20px;}\n"
"QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}\n"
"QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}"));
        exportLogBtn->setFlat(false);

        horizontalLayout_12->addWidget(exportLogBtn);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_15);


        gridLayout_3->addLayout(horizontalLayout_12, 2, 0, 1, 1);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(verticalSpacer_12, 5, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_10);

        changePasswordBtn = new QPushButton(frame_6);
        changePasswordBtn->setObjectName("changePasswordBtn");
        sizePolicy1.setHeightForWidth(changePasswordBtn->sizePolicy().hasHeightForWidth());
        changePasswordBtn->setSizePolicy(sizePolicy1);
        changePasswordBtn->setMinimumSize(QSize(0, 30));
        changePasswordBtn->setStyleSheet(QString::fromUtf8("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;font-size: 20px;}\n"
"QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}\n"
"QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}"));
        changePasswordBtn->setFlat(false);

        horizontalLayout_11->addWidget(changePasswordBtn);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);


        gridLayout_3->addLayout(horizontalLayout_11, 4, 0, 1, 1);

        frame_7 = new QFrame(frame_6);
        frame_7->setObjectName("frame_7");
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_10 = new QHBoxLayout(frame_7);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        userImageDisplay = new QLabel(frame_7);
        userImageDisplay->setObjectName("userImageDisplay");
        userImageDisplay->setMinimumSize(QSize(80, 80));
        userImageDisplay->setTextFormat(Qt::TextFormat::AutoText);
        userImageDisplay->setScaledContents(false);

        horizontalLayout_10->addWidget(userImageDisplay);

        usernameDisplay = new QLabel(frame_7);
        usernameDisplay->setObjectName("usernameDisplay");
        usernameDisplay->setStyleSheet(QString::fromUtf8("font-size:20px;"));

        horizontalLayout_10->addWidget(usernameDisplay);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_16);


        gridLayout_3->addWidget(frame_7, 0, 0, 1, 1);

        verticalSpacer_11 = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        gridLayout_3->addItem(verticalSpacer_11, 3, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);

        logoutBtn = new QPushButton(frame_6);
        logoutBtn->setObjectName("logoutBtn");
        logoutBtn->setMinimumSize(QSize(0, 30));
        logoutBtn->setStyleSheet(QString::fromUtf8("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;background-color:red;font-size: 20px;}\n"
"QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}\n"
"QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}"));

        horizontalLayout_8->addWidget(logoutBtn);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_12);


        gridLayout_3->addLayout(horizontalLayout_8, 8, 0, 1, 1);


        verticalLayout_6->addWidget(frame_6);

        stackedWidget->addWidget(home);
        timetable = new QWidget();
        timetable->setObjectName("timetable");
        horizontalLayoutWidget = new QWidget(timetable);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(120, 20, 351, 51));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        btnPersonalCourse = new QPushButton(horizontalLayoutWidget);
        btnPersonalCourse->setObjectName("btnPersonalCourse");

        horizontalLayout_7->addWidget(btnPersonalCourse);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        btnSchoolCourse = new QPushButton(horizontalLayoutWidget);
        btnSchoolCourse->setObjectName("btnSchoolCourse");

        horizontalLayout_7->addWidget(btnSchoolCourse);

        verticalLayoutWidget = new QWidget(timetable);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(-1, 69, 621, 321));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget_2 = new QStackedWidget(verticalLayoutWidget);
        stackedWidget_2->setObjectName("stackedWidget_2");
        PersonalCourse = new QWidget();
        PersonalCourse->setObjectName("PersonalCourse");
        stackedWidget_2->addWidget(PersonalCourse);
        SchoolCourse = new QWidget();
        SchoolCourse->setObjectName("SchoolCourse");
        stackedWidget_2->addWidget(SchoolCourse);

        verticalLayout->addWidget(stackedWidget_2);

        stackedWidget->addWidget(timetable);
        tasks = new QWidget();
        tasks->setObjectName("tasks");
        sizePolicy.setHeightForWidth(tasks->sizePolicy().hasHeightForWidth());
        tasks->setSizePolicy(sizePolicy);
        gridLayout_6 = new QGridLayout(tasks);
        gridLayout_6->setSpacing(0);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        frame_3 = new QFrame(tasks);
        frame_3->setObjectName("frame_3");
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setAutoFillBackground(true);
        frame_3->setStyleSheet(QString::fromUtf8(""));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        frame = new QFrame(frame_3);
        frame->setObjectName("frame");
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_7 = new QGridLayout(frame);
        gridLayout_7->setObjectName("gridLayout_7");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_2);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName("frame_4");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy2);
        frame_4->setFrameShape(QFrame::Shape::NoFrame);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_9 = new QHBoxLayout(frame_4);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(9, 0, -1, 0);
        tasksDisplay = new QLabel(frame_4);
        tasksDisplay->setObjectName("tasksDisplay");
        sizePolicy2.setHeightForWidth(tasksDisplay->sizePolicy().hasHeightForWidth());
        tasksDisplay->setSizePolicy(sizePolicy2);
        tasksDisplay->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 0;\n"
"font-size: 20px;"));
        tasksDisplay->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_9->addWidget(tasksDisplay);

        addButton = new QPushButton(frame_4);
        addButton->setObjectName("addButton");
        addButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 0;"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/more/img/add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addButton->setIcon(icon5);
        addButton->setIconSize(QSize(25, 25));

        horizontalLayout_9->addWidget(addButton);


        verticalLayout_3->addWidget(frame_4);

        verticalSpacer_1 = new QSpacerItem(13, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_1);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName("horizontalLayout_1");
        horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer_1);

        sortByDeadlineBtn = new QPushButton(frame);
        sortByDeadlineBtn->setObjectName("sortByDeadlineBtn");
        sortByDeadlineBtn->setStyleSheet(QString::fromUtf8("font-size: 10px;\n"
"padding: 3px;"));

        horizontalLayout_1->addWidget(sortByDeadlineBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer_5);

        sortByPriorityBtn = new QPushButton(frame);
        sortByPriorityBtn->setObjectName("sortByPriorityBtn");
        sortByPriorityBtn->setStyleSheet(QString::fromUtf8("font-size: 10px;\n"
"padding: 3px;"));

        horizontalLayout_1->addWidget(sortByPriorityBtn);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_1);

        listWidget = new TaskDisplay(frame);
        listWidget->setObjectName("listWidget");
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setAutoFillBackground(false);
        listWidget->setStyleSheet(QString::fromUtf8("padding: 5px;"));
        listWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        listWidget->setSortingEnabled(false);

        verticalLayout_3->addWidget(listWidget);

        verticalSpacer_9 = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_9);


        gridLayout_7->addLayout(verticalLayout_3, 0, 0, 1, 1);


        horizontalLayout->addWidget(frame);

        horizontalSpacer_2 = new QSpacerItem(13, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        line = new QFrame(frame_3);
        line->setObjectName("line");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy3);
        line->setStyleSheet(QString::fromUtf8(""));
        line->setFrameShadow(QFrame::Shadow::Raised);
        line->setFrameShape(QFrame::Shape::VLine);

        horizontalLayout->addWidget(line);

        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        editor = new TaskEditor(frame_3);
        editor->setObjectName("editor");
        sizePolicy.setHeightForWidth(editor->sizePolicy().hasHeightForWidth());
        editor->setSizePolicy(sizePolicy);
        editor->setStyleSheet(QString::fromUtf8(""));
        editor->setFrameShape(QFrame::Shape::StyledPanel);
        editor->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(editor);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_4->addItem(verticalSpacer_3);

        label_4 = new QLabel(editor);
        label_4->setObjectName("label_4");
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(label_4);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_4->addItem(verticalSpacer_4);

        textEdit = new QTextEdit(editor);
        textEdit->setObjectName("textEdit");
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(textEdit);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_4->addItem(verticalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_5 = new QLabel(editor);
        label_5->setObjectName("label_5");

        horizontalLayout_2->addWidget(label_5);

        comboBox = new QComboBox(editor);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy4);

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_6 = new QLabel(editor);
        label_6->setObjectName("label_6");

        horizontalLayout_3->addWidget(label_6);

        dateTimeEdit = new QDateTimeEdit(editor);
        dateTimeEdit->setObjectName("dateTimeEdit");

        horizontalLayout_3->addWidget(dateTimeEdit);


        verticalLayout_4->addLayout(horizontalLayout_3);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_4->addItem(verticalSpacer_7);

        buttonBox = new QDialogButtonBox(editor);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setAutoFillBackground(false);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout_4->addWidget(buttonBox);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_8);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);


        horizontalLayout->addWidget(editor);

        horizontalSpacer_4 = new QSpacerItem(13, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout_6->addWidget(frame_3, 0, 0, 1, 1);

        stackedWidget->addWidget(tasks);
        setting = new QWidget();
        setting->setObjectName("setting");
        gridLayout_4 = new QGridLayout(setting);
        gridLayout_4->setObjectName("gridLayout_4");
        settingsDisplay = new QLabel(setting);
        settingsDisplay->setObjectName("settingsDisplay");
        settingsDisplay->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 0;\n"
"font-size: 20px;"));
        settingsDisplay->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(settingsDisplay, 0, 0, 1, 1);

        stackedWidget->addWidget(setting);
        login = new QWidget();
        login->setObjectName("login");
        gridLayout_8 = new QGridLayout(login);
        gridLayout_8->setObjectName("gridLayout_8");
        frame_2 = new QFrame(login);
        frame_2->setObjectName("frame_2");
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_2);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        frame_5 = new QFrame(frame_2);
        frame_5->setObjectName("frame_5");
        frame_5->setFrameShape(QFrame::Shape::NoFrame);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_5);
        verticalLayout_2->setSpacing(15);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 120, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        label_3 = new QLabel(frame_5);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font-size:25px;\n"
"font: bold;"));

        verticalLayout_2->addWidget(label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label = new QLabel(frame_5);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font-size:18px;"));

        horizontalLayout_4->addWidget(label);

        usernameEdit = new QLineEdit(frame_5);
        usernameEdit->setObjectName("usernameEdit");
        usernameEdit->setStyleSheet(QString::fromUtf8(""));
        usernameEdit->setFrame(true);

        horizontalLayout_4->addWidget(usernameEdit);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_2 = new QLabel(frame_5);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font-size:18px;"));

        horizontalLayout_5->addWidget(label_2);

        passwordEdit = new QLineEdit(frame_5);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setStyleSheet(QString::fromUtf8(""));
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_5->addWidget(passwordEdit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_18);

        label_7 = new QLabel(frame_5);
        label_7->setObjectName("label_7");
        label_7->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        label_7->setStyleSheet(QString::fromUtf8("font-size:12px;color:0x888888;"));

        horizontalLayout_13->addWidget(label_7);

        registerBtn = new QPushButton(frame_5);
        registerBtn->setObjectName("registerBtn");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(registerBtn->sizePolicy().hasHeightForWidth());
        registerBtn->setSizePolicy(sizePolicy5);
        QPalette palette;
        QBrush brush(QColor(77, 105, 245, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        registerBtn->setPalette(palette);
        registerBtn->setStyleSheet(QString::fromUtf8("font-size:12px;\n"
"padding:3px;"));

        horizontalLayout_13->addWidget(registerBtn);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_17);


        verticalLayout_2->addLayout(horizontalLayout_13);

        buttonBox_2 = new QDialogButtonBox(frame_5);
        buttonBox_2->setObjectName("buttonBox_2");
        buttonBox_2->setStyleSheet(QString::fromUtf8("font-size:18px;"));
        buttonBox_2->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        buttonBox_2->setCenterButtons(true);

        verticalLayout_2->addWidget(buttonBox_2);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_10);


        horizontalLayout_6->addWidget(frame_5);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        gridLayout_8->addWidget(frame_2, 0, 0, 1, 1);

        stackedWidget->addWidget(login);

        gridLayout->addWidget(stackedWidget, 1, 3, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        tab = new QToolBar(MainWindow);
        tab->setObjectName("tab");
        tab->setMovable(false);
        tab->setAllowedAreas(Qt::ToolBarArea::AllToolBarAreas);
        MainWindow->addToolBar(Qt::ToolBarArea::LeftToolBarArea, tab);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ham", nullptr));
        tasksButton->setText(QCoreApplication::translate("MainWindow", "\344\273\273\345\212\241", nullptr));
        classButton->setText(QCoreApplication::translate("MainWindow", "\350\257\276\350\241\250", nullptr));
        homeButton->setText(QCoreApplication::translate("MainWindow", "\344\270\273\351\241\265", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        exportLogBtn->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\212\245\350\241\250", nullptr));
        changePasswordBtn->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        userImageDisplay->setText(QString());
        usernameDisplay->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        logoutBtn->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        btnPersonalCourse->setText(QCoreApplication::translate("MainWindow", "\344\270\252\344\272\272\350\257\276\350\241\250", nullptr));
        btnSchoolCourse->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242\350\257\276\350\241\250", nullptr));
        tasksDisplay->setText(QCoreApplication::translate("MainWindow", "\345\276\205\345\212\236", nullptr));
        addButton->setText(QString());
        sortByDeadlineBtn->setText(QCoreApplication::translate("MainWindow", "\346\214\211\346\210\252\346\255\242\346\227\266\351\227\264\346\216\222\345\272\217", nullptr));
        sortByPriorityBtn->setText(QCoreApplication::translate("MainWindow", "\346\214\211\344\274\230\345\205\210\347\272\247\346\216\222\345\272\217", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\276\205\345\212\236\344\272\213\351\241\271\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\344\274\230\345\205\210\347\272\247\357\274\232", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\344\275\216", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\344\270\255", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\351\253\230", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "\346\210\252\346\255\242\346\227\245\346\234\237\357\274\232", nullptr));
        settingsDisplay->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\254\242\350\277\216\347\231\273\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\264\246\345\217\267\357\274\232", nullptr));
        usernameEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\350\264\246\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\350\277\230\346\262\241\346\234\211\350\264\246\345\217\267?", nullptr));
        registerBtn->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        tab->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
