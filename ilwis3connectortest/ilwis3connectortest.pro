#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T08:14:12
#
#-------------------------------------------------

QT       += testlib

TARGET = ilwis3connectortest
TEMPLATE = lib

include(../global.pri)



DEFINES += ILWIS3CONNECTORTEST_LIBRARY


win32{
    DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases
}

LIBS += -L$$PWD/../libraries/$$PLATFORM$$CONF/ -lilwiscore
unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite

DEPENDPATH += $$PWD/../TestSuite

HEADERS += \
    storingdata.h \
    ilwis3connectortest_global.h \
    ilwis3connectorloaders.h \
    dataaccess.h

SOURCES += \
    storingdata.cpp \
    ilwis3connectorloaders.cpp \
    dataaccess.cpp

