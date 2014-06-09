#include "geos/io/ParseException.h"
#include "ilwis.h"
#include "testsuite.h"
#include "gdalconnectortest.h"
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
#include "catalog.h"
#include "ilwiscontext.h"
#include "catalogtest.h"
#include "featureiterator.h"
#include "geometryhelper.h"

REGISTER_TEST(CatalogTest);

CatalogTest::CatalogTest() : IlwisTestCase("GdalCatalogTest","GdalConnectorTest")
{
}

void CatalogTest::readCatalog() {

    Ilwis::ICatalog cat(makeInputPath("101_101.gpx"));
    DOTEST(cat.isValid(),"is valid gpx catalog");
    std::vector<Ilwis::Resource> items = cat->items();
    DOCOMPARE(items.size(), (unsigned int)10, " 10 objects in the catalog, 5 layers, 5 attribute tables");
    Ilwis::context()->setWorkingCatalog(cat);

    Ilwis::IFeatureCoverage fc("track_points");
    DOTEST(fc.isValid(),"loading points from gpx file");

    Ilwis::FeatureIterator iter(fc);
    Ilwis::UPFeatureI& feature = *iter;
    QString wkt = Ilwis::GeometryHelper::toWKT(feature->geometry().get());
    DOTEST(wkt == "POINT (4.3558570000000003 52.0103980000000021)","loading geometry from point layer");

    Ilwis::ICatalog cat2(makeInputPath(""));
    Ilwis::context()->setWorkingCatalog(cat2);

    Ilwis::IFeatureCoverage fc2("101_101.gpx/track_points");
    DOTEST(fc2.isValid(),"loading points from gpx file");



}
