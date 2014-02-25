#-------------------------------------------------
#
# Project created by QtCreator 2014-02-24T13:44:02
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

include(../global.pri)

TARGET = TestSuite
TEMPLATE = lib

DLLDESTDIR = $$PWD/../../../output/$$PLATFORM$$CONF/bin
DESTDIR = $$PWD/../libraries


DEFINES += TESTSUITE_LIBRARY

SOURCES += testsuite.cpp \
    ilwistestclass.cpp

HEADERS += testsuite.h\
        testsuite_global.h \
    testutils.h \
    testmacros.h \
    ilwistestclass.h

LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/core/ -lilwiscore \
        -L$$PWD/../../libraries/$$PLATFORM$$CONF/ -llibgeos

INCLUDEPATH +=  $$PWD/core \
                $$PWD/../../external/geos
DEPENDPATH +=   $$PWD/core \
                $$PWD/../../external/geos

OTHER_FILES +=

