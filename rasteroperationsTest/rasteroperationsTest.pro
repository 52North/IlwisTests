#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T08:14:12
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

include(../global.pri)

TARGET = rasteroperationsTest
TEMPLATE = lib

DEFINES += RASTEROPERATIONSTEST_LIBRARY

DESTDIR = $$PWD/../../libraries/$$PLATFORM$$CONF/$$TARGET
DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases

SOURCES += rasteroperationstest.cpp \
    rastercalc.cpp \
    classification.cpp

HEADERS += rasteroperationstest.h\
        rasteroperationstest_global.h \
    rastercalc.h \
    classification.h


unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite

DEPENDPATH += $$PWD/../TestSuite

