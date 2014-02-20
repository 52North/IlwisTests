#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T16:44:16
#
#-------------------------------------------------

TARGET = IlwisModuleTests

include(global.pri)

DLLDESTDIR = $$PWD/../libraries/$$PLATFORM$$CONF/$$TARGET
DESTDIR = $$PWD/../output/$$PLATFORM$$CONF/bin

QT       += sql testlib network xmlpatterns

CONFIG   += console
CONFIG   -= app_bundle



TEMPLATE = app


HEADERS += \
    rasteroperationstest/tst_rasteroperationstest.h \
    wfsconnectortest/tst_wfsconnectortest.h \
    core/catalog/tst_resourcetest.h \
    xmltests/qtxmlparsertest.h \
    testutils.h

SOURCES += \
    rasteroperationstest/tst_rasteroperationstest.cpp \
    testmodules.cpp \
    wfsconnectortest/tst_wfsconnectortest.cpp \
    core/catalog/tst_resourcetest.cpp \
    xmltests/qtxmlparsertest.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libraries/$$PLATFORM$$CONF/core/ -lilwiscore \
                                              -L$$PWD/../libraries/$$PLATFORM$$CONF/wfsconnector/ -lwfsconnector
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libraries/$$PLATFORM$$CONF/core/ -lilwiscore \
                                                 -L$$PWD/../libraries/$$PLATFORM$$CONF/wfsconnector/ -lwfsconnector

INCLUDEPATH += $$PWD/../IlwisCore/core \
    $$PWD/../IlwisCore/rasteroperations \
    $$PWD/../IlwisConnectors/wfsconnector \
    $$PWD/../external/

DEPENDPATH += $$PWD/../ilwiscore/core \
    $$PWD/../IlwisCore/rasteroperations \
    $$PWD/../IlwisConnectors/wfsconnector

OTHER_FILES += \
    global.pri \


testtarget.files = testfiles/wfs_capabilities.xml \
    testfiles/test_without_xml_header.xml \
    testfiles/wfs_exceptionreport.xml \
    testfiles/featurecollection.xml \
    testfiles/test.xml \
    testfiles/quad100.xsd

testtarget.path = $$PWD/../output/$$PLATFORM$$CONF/bin/extensions/testfiles

INSTALLS += testtarget
