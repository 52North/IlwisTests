QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-sign-compare
QMAKE_CXXFLAGS += -Wno-unused-local-typedefs
QMAKE_CXXFLAGS += -Wno-deprecated-declarations

CONFIG(debug, debug|release) {
CONF=debug
}

CONFIG(release, debug|release) {
CONF=release
}

OUTDIR = $$PWD/../output/$$CONF
PLATFORM = generic
win32{
    PLATFORM = win32
}

QT += sql

BOOST = $$PWD/../../external
RELATIVE = ../../..
OUTPUTPATH = $$PWD/../../output/bin

unix|win32: LIBS += -L$$PWD/../../libraries/win32debug/core/ -lilwiscore
unix|win32: LIBS += -L$$PWD/../../libraries/win32debug/ -llibgeos
unix|win32: LIBS += -L$$PWD/../../libraries/win32debug/ -llibgeos

INCLUDEPATH += $$PWD/../../IlwisCore/core
DEPENDPATH += $$PWD/../../IlwisCore/core

INCLUDEPATH +=  $$RELATIVE/IlwisCore/core \
                $$RELATIVE/IlwisCore/core/ilwisobjects \
                $$RELATIVE/IlwisCore/core/ilwisobjects/geometry \
                $$RELATIVE/IlwisCore/core/util \
                $$RELATIVE/IlwisCore/core/ilwisobjects/geometry/geodeticdatum \
                $$RELATIVE/IlwisCore/core/ilwisobjects/geometry/projection \
                $$RELATIVE/IlwisCore/core/ilwisobjects/geometry/coordinatesystem \
                $$RELATIVE/IlwisCore/core/ilwisobjects/geometry/georeference \
                $$RELATIVE/IlwisCore/core/ilwisobjects/coverage \
                $$RELATIVE/IlwisCore/core/ilwisobjects/table \
                $$RELATIVE/IlwisCore/core/ilwisobjects/operation \
                $$RELATIVE/IlwisCore/core/catalog \
                $$RELATIVE/IlwisCore/core/ilwisobjects/domain \
                $$BOOST

INCLUDEPATH +=  $$PWD/../../external/geos
DEPENDPATH +=   $$PWD/../../external/geos



