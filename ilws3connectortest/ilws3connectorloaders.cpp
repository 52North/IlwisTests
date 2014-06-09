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

void Ilws3connectorTest::loadCoverages() {
    try{
        Ilwis::IRasterCoverage map1;
        QString res = makeInputPath("n000302.mpr");
        DOTEST(map1.prepare(res) == true,"loading raster map");

        Ilwis::IRasterCoverage map2;
        DOTEST(map2.prepare(makeInputPath("average_monthly_temperature.mpl")),"loading maplist");

        Ilwis::IRasterCoverage map3;
        DOTEST(map3.prepare(makeInputPath("Landuse.mpr")),"loading raster with thematic domain");

        Ilwis::IFeatureCoverage fc;
        DOTEST(fc.prepare(makeInputPath("soils_sadc.mpa")),"loading polygon map");

        DOTEST(fc.prepare(makeInputPath("countries.mpa")),"loading polygon map");

        Ilwis::IFeatureCoverage fc2;
        DOTEST(fc2.prepare(makeInputPath("Contour.mps")),"loading segment map");

        Ilwis::IFeatureCoverage fc3;
        DOTEST(fc3.prepare(makeInputPath("rainfall.mpp")),"loading point map");

        Ilwis::IIlwisObject obj;
        DOTEST(obj.prepare(makeInputPath("average_monthly_temperature_october_11.mpr")),"loading coverage as bare ilwis-object");


        res = makeInputPath("small3_grfnone.mpr");
        DOTEST(map1.prepare(res),"loading raster with georef none");

        res = makeInputPath("cc43.mpr");
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
        DOTEST(dom1.prepare(makeInputPath("landuse.dom")),"loading thematic domain");

        Ilwis::IDomain dom2;
        DOTEST(dom2.prepare(makeInputPath("landuse.dom")),"loading thematic domain");

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void Ilws3connectorTest::tables()
{
    try {
        Ilwis::ITable tbl;

        DOTEST(tbl.prepare(makeInputPath("rainfall.tbt")),"loading table, only numerical columns");

        DOTEST(tbl.prepare(makeInputPath("kenya.tbt")),"loading table, columns of various domains");

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }

}

void Ilws3connectorTest::loaderCsy() {
    try {
        Ilwis::ICoordinateSystem csy;
        DOTEST(csy.prepare(makeInputPath("cochabam.csy")),"loading regular projected csy");

        DOTEST(csy.prepare(makeInputPath("average_monthly_temperature_december_3.mpr")),"loading csy from raster");

        DOTEST(csy.prepare(makeInputPath("ethiopia_dem.csy")),"loading regular latlon csy");

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
        DOTEST(tbl1.prepare(makeInputPath("soils_sadc.tbt")),"loading table");

        Ilwis::IEllipsoid ell;
        DOTEST(ell.prepare("code=wkt:GRS 1980") == true,"loading ellipsoid from wkt");

        Ilwis::IProjection prj;
        DOTEST(prj.prepare(makeInputPath("cochabam.csy")),"loading projection from csy");


        Ilwis::IGeoReference grf;
        DOTEST(grf.prepare(makeInputPath("ethiopia_dem.grf")) == true,"loading regualr corners georef");

        DOTEST(grf.prepare(makeInputPath("tmgeo.grf")) == true,"loading regualr tiepoint georef");

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

