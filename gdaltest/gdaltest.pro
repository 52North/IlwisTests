#-------------------------------------------------
#
# Project created by QtCreator 2014-02-25T08:54:18
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

include(../global.pri)

TARGET = gdaltest
TEMPLATE = lib

DEFINES += GDALTEST_LIBRARY

DESTDIR = $$PWD/../../libraries/$$PLATFORM$$CONF/$$TARGET
DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases

SOURCES += gdaltest.cpp \
    gdalconnectortest.cpp

HEADERS += gdaltest.h\
        gdaltest_global.h \
    gdalconnectortest.h

unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite
DEPENDPATH += $$PWD/../TestSuite
