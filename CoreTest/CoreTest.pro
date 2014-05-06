#-------------------------------------------------
#
# Project created by QtCreator 2014-02-24T11:26:24
#
#-------------------------------------------------

QT       -= gui
QT       +=core testlib

include(../global.pri)

TARGET = CoreTest
TEMPLATE = lib

DESTDIR = $$PWD/../../libraries/$$PLATFORM$$CONF/$$TARGET
DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases

DEFINES += CORETEST_LIBRARY

SOURCES += coretest.cpp \
    util/coordinatetest.cpp \
    util/sizetest.cpp \
    util/numericrangetest.cpp \
    util/locationtest.cpp \
    util/juliantimetests.cpp \
    catalog/tst_resourcetest.cpp \
    ilwisobjects/domain/domaintimetests.cpp \
    ilwisobjects/domain/numericdomaintests.cpp \
    ilwisobjects/domain/thematicdomaintests.cpp \
    ilwisobjects/domain/identifierdomaintests.cpp \
    ilwisobjects/domain/intervaldomaintests.cpp \
    ilwisobjects/coverage/vertexiteratortests.cpp

HEADERS += coretest.h\
        coretest_global.h \
    util/coordinatetest.h \
    util/sizetest.h \
    util/numericrangetest.h \
    util/locationtest.h \
    util/juliantimetests.h \
    catalog/tst_resourcetest.h \
    ilwisobjects/domain/domaintimetests.h \
    ilwisobjects/domain/numericdomaintests.h \
    ilwisobjects/domain/thematicdomaintests.h \
    ilwisobjects/domain/identifierdomaintests.h \
    ilwisobjects/domain/intervaldomaintests.h \
    ilwisobjects/coverage/vertexiteratortests.h

OTHER_FILES +=

unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite
DEPENDPATH += $$PWD/../TestSuite

