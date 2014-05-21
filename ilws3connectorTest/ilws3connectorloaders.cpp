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
#include "ilws3connectorloaders.h"


REGISTER_TEST(Ilws3connectorTest);

Ilws3connectorTest::Ilws3connectorTest() : IlwisTestCase("Ilwis3ConnectorTest","Ilwis3ConnectorTest")
{
}

void Ilws3connectorTest::initTestCase()
{
    _baseDataPath = TestSuite::instance()->inputDataPath();
    if ( !_baseDataPath.exists())
        throw SkipTest("no data path defined");
    _baseDataOutputPath = TestSuite::instance()->outputDataPath();
    if ( !_baseDataOutputPath.exists())
        throw SkipTest("no data output path defined");
}

void Ilws3connectorTest::loadCoverages() {
    try{
        Ilwis::IRasterCoverage map1;
        QString res = QString("file:///%1/n000302.mpr").arg(_baseDataPath.absolutePath());
        DOTEST(map1.prepare(res) == true,"loading raster map");

        Ilwis::IRasterCoverage map2;
        DOTEST(map2.prepare(QString("file:///%1/average_monthly_temperature.mpl").arg(_baseDataPath.absolutePath())),"loading maplist");

        Ilwis::IRasterCoverage map3;
        DOTEST(map3.prepare(QString("file:///%1/Landuse.mpr").arg(_baseDataPath.absolutePath())),"loading raster with thematic domain");

        Ilwis::IFeatureCoverage fc;
        DOTEST(fc.prepare(QString("file:///%1/soils_sadc.mpa").arg(_baseDataPath.absolutePath())),"loading polygon map");

        Ilwis::IFeatureCoverage fc2;
        DOTEST(fc2.prepare(QString("file:///%1/Contour.mps").arg(_baseDataPath.absolutePath())),"loading segment map");

        Ilwis::IFeatureCoverage fc3;
        DOTEST(fc3.prepare(QString("file:///%1/rainfall.mpp").arg(_baseDataPath.absolutePath())),"loading point map");

        Ilwis::IIlwisObject obj;
        DOTEST(obj.prepare(QString("file:///%1/average_monthly_temperature_october_11.mpr").arg(_baseDataPath.absolutePath())),"loading coverage as bare ilwis-object");


        res = QString("file:///%1/mpd4.mpr").arg(_baseDataPath.absolutePath());
        DOTEST(map1.prepare(res),"loading mpd4 raster");

        res = QString("file:///%1/cc43.mpr").arg(_baseDataPath.absolutePath());
        DOTEST(map1.prepare(res), "loading raster with domain color");


    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void Ilws3connectorTest::domainLoadingConstructing()
{
    try{
        Ilwis::IDomain dom1;
        DOTEST(dom1.prepare(QString("file:///%1/landuse.dom").arg(_baseDataPath.absolutePath())),"loading thematic domain");

        Ilwis::IDomain dom2;
        DOTEST(dom2.prepare(QString("file:///%1/landuse.dom").arg(_baseDataPath.absolutePath())),"loading thematic domain");

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void Ilws3connectorTest::tables()
{
    try {
        Ilwis::ITable tbl;

        DOTEST(tbl.prepare(QString("file:///%1/rainfall.tbt").arg(_baseDataPath.absolutePath())),"loading table, only numerical columns");

        DOTEST(tbl.prepare(QString("file:///%1/kenya.tbt").arg(_baseDataPath.absolutePath())),"loading table, columns of various domains");

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }

}

void Ilws3connectorTest::loaderCsy() {
    try {
        Ilwis::ICoordinateSystem csy;
        DOTEST(csy.prepare(QString("file:///%1/cochabam.csy").arg(_baseDataPath.absolutePath())),"loading regular projected csy");

        DOTEST(csy.prepare(QString("file:///%1/average_monthly_temperature_december_3.mpr").arg(_baseDataPath.absolutePath())),"loading csy from raster");

        DOTEST(csy.prepare(QString("file:///%1/ethiopia_dem.csy").arg(_baseDataPath.absolutePath())),"loading regular latlon csy");

        DOTEST(csy.prepare("code=epsg:5464"), "loading projected csy from epsg");

        DOTEST(csy.prepare("code=proj4:+proj=utm +zone=29 +a=6378249.2 +b=6356515 +towgs84=-23,259,-9,0,0,0,0"),"loading from proj4 definition");

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }

}

void Ilws3connectorTest::loaderGeometryThings() {
    try{

        Ilwis::ITable tbl1;
        DOTEST(tbl1.prepare(QString("file:///%1/soils_sadc.tbt").arg(_baseDataPath.absolutePath())),"loading table");

        Ilwis::IEllipsoid ell;
        DOTEST(ell.prepare("code=wkt:GRS 1980") == true,"loading ellipsoid from wkt");

        Ilwis::IProjection prj;
        DOTEST(prj.prepare(QString("file:///%1/cochabam.csy").arg(_baseDataPath.absolutePath())),"loading projection from csy");


        Ilwis::IGeoReference grf;
        DOTEST(grf.prepare(QString("file:///%1/ethiopia_dem.grf").arg(_baseDataPath.absolutePath())) == true,"loading regualr corners georef");

        DOTEST(grf.prepare(QString("file:///%1/tmgeo.grf").arg(_baseDataPath.absolutePath())) == true,"loading regualr tiepoint georef");

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

