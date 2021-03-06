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
#include "featurecoverage.h"
#include "feature.h"
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
    Ilwis::SPFeatureI feature = *iter;
    QString wkt = Ilwis::GeometryHelper::toWKT(feature->geometry().get());
    DOTEST(wkt == "POINT (4.3558570000000003 52.0103980000000021)","loading geometry from point layer");

    Ilwis::ICatalog cat2(makeInputPath(""));
    Ilwis::context()->setWorkingCatalog(cat2);

    Ilwis::IFeatureCoverage fc2("101_101.gpx/track_points");
    DOTEST(fc2.isValid(),"loading points from gpx file");



}

void CatalogTest::wcsCatalog() {
   //Ilwis::ICatalog cat("http://ogi.state.ok.us/geoserver/wcs?version=1.1.0&request=GetCapabilities&service=WCS");
   Ilwis::ICatalog cat("http://sdf.ndbc.noaa.gov/thredds/wcs/hfradar_usegc_1km?request=GetCapabilities&version=1.0.0&service=WCS");
   DOTEST(cat.isValid(),"Succesfully created wcs catalog");
}

void CatalogTest::hdf5Catalog() {
    Ilwis::ICatalog cat(makeInputPath("INTER_OPER_R___TAVGD___L3__20100101T000000_20100102T000000_0003.nc"));
    DOTEST(cat.isValid(),"Succesfully created hdf5 catalog");

    Ilwis::context()->setWorkingCatalog(cat);
    Ilwis::IRasterCoverage raster("lat");

    DOTEST(raster.isValid(),"created raster band lat succesfully");

    DOTESTAPP(raster->pix2value(Ilwis::Pixel(99,101)), 51.6271, 0.001, "reading values from band lat");

    Ilwis::ICatalog cat2(makeInputPath(""));
    Ilwis::context()->setWorkingCatalog(cat2);

    raster.prepare("INTER_OPER_R___TAVGD___L3__20100101T000000_20100102T000000_0003.nc/lon");

    DOTEST(raster.isValid(),"created raster band with relative path to lon succesfully");

    DOTESTAPP(raster->pix2value(Ilwis::Pixel(99,101)), 4.7095, 0.001, "reading values from band lon");
}
