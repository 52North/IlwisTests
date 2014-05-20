#ifndef TST_WFSPARSERTEST_H
#define TST_WFSPARSERTEST_H

#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

#include "wfs.h"

namespace Ilwis {

class FeatureCoverage;

namespace Wfs {

class WfsParserTest : public IlwisTestCase
{
    Q_OBJECT

public:
    WfsParserTest();

private:
    NEW_TEST(WfsParserTest);

    void prepareCoverage(FeatureCoverage *fcoverage, Resource resource);

private Q_SLOTS:
    void parseCorrectNumberOfFeatureTypesFromCapabilities();

    void shouldParseQuad100FeatureCollection();
    void shouldParseGreenlandElevationContoursFeatureCollection();
    void shouldParseSioseINSPIRE_lu_es_14_FeatureCollection();

};
}
}

#endif // TST_WFSPARSERTEST_H
