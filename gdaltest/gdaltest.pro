#-------------------------------------------------
#
# Project created by QtCreator 2014-02-25T08:54:18
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = gdaltest
TEMPLATE = lib

include(../global.pri)

DEFINES += GDALTEST_LIBRARY

win32{
    DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases
}

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
