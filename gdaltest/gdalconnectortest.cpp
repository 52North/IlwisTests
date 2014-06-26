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
#include "featureiterator.h"
#include "catalog.h"
#include "catalogview.h"
#include "ilwiscontext.h"

REGISTER_TEST(GDALConnectorTest);

GDALConnectorTest::GDALConnectorTest() : IlwisTestCase("GdalConnectorTest", "GdalConnectorTest")
{

}

void GDALConnectorTest::tableLoadTests(){

    try{
        QString localfld = _baseDataPath.absolutePath();
        QUrl file = QUrl::fromLocalFile( localfld + "/rainfall.shp");
        Ilwis::ITable tbl1(file.toString());
        DOTEST(tbl1.isValid(),"Table rainfall.shp succesfully loaded");
        DOTEST(!tbl1->isInternalObject(),"Table rainfall.shp loaded from file");

        DOCOMPARE(tbl1->recordCount(),(unsigned int)13,"check record count");
        DOTEST(tbl1->columnIndex("FEBRUARY") != Ilwis::iUNDEF, "columns are loaded");

    } catch(const Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1()) ;
    }

}

void GDALConnectorTest::tableStoreTests(){

}

void GDALConnectorTest::rasterLoadTests() {
    try{
        Ilwis::IRasterCoverage map1;
        DOTEST(map1.prepare( makeInputPath("a_200006_bv.img")),"basic loading idl file");

        DOTEST(map1.prepare( makeInputPath("f41078a1.tif")),"basic loading raster, geotiff");

        DOTEST(map1.prepare(makeInputPath("kenya_2009ndvi_cor_22.img")),"loading erdas imagine file");

        DOTEST(map1.prepare(makeInputPath("GCL_INT.tif")),"loading geotiff");

        DOTEST(map1.prepare(makeInputPath("colordem.tif")),"loading geotiff with colors");


    } catch(const Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1()) ;
    }

}

void GDALConnectorTest::rasterStoreTests() {
    try{
        Ilwis::IRasterCoverage map1;
        qDebug() << "Test the output result in suitable client";
        QString res = makeInputPath("average_monthly_temperature_august_2.mpr");
        map1.prepare(res);

        qDebug() << "storing to ilwis3 format; value map; output result is aaraster1.mpr";

        res = QString(makeInputPath("aaraster1.mpr"));
        map1->connectTo(res, "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
        map1->createTime(Ilwis::Time::now());
        map1->store();

        res = QString(makeInputPath("n000302.mpr"));
        DOTEST(map1.prepare(res), "loading mpr");
        qDebug() << "loading ilwis3, toring as geotif; output os aaraster2.tif";
        map1->connectTo(makeOutputPath("aaraster2.tif"), "GTiff","gdal",Ilwis::IlwisObject::cmOUTPUT);
        map1->createTime(Ilwis::Time::now());
        map1->store();


        qDebug() << "storing to ilwis3 format, maplist; value map; output result is aa2.mpl";
        qDebug() << "TODO this test case fails for unknown reason; the write gives an bad_alloc exception in grid.h : 47. debug later";

        //    map1.prepare(QString("file:///%1/other/hanigodu-megelta4.img").arg(_baseDataPath.absolutePath()));
        //    map1->connectTo(QString("file:///%1/aa2.mpr").arg(_baseDataPath.absolutePath()), "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
        //    map1->setCreateTime(Ilwis::Time::now());
        //    map1->store();

    } catch(const Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1()) ;
    }

}

void GDALConnectorTest::featureLoadTests() {
    try {

        Ilwis::IFeatureCoverage fc;
        QString res = makeInputPath("woredas.shp");

        DOTEST(fc.prepare(res) == true,"basic loading feature coverage, polygons");

        DOTEST(fc.prepare(makeInputPath("rainfall.shp")),"basic loading feature coverage, points");

        DOTEST(fc.prepare(makeInputPath("drainage.shp")), "basic loading feature coverage, lines");

    } catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void GDALConnectorTest::featureStoreTests() {
    try{
       qDebug() << "Storing features. Test the output result in suitable client";

       Ilwis::IFeatureCoverage fc;

       DOTEST(fc.prepare(makeInputPath("Rainfall.mpp")), "loading point map");
       qDebug() << "storing as shape; output aapoints1.shp";
       fc->connectTo(makeOutputPath("aapoints1.shp"),"ESRI Shapefile", "gdal", Ilwis::IlwisObject::cmOUTPUT);
       fc->store();

       DOTEST(fc.prepare(makeInputPath("Drainage.mps")),"loading segment map");
       qDebug() << "storing as shape; output aalines1.shp";
       fc->connectTo(makeOutputPath("aalines1.shp"),"ESRI Shapefile", "gdal", Ilwis::IlwisObject::cmOUTPUT);
       fc->store();

       DOTEST(fc.prepare(makeInputPath("soils_sadc.mpa")),"loading polygon map");
       qDebug() << "storing as shape; output aapolygons1.shp";
       fc->connectTo(makeOutputPath("aapolygons1.shp"),"ESRI Shapefile", "gdal", Ilwis::IlwisObject::cmOUTPUT);
       fc->store();

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }


}

/*void GDALConnectorTest::catalogLoadTests(){
    try{
        qDebug() << "Loading Catalog. Test the output result in suitable client";

        Ilwis::CatalogView cat(QUrl(QString("file:///%1/101_101.gpx").arg(_baseDataPath.absolutePath())));
        cat.prepare();
        DOCOMPARE(cat.isValid(), true, "is catalog valid");
        std::vector<Ilwis::Resource> res = cat.items();
        DOCOMPARE(res.size(), (unsigned int)10, "this gpx always has 10 object, 5 layers and 5 attribute tables");

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}*/




