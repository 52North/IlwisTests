#include <QColor>
#include "ilwis.h"
#include "../TestSuite/testsuite.h"
#include "kernel.h"
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
#include "attributerecord.h"
#include "feature.h"
#include "featurecoverage.h"
#include "featureiterator.h"
//#include "ilws3connectorloaders.h"
#include "dataaccess.h"


REGISTER_TEST(DataAccess);

DataAccess::DataAccess() : IlwisTestCase("DataAccess", "Ilwis3ConnectorTest")
{
}

void DataAccess::initTestCase()
{
    _baseDataPath = TestSuite::instance()->inputDataPath();
    if ( !_baseDataPath.exists())
        throw SkipTest("no data path defined");
    _baseDataOutputPath = TestSuite::instance()->outputDataPath();
    if ( !_baseDataOutputPath.exists())
        throw SkipTest("no data output path defined");
}

void DataAccess::rasters(){
    Ilwis::IRasterCoverage map1(QString("file:///%1/n000302.mpr").arg(_baseDataPath.absolutePath()));

    DOCOMPARE(map1->coord2value(Ilwis::Coordinate(112109.75,128832.51)), 71.0, "accesing raster through coordinate");

    DOCOMPARE(map1->pix2value(Ilwis::Pixel(564, 623)), 169.0, "accessing raster through pixel");

    map1.prepare(QString("file:///%1/kenya_2009ndvi_cor_22.mpr").arg(_baseDataPath.absolutePath()));

    DOCOMPARE(map1->pix2value(Ilwis::Pixel(416,501)), 0.232, "accessing raster through georef submap");

    map1.prepare(QString("file:///%1/tmb1.mpr").arg(_baseDataPath.absolutePath()));

    DOCOMPARE(map1->coord2value(Ilwis::Coordinate(800827.47,8083453.21)), 40.0,"accessing raster through tiepoint georef");

    map1.prepare(QString("file:///%1/average_monthly_temperature.mpl").arg(_baseDataPath.absolutePath()));

    DOCOMPARE(map1->pix2value(Ilwis::Pixel(898,277,3)), 24.20,"Accessing pixels in a maplist");

    map1.prepare(QString("file:///%1/cc43.mpr").arg(_baseDataPath.absolutePath()));
    QColor clr = map1->datadef().domain<>()->impliedValue(map1->pix2value(Ilwis::Pixel(136,199))).value<QColor>();
    DOCOMPARE(clr, QColor(46,47,51), "accessing color values");
}

void DataAccess::features() {
    Ilwis::IFeatureCoverage features;

    features.prepare(QString("file:///%1/rainfall.mpp").arg(_baseDataPath.absolutePath()));

    Ilwis::FeatureIterator iter(features);
    Ilwis::UPFeatureI& f = *(iter + 4);
    DOCOMPARE(f("january").toInt(), 93,"accessing value of 4th feature, january attribute column");

    features.prepare(QString("file:///%1/Contour.mps").arg(_baseDataPath.absolutePath()));
    Ilwis::FeatureIterator iter2(features);
    Ilwis::UPFeatureI& f2 = *(iter2 + 10);
    DOCOMPARE(f2(FEATUREVALUECOLUMN).toInt(), 2600, "accessing map value of the 10th segment");

    features.prepare(QString("file:///%1/soils_sadc.mpa").arg(_baseDataPath.absolutePath()));
    Ilwis::FeatureIterator iter3(features);
    Ilwis::UPFeatureI& f3 = *(iter3 + 4);
    DOTEST(f3("FAOSOIL",false).toString() == "Rd18-3ab", "accessing attribute value of the 4th polygon");

}

void DataAccess::table() {
    Ilwis::ITable tbl;

    tbl.prepare(QString("file:///%1/rainfall.tbt").arg(_baseDataPath.absolutePath()));
    std::vector<QVariant> values = tbl->column("february");
    DOCOMPARE(values[2].toInt(), 165, "Accessing numerical column");

    tbl.prepare(QString("file:///%1/geom.tbt").arg(_baseDataPath.absolutePath()));

    DOCOMPARE(tbl->cell("zonation",1).toInt(), 1, "Accessing cell , getting raw value as return");
    DOTEST(tbl->cell("zonation",1, false).toString() == "Alluvial fan zone", "Accessing cell get string value as return");

}

