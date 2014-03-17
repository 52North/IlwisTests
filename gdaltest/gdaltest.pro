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

SOURCES += \
    gdalconnectortest.cpp \
    catalogtest.cpp \
    gdaldataaccess.cpp

HEADERS +=\
        gdaltest_global.h \
    gdalconnectortest.h \
    catalogtest.h \
    gdaldataaccess.h

unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite
DEPENDPATH += $$PWD/../TestSuite
