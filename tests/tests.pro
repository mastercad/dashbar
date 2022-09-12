QT += core widgets testlib
QT -= gui

CONFIG += qt c++11 console warn_on depend_includepath testcase
CONFIG -= app_bundle

TARGET = DashbarTests
TEMPLATE = app

HEADERS += ../src/application.h \
    ../src/applicationRules.h \
    ../src/applications.h \
    ../src/buttonManager.h \
    ../src/config.h \
    ../src/fileDialog.h \
    ../src/flowlayout.h \
    ../src/mainwindow.h \
    ../src/mapper.h \
    ../src/windowPositionManager.h \
    tst_applications.h \
    tst_buttonManager.h \
    tst_windowPositionManager.h

SOURCES += ../src/application.cpp \
    ../src/applicationRules.cpp \
    ../src/applications.cpp \
    ../src/buttonManager.cpp \
    ../src/config.cpp \
    ../src/fileDialog.cpp \
    ../src/flowlayout.cpp \
    ../src/mainwindow.cpp \
    ../src/mapper.cpp \
    ../src/windowPositionManager.cpp \
    tst_applications.cpp \
    tst_buttonManager.cpp \
    tst_main.cpp \
    tst_windowPositionManager.cpp

INCLUDEPATH += ./ \
    ../src

DESTDIR = $$PWD/../build
