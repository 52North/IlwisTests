#-------------------------------------------------
#
# Project created by QtCreator 2014-02-25T14:47:07
#
#-------------------------------------------------

QT       += testlib

include(../global.pri)

TARGET = postgrestest
TEMPLATE = lib

DEFINES += POSTGRESTEST_LIBRARY

DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases

SOURCES += postgrestest.cpp \
    postgresdemo.cpp


HEADERS += postgrestest_global.h \
    postgrestest.h \
    postgresdemo.h

unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite
DEPENDPATH += $$PWD/../TestSuite
