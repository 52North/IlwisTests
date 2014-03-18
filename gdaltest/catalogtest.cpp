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

REGISTER_TEST(CatalogTest);

CatalogTest::CatalogTest() : IlwisTestCase("GdalCatalogTest","GdalConnectorTest")
{
}

void CatalogTest::initTestCase()
{
    _baseDataPath = TestSuite::instance()->inputDataPath();
    if ( !_baseDataPath.exists())
        throw SkipTest("no data path defined");
    _baseDataOutputPath = TestSuite::instance()->outputDataPath();
    if ( !_baseDataOutputPath.exists())
        throw SkipTest("no data output path defined");
}

void CatalogTest::readCatalog() {
    DOTEST(Ilwis::mastercatalog()->addContainer(QUrl(QString("file:///%1/gpx").arg(_baseDataPath.absolutePath()))),"adding catalog with gpx file");

    Ilwis::ICatalog cat(QString("file:///%1/gpx/101_101.gpx").arg(_baseDataPath.absolutePath()));
    DOTEST(cat.isValid(),"is valid gpx catalog");
    DOTEST(cat->items().size() == 5, " 5 layers in the catalog");

    DOTEST(Ilwis::IFeatureCoverage(cat->items()[2]).isValid(),"loading lines from gpx file");

}
