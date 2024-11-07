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
    QStackedWidget *stackedWidget;
    QWidget *home;
    QGridLayout *gridLayout_3;
    QLabel *homeDisplay;
    QToolButton *settingsButton;
    QToolButton *homeButton;
    QToolButton *tasksButton;
    QToolButton *classButton;
    QWidget *timetable;
    QGridLayout *gridLayout_5;
    QLabel *timetableDisplay;
    QWidget *tasks;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_5;
    QLabel *tasksDisplay;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *addButton;
    QSpacerItem *verticalSpacer_2;
    TaskDisplay *listWidget;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QSpacerItem *horizontalSpacer_3;
    TaskEditor *editor;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_9;
    QTextEdit *textEdit;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QDateTimeEdit *dateTimeEdit;
    QSpacerItem *verticalSpacer_7;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *horizontalSpacer_4;
    QWidget *setting;
    QGridLayout *gridLayout_4;
    QLabel *settingsDisplay;
    QToolBar *tab;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(850, 400);
        MainWindow->setMinimumSize(QSize(850, 0));
        MainWindow->setMaximumSize(QSize(850, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/img/icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color:rgb(30, 30, 30);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        home = new QWidget();
        home->setObjectName("home");
        gridLayout_3 = new QGridLayout(home);
        gridLayout_3->setObjectName("gridLayout_3");
        homeDisplay = new QLabel(home);
        homeDisplay->setObjectName("homeDisplay");
        homeDisplay->setStyleSheet(QString::fromUtf8("color:white; \n"
"background-color: transparent; \n"
"border: 0;"));
        homeDisplay->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_3->addWidget(homeDisplay, 0, 2, 1, 1);

        settingsButton = new QToolButton(home);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setStyleSheet(QString::fromUtf8("color:white; \n"
"background-color: transparent; \n"
"border: 0;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/tab/img/settings.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        settingsButton->setIcon(icon1);
        settingsButton->setIconSize(QSize(30, 30));
        settingsButton->setAutoExclusive(true);
        settingsButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout_3->addWidget(settingsButton, 1, 3, 1, 1);

        homeButton = new QToolButton(home);
        homeButton->setObjectName("homeButton");
        homeButton->setStyleSheet(QString::fromUtf8("color:white; \n"
"background-color: transparent; \n"
"border: 0;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/tab/img/home.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        homeButton->setIcon(icon2);
        homeButton->setIconSize(QSize(30, 30));
        homeButton->setAutoExclusive(true);
        homeButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout_3->addWidget(homeButton, 2, 0, 1, 1);

        tasksButton = new QToolButton(home);
        tasksButton->setObjectName("tasksButton");
        tasksButton->setStyleSheet(QString::fromUtf8("color:white; \n"
"background-color: transparent; \n"
"border: 0;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/tab/img/tasks.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tasksButton->setIcon(icon3);
        tasksButton->setIconSize(QSize(30, 30));
        tasksButton->setAutoExclusive(true);
        tasksButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout_3->addWidget(tasksButton, 2, 2, 1, 1);

        classButton = new QToolButton(home);
        classButton->setObjectName("classButton");
        classButton->setStyleSheet(QString::fromUtf8("color:white; \n"
"background-color: transparent; \n"
"border: 0;"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/tab/img/class.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        classButton->setIcon(icon4);
        classButton->setIconSize(QSize(30, 30));
        classButton->setAutoExclusive(true);
        classButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout_3->addWidget(classButton, 3, 1, 1, 1);

        stackedWidget->addWidget(home);
        timetable = new QWidget();
        timetable->setObjectName("timetable");
        gridLayout_5 = new QGridLayout(timetable);
        gridLayout_5->setObjectName("gridLayout_5");
        timetableDisplay = new QLabel(timetable);
        timetableDisplay->setObjectName("timetableDisplay");
        timetableDisplay->setStyleSheet(QString::fromUtf8("color:white; \n"
"background-color: transparent; \n"
"border: 0;"));
        timetableDisplay->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_5->addWidget(timetableDisplay, 0, 0, 1, 1);

        stackedWidget->addWidget(timetable);
        tasks = new QWidget();
        tasks->setObjectName("tasks");
        sizePolicy.setHeightForWidth(tasks->sizePolicy().hasHeightForWidth());
        tasks->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(tasks);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_5 = new QSpacerItem(30, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        tasksDisplay = new QLabel(tasks);
        tasksDisplay->setObjectName("tasksDisplay");
        tasksDisplay->setStyleSheet(QString::fromUtf8("color:white; \n"
"background-color: transparent; \n"
"border: 0;"));
        tasksDisplay->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(tasksDisplay);

        horizontalSpacer_6 = new QSpacerItem(120, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        addButton = new QPushButton(tasks);
        addButton->setObjectName("addButton");
        addButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 0;"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/more/img/add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addButton->setIcon(icon5);
        addButton->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(addButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(13, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(verticalSpacer_2);

        listWidget = new TaskDisplay(tasks);
        listWidget->setObjectName("listWidget");
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setAutoFillBackground(false);
        listWidget->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        listWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout->addWidget(listWidget);

        verticalSpacer_3 = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(13, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        line = new QFrame(tasks);
        line->setObjectName("line");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_3->addWidget(line);

        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        editor = new TaskEditor(tasks);
        editor->setObjectName("editor");
        sizePolicy.setHeightForWidth(editor->sizePolicy().hasHeightForWidth());
        editor->setSizePolicy(sizePolicy);
        editor->setStyleSheet(QString::fromUtf8("background-color:rgb(45, 45, 45);"));
        editor->setFrameShape(QFrame::Shape::StyledPanel);
        editor->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_6 = new QGridLayout(editor);
        gridLayout_6->setObjectName("gridLayout_6");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        label_2 = new QLabel(editor);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_9);

        textEdit = new QTextEdit(editor);
        textEdit->setObjectName("textEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(textEdit);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(editor);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        comboBox = new QComboBox(editor);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label = new QLabel(editor);
        label->setObjectName("label");

        horizontalLayout_4->addWidget(label);

        dateTimeEdit = new QDateTimeEdit(editor);
        dateTimeEdit->setObjectName("dateTimeEdit");

        horizontalLayout_4->addWidget(dateTimeEdit);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_7);

        buttonBox = new QDialogButtonBox(editor);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setAutoFillBackground(false);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout_2->addWidget(buttonBox);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_8);


        gridLayout_6->addLayout(verticalLayout_2, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(editor);

        horizontalSpacer_4 = new QSpacerItem(13, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        stackedWidget->addWidget(tasks);
        setting = new QWidget();
        setting->setObjectName("setting");
        gridLayout_4 = new QGridLayout(setting);
        gridLayout_4->setObjectName("gridLayout_4");
        settingsDisplay = new QLabel(setting);
        settingsDisplay->setObjectName("settingsDisplay");
        settingsDisplay->setStyleSheet(QString::fromUtf8("color:white; \n"
"background-color: transparent; \n"
"border: 0;"));
        settingsDisplay->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(settingsDisplay, 0, 0, 1, 1);

        stackedWidget->addWidget(setting);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        tab = new QToolBar(MainWindow);
        tab->setObjectName("tab");
        tab->setMovable(false);
        tab->setAllowedAreas(Qt::ToolBarArea::AllToolBarAreas);
        MainWindow->addToolBar(Qt::ToolBarArea::LeftToolBarArea, tab);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ham", nullptr));
        homeDisplay->setText(QCoreApplication::translate("MainWindow", "\344\270\273\351\241\265", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        homeButton->setText(QCoreApplication::translate("MainWindow", "\344\270\273\351\241\265", nullptr));
        tasksButton->setText(QCoreApplication::translate("MainWindow", "\344\273\273\345\212\241", nullptr));
        classButton->setText(QCoreApplication::translate("MainWindow", "\350\257\276\350\241\250", nullptr));
        timetableDisplay->setText(QCoreApplication::translate("MainWindow", "\350\257\276\350\241\250", nullptr));
        tasksDisplay->setText(QCoreApplication::translate("MainWindow", "\345\276\205\345\212\236", nullptr));
        addButton->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\276\205\345\212\236\344\272\213\351\241\271\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\344\274\230\345\205\210\347\272\247\357\274\232", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\344\275\216", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\344\270\255", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\351\253\230", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "\346\210\252\346\255\242\346\227\245\346\234\237\357\274\232", nullptr));
        settingsDisplay->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        tab->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
