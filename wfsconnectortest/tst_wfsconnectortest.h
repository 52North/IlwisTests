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
    void parseFeatureTypesFromCapabilities();
    void cleanupTestCase();

private:
    void sandbox();
    void canUseValidWfsUrlWithCapitalParameters();
    void canUseValidWfsUrlWithMixedCapitalParameters();
    WebFeatureService *_wfs;

};

#endif // TST_WFSCONNECTORTEST_H
