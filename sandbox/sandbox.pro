#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T08:14:12
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = sandbox
TEMPLATE = lib

include(../global.pri)



DEFINES += sandbox_LIBRARY

win32{
    DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases
}


SOURCES += sandboxtest.cpp

HEADERS += sandboxtest.h


unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite

DEPENDPATH += $$PWD/../TestSuite

