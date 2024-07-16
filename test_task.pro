#-------------------------------------------------
#
# Project created by QtCreator 2024-07-11T10:00:46
#
#-------------------------------------------------

QT       += core gui network

CONFIG += c++20

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_task
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

INCLUDEPATH += include

SOURCES += \
        main.cpp \
        testtask.cpp \
    infomodel.cpp \
    dataobject.cpp\
    workerthread.cpp \
    rectobject.cpp \
    ellipseobject.cpp \
    lineobject.cpp \
    triangleobject.cpp

HEADERS += \
        testtask.h \
    infomodel.h \
    dataobject.h \
    api_generated.h\
    workerthread.h \
    rectobject.h \
    ellipseobject.h \
    lineobject.h \
    triangleobject.h

FORMS += \
        testtask.ui

RESOURCES += \
    resource.qrc
