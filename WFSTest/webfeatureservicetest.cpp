#include "webfeatureservicetest.h"
#include "wfstestconstants.h"
#include "wfsmoduletest.h"
#include "wfs.h"

using namespace Ilwis;
using namespace Wfs;

WebFeatureServiceTest::WebFeatureServiceTest():
    IlwisTestCase("WebFeatureServiceTest","WfsConnectorTest")
{
}

void WebFeatureServiceTest::createWebFeatureService()
{
    QUrl wfsUrl(WFS_TEST_SERVER_1);
    _wfs = new WebFeatureService(wfsUrl);
}

void WebFeatureServiceTest::cleanupTestCase() {
    delete _wfs;
}

