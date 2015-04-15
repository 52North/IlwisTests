#include <QColor>
#include "ilwis.h"
#include "../TestSuite/testsuite.h"
#include "raster.h"
#include "table.h"
#include "ellipsoid.h"
#include "projection.h"
#include "featurecoverage.h"
#include "feature.h"
#include "featureiterator.h"
//#include "ilwis3connectorloaders.h"
#include "dataaccess.h"


REGISTER_TEST(DataAccess);

DataAccess::DataAccess() : IlwisTestCase("DataAccess", "Ilwis3ConnectorTest")
{
}

void DataAccess::rasters(){
    Ilwis::IRasterCoverage map1(makeInputPath("n000302.mpr"));

    DOCOMPARE(map1->coord2value(Ilwis::Coordinate(112109.75,128832.51)), 71.0, "accesing raster through coordinate");

    DOCOMPARE(map1->pix2value(Ilwis::Pixel(564, 623)), 169.0, "accessing raster through pixel");

    map1.prepare(makeInputPath("kenya_2009ndvi_cor_22.mpr"));

    DOCOMPARE(map1->pix2value(Ilwis::Pixel(416,501)), 0.232, "accessing raster through georef submap");

    map1.prepare(makeInputPath("tmb1.mpr"));

    DOCOMPARE(map1->coord2value(Ilwis::Coordinate(800827.47,8083453.21)), 40.0,"accessing raster through tiepoint georef");

    map1.prepare(makeInputPath("average_monthly_temperature.mpl"));

    DOCOMPARE(map1->pix2value(Ilwis::Pixel(898,277,3)), 24.20,"Accessing pixels in a maplist");

    map1.prepare(makeInputPath("cc43.mpr"));
    QColor clr = map1->datadef().domain<>()->impliedValue(map1->pix2value(Ilwis::Pixel(136,199))).value<QColor>();
    DOCOMPARE(clr, QColor(46,47,51), "accessing color values");
}

void DataAccess::features() {
    Ilwis::IFeatureCoverage features;

    features.prepare(makeInputPath("rainfall.mpp"));

    Ilwis::FeatureIterator iter(features);
    Ilwis::SPFeatureI f = *(iter + 4);
    DOCOMPARE(f("january").toInt(), 93,"accessing value of 4th feature, january attribute column");

    features.prepare(makeInputPath("Contour.mps"));
    Ilwis::FeatureIterator iter2(features);
    Ilwis::SPFeatureI f2 = *(iter2 + 10);
    DOCOMPARE(f2(FEATUREVALUECOLUMN).toInt(), 2600, "accessing map value of the 10th segment");

    features.prepare(makeInputPath("soils_sadc.mpa"));
    Ilwis::FeatureIterator iter3(features);
    Ilwis::SPFeatureI f3 = *(iter3 + 4);
    auto result = f3->cell(QString("FAOSOIL"),false);
    DOTEST(result.toString() == "Rd18-3ab", "accessing attribute value of the 4th polygon");

}

void DataAccess::table() {
    Ilwis::ITable tbl;

    tbl.prepare(makeInputPath("rainfall.tbt"));
    std::vector<QVariant> values = tbl->column("february");
    DOCOMPARE(values[2].toInt(), 165, "Accessing numerical column");

    tbl.prepare(makeInputPath("geom.tbt"));

    DOCOMPARE(tbl->cell("zonation",1).toInt(), 1, "Accessing cell , getting raw value as return");
    DOTEST(tbl->cell("zonation",1, false).toString() == "Alluvial fan zone", "Accessing cell get string value as return");

}

