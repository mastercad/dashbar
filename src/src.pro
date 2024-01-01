######################################################################
# Automatically generated by qmake (3.1) Mon Aug 29 10:43:55 2022
######################################################################

TEMPLATE = app

QT += core gui widgets

TARGET = Dashbar

INCLUDEPATH += .

CONFIG += c++11

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += \
           application.h \
           applicationRules.h \
           applications.h \
           buttonManager.h \
           config.h \
           fileDialog.h \
           flowlayout.h \
           mainwindow.h \
           mapper.h \
           windowPositionManager.h \
           osretriever.h

FORMS += mainwindow.ui

SOURCES += \
           application.cpp \
           applicationRules.cpp \
           applications.cpp \
           buttonManager.cpp \
           config.cpp \
           fileDialog.cpp \
           flowlayout.cpp \
           main.cpp \
           mainwindow.cpp \
           mapper.cpp \
           windowPositionManager.cpp \
           osretriever.cpp

RESOURCES += resources.qrc

TRANSLATIONS += Dashbar_en_GB.ts

DESTDIR = $$PWD/../build
