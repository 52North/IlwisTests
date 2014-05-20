#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T08:14:12
#
#-------------------------------------------------

QT       += testlib

TARGET = rasteroperationsTest
TEMPLATE = lib

include(../global.pri)



DEFINES += ILWS3CONNECTORTEST_LIBRARY


win32{
    DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases
}

LIBS += -L$$PWD/../libraries/$$PLATFORM$$CONF/ -lilwiscore
unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite

DEPENDPATH += $$PWD/../TestSuite

HEADERS += \
    storingdata.h \
    ilws3connectortest_global.h \
    ilws3connectorloaders.h \
    dataaccess.h

SOURCES += \
    storingdata.cpp \
    ilws3connectorloaders.cpp \
    dataaccess.cpp

