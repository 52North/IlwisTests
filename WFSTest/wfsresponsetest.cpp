
#include <QTest>
#include <QFile>

#include "wfsresponse.h"
#include "wfsresponsetest.h"

#include "testutils.h"
#include "testsuite.h"

using namespace Ilwis;
using namespace Wfs;

REGISTER_TEST(WfsResponseTest);

WfsResponseTest::WfsResponseTest():
    IlwisTestCase("WfsResponseTest", "WfsConnectorTest")
{
}

void WfsResponseTest::shouldRecognizeExceptionReport()
{
    WfsResponse testResponse(Utils::openFile("testcases/testfiles/wfs_exceptionreport.xml"));
    DOTEST2(testResponse.isException(), "Response did not recognized exception report!");
}

void WfsResponseTest::shouldParseExceptionReportWithDetails()
{
    WfsResponse testResponse(Utils::openFile("testcases/testfiles/wfs_exceptionreport.xml"));
    DOTEST2( !testResponse.parseException().isEmpty(), "No Exception report could be parsed!");
}

void WfsResponseTest::shouldNotRecognizeExceptionReport()
{
    WfsResponse testResponse(Utils::openFile("testcases/testfiles/wfs_capabilities.xml"));
    DOTEST2( !testResponse.isException(), "Response recognized an exception message!");
}
