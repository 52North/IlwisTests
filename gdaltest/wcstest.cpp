#include "ilwis.h"
#include "testsuite.h"
#include "kernel.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "raster.h"
#include "attributerecord.h"
#include "feature.h"
#include "featurecoverage.h"
#include "featureiterator.h"
#include "catalog.h"
#include "pixeliterator.h"
#include "ilwiscontext.h"
#include "wcstest.h"


REGISTER_TEST(WCSTest);

WCSTest::WCSTest() : IlwisTestCase("WCSTest","GdalConnectorTest")
{
}

void WCSTest::getCapabilities() {
    Ilwis::ICatalog wcsCatalog("http://ogi.state.ok.us/geoserver/wcs?VERSION=1.1.0&REQUEST=GetCapabilities&SERVICE=WCS");

    DOTEST(wcsCatalog.isValid(), "opened wcs catalog");
}
