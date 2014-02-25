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

DLLDESTDIR = $$PWD/../../../output/$$PLATFORM$$CONF/bin/testcases
DESTDIR = $$PWD/../libraries

SOURCES += gdaltest.cpp \
    gdalconnectortest.cpp

HEADERS += gdaltest.h\
        gdaltest_global.h \
    gdalconnectortest.h

INSTALLS += testtarget

unix|win32: LIBS += -L$$PWD/../libraries/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite
DEPENDPATH += $$PWD/../TestSuite
