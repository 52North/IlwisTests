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

DLLDESTDIR = $$PWD/../../../output/$$PLATFORM$$CONF/bin/testcases
DESTDIR = $$PWD/../libraries

SOURCES += postgrestest.cpp


HEADERS += postgrestest_global.h \
    postgrestest.h

INSTALLS += testtarget

unix|win32: LIBS += -L$$PWD/../libraries/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite
DEPENDPATH += $$PWD/../TestSuite
