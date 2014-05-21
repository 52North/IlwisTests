#-------------------------------------------------
#
# Project created by QtCreator 2014-02-24T13:37:32
#
#-------------------------------------------------

QT       += core testlib

QT       -= gui

TARGET = TestRunner
CONFIG   += console
CONFIG   -= app_bundle

include(../global.pri)

win32{
    DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin
}

DESTDIR = $$PWD/../../libraries/$$PLATFORM$$CONF

TEMPLATE = app

SOURCES += main.cpp

unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite
DEPENDPATH += $$PWD/../TestSuite
