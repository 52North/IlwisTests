#include "ilwis.h"
#include "testsuite.h"
#include "gdalconnectortest.h"
#include "kernel.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"

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
    QUrl file = QUrl::fromLocalFile(_baseDataPath.absolutePath() + "/shape/rainfall.shp");
    Ilwis::ITable tbl1(file.toString());

    DOTEST(tbl1.isValid(),"Table rainfall.shp succesfully loaded");
    DOTEST(tbl1->cell(1,0).toString() == "UMSS", "column test 1");
    DOTEST(tbl1->cell("APRIL",0).toInt() == 36, "column test 2");
    DOTEST(tbl1->cell("JUNE",2).toInt() == 35, "column test 3");
    DOTEST(tbl1->cell("NOVEMBER",4).toInt() == 81, "column test 4");

    file = QUrl::fromLocalFile(_baseDataPath.absolutePath() + "/shape/regions.shp");
    DOTEST(tbl1.prepare(file.toString()), "Loaded table regions.shp");

    DOTEST(tbl1->cell("REGIONNAME",3).toString() == "Dire Dawa", "column test 5");
    DOTEST(tbl1->cell("COUNT",7).toDouble() == 34.0, "column test 6");


}

void GDALConnectorTest::tableStoreTests(){

}

void GDALConnectorTest::rasterLoadTests() {

}

void GDALConnectorTest::rasterStoreTests() {

}

void GDALConnectorTest::featureLoadTests() {

}

void GDALConnectorTest::featureStoreTests() {

}

void GDALConnectorTest::attributeLoadTests() {

}

void GDALConnectorTest::attributeStoreTests() {

}
