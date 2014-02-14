#-------------------------------------------------
#
# Project created by QtCreator 2014-02-13T15:24:14
#
#-------------------------------------------------

QT       += core testlib

QT       -= gui

TARGET = TestSuite
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(global.pri)

DLLDESTDIR = $$PWD/../../libraries/$$PLATFORM$$CONF/$$TARGET
DESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin

SOURCES += main.cpp \
    core/util/locationtest.cpp \
    testsuite.cpp \
    ilwistestclass.cpp \
    core/util/coordinatetest.cpp

HEADERS += \
    testmacros.h \
    core/util/locationtest.h \
    testsuite.h \
    ilwistestclass.h \
    core/util/coordinatetest.h
