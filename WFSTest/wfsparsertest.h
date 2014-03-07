#ifndef TST_WFSPARSERTEST_H
#define TST_WFSPARSERTEST_H

#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

#include "wfs.h"

using namespace Ilwis;
using namespace Wfs;

class QUrl;

class WfsParserTest : public IlwisTestCase
{
    Q_OBJECT

public:
    WfsParserTest();

private:
    NEW_TEST(WfsParserTest);

    void shouldParseSioseINSPIRE_lu_es_14_FeatureCollection(); // seg_faults when parsing inner rings :/

private Q_SLOTS:
    void parseCorrectNumberOfFeatureTypesFromCapabilities();

    void shouldParseQuad100FeatureCollection();
    void shouldParseGreenlandElevationContoursFeatureCollection();

};

#endif // TST_WFSPARSERTEST_H
