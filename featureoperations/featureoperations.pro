#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T08:14:12
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = featureoperationsTest
TEMPLATE = lib

include(../global.pri)



DEFINES += FEATUREOPERATIONSTEST_LIBRARY

win32{
    DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases
}


SOURCES += featureoperationstest.cpp

HEADERS += featureoperationstest.h


unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite

DEPENDPATH += $$PWD/../TestSuite

