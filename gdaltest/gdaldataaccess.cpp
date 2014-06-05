#include "ilwis.h"
#include "testsuite.h"
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
#include "pixeliterator.h"
#include "ilwiscontext.h"
#include "gdaldataaccess.h"

REGISTER_TEST(GdalDataAccess);

GdalDataAccess::GdalDataAccess() : IlwisTestCase("GdalDataAccess", "GdalConnectorTest")
{
}

void GdalDataAccess::tableAccess(){

    QUrl file = QUrl::fromLocalFile(_baseDataPath.absolutePath() + "/shape/rainfall.shp");
    Ilwis::ITable tbl1;
    DOTEST(tbl1.prepare(file.toString()),"loading table from shape");

    DOCOMPARE(tbl1->recordCount(),(unsigned int)13,"check record count");
    DOTEST(tbl1->cell(1,0).toString() == "UMSS", "column test 1");
    DOTEST(tbl1->cell("APRIL",0).toInt() == 36, "column test 2");
    DOTEST(tbl1->cell("JUNE",2).toInt() == 35, "column test 3");
    DOTEST(tbl1->cell("NOVEMBER",4).toInt() == 81, "column test 4");

    file = QUrl::fromLocalFile(_baseDataPath.absolutePath() + "/shape/regions.shp");
    DOTEST(tbl1.prepare(file.toString()), "Loaded table regions.shp");

    DOTEST(tbl1->cell("REGIONNAME",3).toString() == "Dire Dawa", "column test 5");
    DOTEST(tbl1->cell("COUNT",7).toDouble() == 34.0, "column test 6");
}

void GdalDataAccess::accessingFeatureData() {
    try {
        Ilwis::IFeatureCoverage fc;
        qDebug() << "Features : accessing data ";

        DOTEST(fc.prepare(QString("file:///%1/shape/regions.shp").arg(_baseDataPath.absolutePath())), "Loading regions.shp");
        QString env = fc->envelope().toString();
        DOTEST(env == "POLYGON(33.0065 3.40088,47.9605 14.9637)","FeatureCoverage: testing envelope (bbox)");

        DOTEST(fc.prepare(QString("file:///%1/shape/rainfall.shp").arg(_baseDataPath.absolutePath())),"loading point map");
        Ilwis::FeatureIterator iter1(fc);

        Ilwis::UPFeatureI& f1 = *(iter1 + 1);
        QVariant output = f1->cell("RAINFALL");
        DOTEST(output.toString() =="taquina","accesing attribute string data of pointmap");

        Ilwis::UPFeatureI& f2 = *(iter1 + 4);
        output = f2("JANUARY");
        DOCOMPARE(output.toInt(), 85 ,"accesing attribute numeric data of pointmap");

        DOTEST(fc.prepare(QString("file:///%1/shape/drainage.shp").arg(_baseDataPath.absolutePath())),"loading segment map");
        Ilwis::FeatureIterator iter2(fc);

        Ilwis::UPFeatureI& f3 = *(iter2 + 104);
        output = f3->cell("DRAINAGE");
        DOTEST(output.toString() == "lake","accesing attribute string data of line coverage");

        Ilwis::UPFeatureI& f4 = *(iter2 + 21);
        output = f4("C1");
        DOCOMPARE(output.toInt(), 1 ,"accesing attribute numeric data ofline coverage");

        DOTEST(fc.prepare(QString("file:///%1/shape/geology.shp").arg(_baseDataPath.absolutePath())),"loading polygon map");
        Ilwis::FeatureIterator iter3(fc);

        Ilwis::UPFeatureI& f5 = *(iter3 + 40);
        output = f5->cell("GEOLOGY");
        DOTEST(output.toString() == "Shales","accesing attribute string data of polygon coverage");


    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void GdalDataAccess::accessingRasterData() {
    try {
        qDebug() << "Gridcoverage: access value through GDAL";

        Ilwis::IRasterCoverage raster(QString("file:///%1/f41078a1.tif").arg(_baseDataPath.absolutePath()));
        DOCOMPARE(raster->pix2value(Ilwis::Pixel(3278,2669)), 4.0,"accessing numerical value raster map");

        raster.prepare(QString("file:///%1/GCL_INT.tif").arg(_baseDataPath.absolutePath()));
        DOCOMPARE(raster->pix2value(Ilwis::Pixel(239,297,23)), 48.0, "accessing numerical value in stack of raster (layer 24)");

    }catch (const Ilwis::ErrorObject& err) {
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }


}
