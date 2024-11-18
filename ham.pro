QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core network multimedia
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ComboBoxManager.cpp \
    coursecontrol.cpp \
    hamsystem.cpp \
    homedisplay.cpp \
    main.cpp \
    netdataaccess.cpp \
    passwordchange.cpp \
    personalcoursedisplay.cpp \
    registeruser.cpp \
    schoolcoursedisplay.cpp \
    taskdisplay.cpp \
    taskeditor.cpp \
    taskitem.cpp \
    ClockWidget.cpp\
    taskscontrol.cpp

HEADERS += \
    ComboBoxManager.h \
    coursecontrol.h \
    hamsystem.h \
    homedisplay.h \
    netdataaccess.h \
    passwordchange.h \
    personalcoursedisplay.h \
    registeruser.h \
    schoolcoursedisplay.h \
    taskdisplay.h \
    taskeditor.h \
    taskitem.h \
    ClockWidget.h\
    taskscontrol.h

FORMS += \
    hamsystem.ui \
    passwordchange.ui \
    registeruser.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES +=

RC_ICONS = img/logo.ico
