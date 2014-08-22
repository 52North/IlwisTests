#-------------------------------------------------
#
# Project created by QtCreator 2011-12-16T23:41:53
#
#-------------------------------------------------

TARGET = Ilwis

include(global.pri)

DLLDESTDIR = $$PWD/../libraries/$$PLATFORM$$CONF/$$TARGET
DESTDIR = $$PWD/../output/$$PLATFORM$$CONF/bin

QT       += core gui sql testlib

TEMPLATE = app

SOURCES += systemtest/main.cpp \
    systemtest/systemtest.cpp



HEADERS += \
    systemtest/systemtest.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libraries/$$PLATFORM$$CONF/core/ -lilwiscore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libraries/$$PLATFORM$$CONF/core/ -lilwiscore

INCLUDEPATH += $$PWD/../ilwiscore/core
DEPENDPATH += $$PWD/../ilwiscore/core

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libraries/win32release/ -llibgeos
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libraries/win32debug/ -llibgeos

INCLUDEPATH += $$PWD/../external/geos
DEPENDPATH += $$PWD/../external/geos

OTHER_FILES += \
    global.pri


