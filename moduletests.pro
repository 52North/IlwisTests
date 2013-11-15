#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T16:44:16
#
#-------------------------------------------------

TARGET = IlwisModuleTests

include(global.pri)

DLLDESTDIR = $$PWD/../libraries/$$PLATFORM$$CONF/$$TARGET
DESTDIR = $$PWD/../output/$$PLATFORM$$CONF/bin

QT       += sql testlib

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


HEADERS += \
    rasteroperationstest/tst_rasteroperationstest.h \
    systemtest/systemtest.h \
    testcontants.h

SOURCES += \
    rasteroperationstest/tst_rasteroperationstest.cpp \
    testmodules.cpp \
    systemtest/systemtest.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libraries/$$PLATFORM$$CONF/core/ -lilwiscore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libraries/$$PLATFORM$$CONF/core/ -lilwiscore

INCLUDEPATH += $$PWD/../ilwiscore/core \
    $$PWD/../ilwiscore/rasteroperations
DEPENDPATH += $$PWD/../ilwiscore/core \
    $$PWD/../ilwiscore/rasteroperations

OTHER_FILES += \
    global.pri

