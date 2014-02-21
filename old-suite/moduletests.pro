#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T16:44:16
#
#-------------------------------------------------

QT       += sql testlib network xmlpatterns

QT       -= gui

TARGET = IlwisModuleTests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(global.pri)

DLLDESTDIR = $$PWD/../../libraries/$$PLATFORM$$CONF/$$TARGET
DESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin


SOURCES += \
    rasteroperationstest/tst_rasteroperationstest.cpp \
    testmodules.cpp \
    wfsconnectortest/tst_wfsconnectortest.cpp \
    core/catalog/tst_resourcetest.cpp \
    xmltests/qtxmlparsertest.cpp

HEADERS += \
    rasteroperationstest/tst_rasteroperationstest.h \
    wfsconnectortest/tst_wfsconnectortest.h \
    core/catalog/tst_resourcetest.h \
    xmltests/qtxmlparsertest.h \
    testutils.h

testtarget.files = testfiles/wfs_capabilities.xml \
    testfiles/test_without_xml_header.xml \
    testfiles/wfs_exceptionreport.xml \
    testfiles/featurecollection.xml \
    testfiles/test.xml \
    testfiles/quad100.xsd \
    testfiles/greenlevel_contours.xsd

testtarget.path = $$PWD/../../output/$$PLATFORM$$CONF/bin/extensions/testfiles

INSTALLS += testtarget
