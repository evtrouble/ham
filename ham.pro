QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core network
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coursecontrol.cpp \
    hamsystem.cpp \
    homedisplay.cpp \
    main.cpp \
    mainwindow.cpp \
    netdataaccess.cpp \
    passwordchange.cpp \
    personalcoursedisplay.cpp \
    registeruser.cpp \
    schoolcoursedisplay.cpp \
    taskdisplay.cpp \
    taskeditor.cpp \
    taskitem.cpp \
    taskscontrol.cpp

HEADERS += \
    coursecontrol.h \
    hamsystem.h \
    homedisplay.h \
    mainwindow.h \
    netdataaccess.h \
    passwordchange.h \
    personalcoursedisplay.h \
    registeruser.h \
    schoolcoursedisplay.h \
    taskdisplay.h \
    taskeditor.h \
    taskitem.h \
    taskscontrol.h

FORMS += \
    mainwindow.ui \
    passwordchange.ui \
    registeruser.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES += \
    img/down-arrow.png
