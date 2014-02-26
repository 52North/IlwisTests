#-------------------------------------------------
#
# Project created by QtCreator 2014-02-25T14:47:07
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

include(../global.pri)

TARGET = postgrestest
TEMPLATE = lib

DEFINES += POSTGRESTEST_LIBRARY

DESTDIR = $$PWD/../../libraries/$$PLATFORM$$CONF/$$TARGET
DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases

SOURCES += postgrestest.cpp


HEADERS += postgrestest_global.h \
    postgrestest.h

unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite
DEPENDPATH += $$PWD/../TestSuite
