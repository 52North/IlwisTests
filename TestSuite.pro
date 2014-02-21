#-------------------------------------------------
#
# Project created by QtCreator 2014-02-13T15:24:14
#
#-------------------------------------------------

QT       += core testlib network xmlpatterns

QT       -= gui

TARGET = TestSuite
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(global.pri)

DLLDESTDIR = $$PWD/../libraries/$$PLATFORM$$CONF/$$TARGET
DESTDIR = $$PWD/../output/$$PLATFORM$$CONF/bin

SOURCES += main.cpp \
    core/util/locationtest.cpp \
    testsuite.cpp \
    ilwistestclass.cpp \
    core/util/coordinatetest.cpp \
    connectors/gdalconnector/gdalconnectortest.cpp \
    core/util/sizetest.cpp \
    core/util/numericrangetest.cpp \
    core/util/juliantimetests.cpp \
    core/ilwisobjects/domain/domaintimetests.cpp \
    core/catalog/tst_resourcetest.cpp \
    connectors/wfsconnector/qtxmlparsertest.cpp \
    connectors/wfsconnector/wfsconnectortest.cpp \
    core/rasteroperations/rasteroperationstest.cpp \
    connectors/wfsconnector/wfscatalogconnectortest.cpp \
    connectors/wfsconnector/wfsmoduletest.cpp \
    connectors/wfsconnector/webfeatureservicetest.cpp

HEADERS += \
    testmacros.h \
    core/util/locationtest.h \
    testsuite.h \
    ilwistestclass.h \
    core/util/coordinatetest.h \
    connectors/gdalconnector/gdalconnectortest.h \
    core/util/sizetest.h \
    core/util/juliantimetests.h \
    core/ilwisobjects/domain/domaintimetests.h \
    core/util/numericrangetest.h \
    core/catalog/tst_resourcetest.h \
    connectors/wfsconnector/qtxmlparsertest.h \
    testutils.h \
    connectors/wfsconnector/wfsconnectortest.h \
    core/rasteroperations/rasteroperationstest.h \
    connectors/wfsconnector/wfscatalogconnectortest.h \
    connectors/wfsconnector/wfsmoduletest.h \
    connectors/wfsconnector/webfeatureservicetest.h
