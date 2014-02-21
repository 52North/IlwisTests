#ifndef TST_WFSCONNECTORTEST_H
#define TST_WFSCONNECTORTEST_H

#include "wfsresponse.h"
#include "wfs.h"

using namespace Ilwis;
using namespace Wfs;

class QUrl;

class WfsConnectorTest :  public QObject
{
    Q_OBJECT

public:
    WfsConnectorTest();

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

private:
    WebFeatureService *_wfs;

    void sandbox();

};

#endif // TST_WFSCONNECTORTEST_H
