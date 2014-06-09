#include "kernel.h"
#include "testsuite.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "raster.h"
#include "coverage.h"
#include "ellipsoid.h"
#include "projection.h"
#include "coordinatesystem.h"
#include "raster.h"
#include "pixeliterator.h"
#include "attributerecord.h"
#include "geometryhelper.h"
#include "numericdomain.h"
#include "juliantime.h"
#include "operationhelper.h"
#include "rastercoveragetest.h"


REGISTER_TEST(RasterCoverageTest);

RasterCoverageTest::RasterCoverageTest() : IlwisTestCase("RasterCovergeTest","CoreTest")
{
}


void RasterCoverageTest::bands(){
    Ilwis::IRasterCoverage raster(makeInputPath("average_monthly_temperature.mpl"));
    DOTEST(raster.isValid(),"map list loaded");
    double origvalue1 = raster->pix2value(Ilwis::Pixel(500,500,3));
    double origvalue2 = raster->pix2value(Ilwis::Pixel(500,500,4));

    Ilwis::IRasterCoverage raster2;
    raster2.prepare();
    Ilwis::PixelIterator iter = raster->band(3);
    Ilwis::PixelIterator iter2 = raster->band(4);

    Ilwis::ITimeDomain dom;
    dom.prepare();
    dom->range(new Ilwis::TimeInterval("20090101", "20100101",{"30D"}));
    raster2->indexDomain(dom);


    raster2->band("20090131",iter);
    raster2->band("20090302",iter2);

    DOTEST(raster2->pix2value(Ilwis::Pixel(500,500,0)) == origvalue1,"same value as original1");
    DOTEST(raster2->pix2value(Ilwis::Pixel(500,500,1)) == origvalue2,"same value as original2");



}
