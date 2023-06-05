#-------------------------------------------------
#
# Project created by QtCreator 2022-03-10T17:15:57
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += serialbus serialport widgets
QT       += sql
QT       += charts
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = robotPro
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    camera.cpp \
    camera_login.cpp \
    logwidget.cpp \
        main.cpp \
        mainwindow.cpp \
    inspection.cpp \
    history.cpp \
    robot_login.cpp \
    warning.cpp \
    xiancheng.cpp \
    moniguiji.cpp

HEADERS += \
    camera.h \
    camera_login.h \
    dhconfigsdk.h \
    dhnetsdk.h \
    logwidget.h \
        mainwindow.h \
    inspection.h \
    history.h \
    robot_login.h \
    warning.h \
    xiancheng.h \
    moniguiji.h

FORMS += \
    camera.ui \
    camera_login.ui \
    logwidget.ui \
        mainwindow.ui \
    inspection.ui \
    history.ui \
    robot_login.ui \
    warning.ui \
    moniguiji.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
unix:!macx|win32: LIBS += -L$$PWD/libs/ -ldhconfigsdk

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/dhconfigsdk.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/libs/libdhconfigsdk.a

unix:!macx|win32: LIBS += -L$$PWD/libs/ -ldhnetsdk

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/dhnetsdk.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/libs/libdhnetsdk.a

#for DbgHelp
#方便生成DUMP调试
LIBS += -lDbgHelp
QMAKE_LFLAGS_RELEASE = /INCREMENTAL:NO /DEBUG

#release版程序带上调试信息
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

#for qBreakpad
#qBreakpad中需要使用到network模块
QT += network

#启用多线程、异常、RTTI、STL支持
CONFIG += thread exceptions rtti stl

#没有c++11和AppKit库编译器不能解决符号的地址
CONFIG += c++11
macx: LIBS += -framework AppKit

#release版程序带上调试信息
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

#配置头文件搜索路径和链接库路径
INCLUDEPATH += $$PWD/qBreakpad/include

CONFIG(debug, debug|release) {
LIBS += -L$$PWD/qBreakpad/lib/debug -lqBreakpad
} else {
LIBS += -L$$PWD/qBreakpad/lib/release -lqBreakpad
}

RESOURCES += \
    images.qrc
