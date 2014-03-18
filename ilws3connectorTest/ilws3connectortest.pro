#-------------------------------------------------
#
# Project created by QtCreator 2014-02-27T11:11:24
#
#-------------------------------------------------

TARGET = ilws3connectorTest
TEMPLATE = lib

DEFINES += ILWS3CONNECTORTEST_LIBRARY

SOURCES += \
    dataaccess.cpp \
    ilws3connectorloaders.cpp \
    storingdata.cpp

HEADERS +=\
        ilws3connectortest_global.h \
    dataaccess.h \
    ilws3connectorloaders.h \
    storingdata.h


QT       += testlib

QT       -= gui

include(../global.pri)

DESTDIR = $$PWD/../../libraries/$$PLATFORM$$CONF/$$TARGET
DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases

unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite
DEPENDPATH += $$PWD/../TestSuite
