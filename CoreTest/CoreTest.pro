#-------------------------------------------------
#
# Project created by QtCreator 2014-02-24T11:26:24
#
#-------------------------------------------------

QT       -= gui
QT       +=core testlib network xmlpatterns

include(../global.pri)

TARGET = CoreTest
TEMPLATE = lib

win32{
    DLLDESTDIR = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases
}


DEFINES += CORETEST_LIBRARY

SOURCES += coretest.cpp \
    util/coordinatetest.cpp \
    util/sizetest.cpp \
    util/numericrangetest.cpp \
    util/locationtest.cpp \
    util/juliantimetests.cpp \
    util/qtxmlparsertest.cpp \
    catalog/tst_resourcetest.cpp \
    ilwisobjects/domain/domaintimetests.cpp \
    ilwisobjects/domain/numericdomaintests.cpp \
    ilwisobjects/domain/thematicdomaintests.cpp \
    ilwisobjects/domain/identifierdomaintests.cpp \
    ilwisobjects/domain/intervaldomaintests.cpp \
    ilwisobjects/table/tabletests.cpp \
    iterators/vertexiteratortest.cpp \
    iterators/pixeliteratortest.cpp \
    ilwisobjects/coverage/rastercoveragetest.cpp \
    ilwisobjects/coverage/featurecoveragetest.cpp

HEADERS += coretest.h\
        coretest_global.h \
    util/coordinatetest.h \
    util/sizetest.h \
    util/numericrangetest.h \
    util/locationtest.h \
    util/juliantimetests.h \
    util/qtxmlparsertest.h \
    catalog/tst_resourcetest.h \
    ilwisobjects/domain/domaintimetests.h \
    ilwisobjects/domain/numericdomaintests.h \
    ilwisobjects/domain/thematicdomaintests.h \
    ilwisobjects/domain/identifierdomaintests.h \
    ilwisobjects/domain/intervaldomaintests.h \
    ilwisobjects/coverage/vertexiteratortests.h \
    ilwisobjects/table/tabletests.h \
    iterators/vertexiteratortest.h \
    iterators/pixeliteratortest.h \
    ilwisobjects/coverage/rastercoveragetest.h \
    ilwisobjects/coverage/featurecoveragetest.h

unix|win32: LIBS += -L$$PWD/../../libraries/$$PLATFORM$$CONF/TestSuite/ -lTestSuite

INCLUDEPATH += $$PWD/../TestSuite
DEPENDPATH += $$PWD/../TestSuite

OTHER_FILES += \
    testfiles/test_without_xml_header.xml \
    testfiles/test.xml

testfiles.files = \
    testfiles/test_without_xml_header.xml \
    testfiles/test.xml

testfiles.path = $$PWD/../../output/$$PLATFORM$$CONF/bin/testcases/testfiles

INSTALLS += testfiles
