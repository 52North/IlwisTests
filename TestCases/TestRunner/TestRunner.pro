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

DESTDIR = $$PWD/../../../output/$$PLATFORM$$CONF/bin

TEMPLATE = app

SOURCES += main.cpp

unix|win32: LIBS += -L$$PWD/../libraries/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite
DEPENDPATH += $$PWD/../TestSuite
