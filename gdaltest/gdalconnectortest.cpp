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

void GDALConnectorTest::initTestCase()
{
    _baseDataPath = TestSuite::instance()->inputDataPath();
    if ( !_baseDataPath.exists())
        throw SkipTest("no data path defined");
    _baseDataOutputPath = TestSuite::instance()->outputDataPath();
    if ( !_baseDataOutputPath.exists())
        throw SkipTest("no data output path defined");
}

void GDALConnectorTest::tableLoadTests(){

    try{
        QUrl file = QUrl::fromLocalFile(_baseDataPath.absolutePath() + "/shape/rainfall.shp");
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

        DOTEST(map1.prepare(QString("file:///%1/f41078a1.tif").arg(_baseDataPath.absolutePath())),"basic loading raster, geotiff");

        DOTEST(map1.prepare(QString("file:///%1/hanigodu-megelta4.img").arg(_baseDataPath.absolutePath())),"loading erdas imagine file");

        DOTEST(map1.prepare(QString("file:///%1/GCL_FLOAT.tif").arg(_baseDataPath.absolutePath())),"loading erdas imagine file");

    } catch(const Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1()) ;
    }

}

void GDALConnectorTest::rasterStoreTests() {
    try{
        Ilwis::IRasterCoverage map1;
        qDebug() << "Test the output result in suitable client";
        QString res = QString("file:///%1/average_monthly_temperature_august_2.tif").arg(_baseDataPath.absolutePath());
        map1.prepare(res);

        qDebug() << "storing to ilwis3 format; value map; output result is aaraster1.mpr";

        res = QString("file:///%1/aaraster1.mpr").arg(_baseDataPath.absolutePath());
        map1->connectTo(res, "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
        map1->setCreateTime(Ilwis::Time::now());
        map1->store();

        res = QString("file:///%1/n000302.mpr").arg(_baseDataPath.absolutePath());
        DOTEST(map1.prepare(res), "loading mpr");
        qDebug() << "loading ilwis3, toring as geotif; output os aaraster2.tif";
        map1->connectTo(res = QString("file:///%1/aaraster2.tif").arg(_baseDataPath.absolutePath()), "GTiff","gdal",Ilwis::IlwisObject::cmOUTPUT);
        map1->setCreateTime(Ilwis::Time::now());
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
        QString res = QString("file:///%1/shape/woredas.shp").arg(_baseDataPath.absolutePath());

        DOTEST(fc.prepare(res) == true,"basic loading feature coverage, polygons");

        DOTEST(fc.prepare(QString("file:///%1/shape/rainfall.shp").arg(_baseDataPath.absolutePath())),"basic loading feature coverage, points");

        DOTEST(fc.prepare(QString("file:///%1/shape/drainage.shp").arg(_baseDataPath.absolutePath())), "basic loading feature coverage, lines");

    } catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void GDALConnectorTest::featureStoreTests() {
    try{
       qDebug() << "Storing features. Test the output result in suitable client";

       Ilwis::IFeatureCoverage fc;

       DOTEST(fc.prepare(QString("file:///%1/Rainfall.mpp").arg(_baseDataPath.absolutePath())), "loading point map");
       qDebug() << "storing as shape; output aapoints1.shp";
       fc->connectTo(QString("file:///%1/aapoints1.shp").arg(_baseDataPath.absolutePath()),"ESRI Shapefile", "gdal", Ilwis::IlwisObject::cmOUTPUT);
       fc->store();

       DOTEST(fc.prepare(QString("file:///%1/Drainage.mps").arg(_baseDataPath.absolutePath())),"loading segment map");
       qDebug() << "storing as shape; output aalines1.shp";
       fc->connectTo(QString("file:///%1/aalines1.shp").arg(_baseDataPath.absolutePath()),"ESRI Shapefile", "gdal", Ilwis::IlwisObject::cmOUTPUT);
       fc->store();

       DOTEST(fc.prepare(QString("file:///%1/soils_sadc.mpa").arg(_baseDataPath.absolutePath())),"loading polygon map");
       qDebug() << "storing as shape; output aapolygons1.shp";
       fc->connectTo(QString("file:///%1/aapolygons1.shp").arg(_baseDataPath.absolutePath()),"ESRI Shapefile", "gdal", Ilwis::IlwisObject::cmOUTPUT);
       fc->store();

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }


}

void GDALConnectorTest::catalogLoadTests(){
    try{
        qDebug() << "Loading Catalog. Test the output result in suitable client";

        Ilwis::CatalogView cat;
        cat.prepare(QUrl(QString("file:///%1/gpx/101_101.gpx").arg(_baseDataPath.absolutePath())),"");
//        cat.prepare(QUrl(QString("file:///%1/pytest/feature/test.gpx").arg(_baseDataPath.absolutePath())),"");
        DOCOMPARE(cat.isValid(), true, "is catalog valid");
        std::vector<Ilwis::Resource> res = cat.items();
        DOCOMPARE(res.size(), (unsigned int)10, "this gpx always has 10 object, 5 layers and 5 attribute tables");

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}




