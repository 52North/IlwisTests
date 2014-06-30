#-------------------------------------------------
#
# Project created by QtCreator 2014-02-24T13:44:02
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = TestSuite
TEMPLATE = lib

include(../global.pri)

DEFINES += TESTSUITE_LIBRARY

SOURCES += testsuite.cpp \
    ilwistestclass.cpp

HEADERS += testsuite.h\
        testsuite_global.h \
        testutils.h \
        testmacros.h \
        ilwistestclass.h

DESTDIR = $$PWD/../../libraries/$$PLATFORM$$CONF

win32{
    DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin
}



