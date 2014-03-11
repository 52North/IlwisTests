#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T13:21:11
#
#-------------------------------------------------

QT       += testlib network xmlpatterns

QT       -= gui

include(../global.pri)

TARGET = wfstest

TEMPLATE = lib

DEFINES += WFSTEST_LIBRARY

DESTDIR = $$PWD/../../libraries/$$PLATFORM$$CONF/$$TARGET
DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases

SOURCES += \
    wfsmoduletest.cpp \
    wfscatalogconnectortest.cpp \
    webfeatureservicetest.cpp \
    qtxmlparsertest.cpp \
    wfsresponsetest.cpp \
    wfsparsertest.cpp \
    wfsdemo.cpp

HEADERS +=\
    wfstest_global.h \
    wfsmoduletest.h \
    wfscatalogconnectortest.h \
    webfeatureservicetest.h \
    qtxmlparsertest.h \
    wfstestconstants.h \
    wfsresponsetest.h \
    wfsparsertest.h \
    wfsdemo.h

unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite
unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/wfsconnector/ -lwfsconnector

INCLUDEPATH += $$PWD/../TestSuite \
               $$PWD/../../IlwisConnectors/wfsconnector
DEPENDPATH += $$PWD/../TestSuite \
              $$PWD/../../IlwisConnectors/wfsconnector

OTHER_FILES += \
    testfiles/wfs_exceptionreport.xml \
    testfiles/wfs_capabilities.xml \
    testfiles/test_without_xml_header.xml \
    testfiles/test.xml \
    testfiles/quad100.xsd \
    testfiles/greenlevel_contours.xsd \
    testfiles/featurecollection_quad100.xml \
    testfiles/featurecollection_greenlevel_contours.xml \
    testfiles/featurecollection_sioseinspire_lu_es_14.xml \
    testfiles/sioseinspire_lu_es_14.xsd

testdll.files = \
     $$PWD/../../libraries/$$PLATFORM$$CONF/wfsconnector/wfsconnector.dll

testfiles.files = \
    testfiles/wfs_exceptionreport.xml \
    testfiles/wfs_capabilities.xml \
    testfiles/test_without_xml_header.xml \
    testfiles/test.xml \
    testfiles/quad100.xsd \
    testfiles/greenlevel_contours.xsd \
    testfiles/featurecollection_quad100.xml \
    testfiles/featurecollection_greenlevel_contours.xml \
    testfiles/featurecollection_sioseinspire_lu_es_14.xml \
    testfiles/sioseinspire_lu_es_14.xsd

testdll.path = \
    $$PWD/../../output/$$PLATFORM$$CONF/bin/

testfiles.path = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases/testfiles

INSTALLS += testfiles testdll
