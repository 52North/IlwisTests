#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T08:14:12
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = rasteroperationsTest
TEMPLATE = lib

include(../global.pri)



DEFINES += RASTEROPERATIONSTEST_LIBRARY

win32{
    DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases
}


SOURCES += \
    rastercalc.cpp \
    classification.cpp \
    rasteroperations.cpp

HEADERS +=\
        rasteroperationstest_global.h \
    rastercalc.h \
    classification.h \
    rasteroperations.h


unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite

DEPENDPATH += $$PWD/../TestSuite

