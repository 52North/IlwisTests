#ifndef TST_WFSCONNECTORTEST_H
#define TST_WFSCONNECTORTEST_H

#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

#include "wfs.h"

using namespace Ilwis;
using namespace Wfs;

class QUrl;

class WfsConnectorTest : public IlwisTestCase
{
    Q_OBJECT

public:
    WfsConnectorTest();

private:
    NEW_TEST(WfsConnectorTest);

    WebFeatureService *_wfs;
    void sandbox();

private Q_SLOTS:

    void initTestCase();
    void shouldRecognizeExceptionReport();
    void shouldNotRecognizeExceptionReport();
    void shouldParseExceptionReportWithDetails();
    void parseCorrectNumberOfFeatureTypesFromCapabilities();
    void shouldCreateITableFromFeatureDescription();
    void shouldPrepareWfsFeature();
    void testInitialFeatureHasEmptyBBox();
    void canUseValidWfsUrlWithCapitalParameters();
    void canUseValidWfsUrlWithMixedCapitalParameters();
    void cleanupTestCase();

};

#endif // TST_WFSCONNECTORTEST_H
