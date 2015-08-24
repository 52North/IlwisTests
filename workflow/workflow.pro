#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T08:14:12
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = workflow
TEMPLATE = lib

include(../global.pri)



DEFINES += workflow_LIBRARY

win32{
    DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases
}


SOURCES += \
    workflowtest.cpp

HEADERS += \
    workflowtest.h


LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite

DEPENDPATH += $$PWD/../TestSuite

