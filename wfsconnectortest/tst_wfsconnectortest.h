#ifndef TST_WFSCONNECTORTEST_H
#define TST_WFSCONNECTORTEST_H

#include "wfsresponse.h"
#include "wfs.h"

using namespace Ilwis;
using namespace Wfs;

class QUrl;
class FeatureCoverage;

class WfsConnectorTest :  public QObject
{
    Q_OBJECT

public:
    WfsConnectorTest();

private Q_SLOTS:

    void initTestCase();
    void shouldRecognizeExceptionReport();
    void shouldNotRecognizeExceptionReport();
    void parseCorrectNumberOfFeatureTypesFromCapabilities();
    void shouldLoadFeatureMetadata();
    void testInitialFeatureHasEmptyBBox();
    void cleanupTestCase();

private:
    WebFeatureService *_wfs;
    QFile *_file;

    void sandbox();
    void canUseValidWfsUrlWithCapitalParameters();
    void canUseValidWfsUrlWithMixedCapitalParameters();

};

#endif // TST_WFSCONNECTORTEST_H
