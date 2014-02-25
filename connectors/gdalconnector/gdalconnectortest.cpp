#include "ilwis.h"
#include "testsuite.h"
#include "gdalconnectortest.h"
#include "kernel.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "coverage.h"
#include "attributerecord.h"
#include "feature.h"
#include "featurecoverage.h"

#include "catalog.h"
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

void GDALConnectorTest::standaloneTableLoad(){
    Ilwis::Catalog cat;
    cat.prepare(QUrl(_baseDataPath.absolutePath() + "/shape/"));
    Ilwis::context()->setWorkingCatalog(cat);
    Ilwis::ITable tbl1("rainfall.shp");
    DOTEST(!tbl1->isInternalObject(),"Table rainfall.shp loaded from file");

    DOTEST(tbl1.isValid(),"Table rainfall.shp succesfully loaded");
}

void GDALConnectorTest::tableLoadTests(){

    QUrl file = QUrl::fromLocalFile(_baseDataPath.absolutePath() + "/shape/rainfall.shp");
    Ilwis::ITable tbl1(file.toString());
    DOTEST(!tbl1->isInternalObject(),"Table rainfall.shp loaded from file");

    DOTEST(tbl1.isValid(),"Table rainfall.shp succesfully loaded");
    DOCOMPARE(tbl1->recordCount(),(unsigned int)0,"record count is zero if binary data not loaded!");//TODO to be guarded
    DOTEST(tbl1->cell(1,0).toString() == "UMSS", "column test 1");
    DOCOMPARE(tbl1->recordCount(),(unsigned int)13,"check record count");
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
