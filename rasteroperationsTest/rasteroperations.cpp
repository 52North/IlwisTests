#include "kernel.h"
#include "ilwiscontext.h"
#include "testsuite.h"
#include "catalog.h"
#include "raster.h"
#include "ilwisoperation.h"
#include "rasteroperations.h"


REGISTER_TEST(RasterOperations);


using namespace Ilwis;
using namespace boost;


RasterOperations::RasterOperations() : IlwisTestCase("Applications", "RasterOperationsTest")
{
}

void RasterOperations::testMirrorRotate() {
    try {
        QString expr = QString("aamirvert=mirrorrotateraster(small.mpr,rotate180)");
        Ilwis::ExecutionContext ctx;
       DOTEST(Ilwis::commandhandler()->execute(expr,&ctx), "mirror rotate mirrvert done.");

        Ilwis::IRasterCoverage raster("ilwis://internalcatalog/aamirvert");
        raster->connectTo(QString("file:///%1/aamirvert.mpr").arg(_baseDataPath.absolutePath()), "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
       raster->createTime(Ilwis::Time::now());
       raster->store();
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void RasterOperations::testResample() {

    Ilwis::IGeoReference grf("code=georef:type=corners,csy=epsg:21037,envelope=-3.02456e+06 -4.55547e+06 6.47259e+06 4.39692e+06,gridsize=1188 1120,name=grf1");
    QString expr = QString("aa5resbic=resample(n000302.mpr,grf1,bicubic)");
    DOTEST(grf.isValid(),"making georef by code");
    //QString expr = QString("aa5resbic=resample(average_monthly_temperature_january_5.mpr,plate102.grf,bicubic)");
    //QString expr = QString("aa5resbic=resample(small3.mpr,aeqsmall.grf,bicubic)");

    Ilwis::ExecutionContext ctx;
    Ilwis::SymbolTable syms;
    DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "resample done.");

    Ilwis::IRasterCoverage raster("ilwis://internalcatalog/aa5resbic");
    raster->connectTo(QString("file:///%1/aa5ss.mpr").arg(_baseDataPath.absolutePath()), "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
    raster->createTime(Ilwis::Time::now());
    raster->store();
}



void RasterOperations::iffRasterTest()
{
    try {
        // aa = small > 50
        QString expr = QString("newmap=iff(aa.mpr,%1,%2)").arg(50).arg(10);
        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        IRasterCoverage raster = syms.getValue<IRasterCoverage>(ctx._results[0]);
        QString outputFile = makeOutputPath("OutMapTest.mpr");
        qDebug() << "write to: " << outputFile;

        raster->connectTo(outputFile, "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
        raster->createTime(Ilwis::Time::now());
        raster->store();

        DOTEST(raster->pix2value(Ilwis::Pixel(1,1,0)) == 50,"value that confirms the input map expression");
        DOTEST(raster->pix2value(Ilwis::Pixel(3,4,0)) == 50,"value that confirms the input map expression");
        DOTEST(raster->pix2value(Ilwis::Pixel(4,1,0)) == 50,"value that confirms the input map expression");
        DOTEST(raster->pix2value(Ilwis::Pixel(4,0,0)) == 10,"value that does not confirm the input map expression");
        DOTEST(raster->pix2value(Ilwis::Pixel(2,2,0)) == 10,"value that does not confirm the input map expression");
        DOTEST(raster->pix2value(Ilwis::Pixel(4,4,0)) == 10,"value that does not confirm the input map expression");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void RasterOperations::iffRasterGeorefTest()
{
    try {
        // OutMap3 = IFF ((Landuse="Grassland") AND (INRANGE(Contour,4000,5000)), "True", "False")
        QString expr = QString("newmap=iff(OutMap3.mpr,%1,%2)").arg("true").arg("false");
        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        IRasterCoverage raster = syms.getValue<IRasterCoverage>(ctx._results[0]);
        QString outputFile = makeOutputPath("OutMap3Test.mpr");
        qDebug() << "write to: " << outputFile;

        raster->connectTo(outputFile, "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
        raster->createTime(Ilwis::Time::now());
        raster->store();

        DOTEST(raster->pix2value(Ilwis::Pixel(370,370,0)) == 0,"value that does not confirm the input map expression");
        DOTEST(raster->pix2value(Ilwis::Pixel(251,554,0))  == 0,"value that does not confirm the input map expression");
        DOTEST(raster->pix2value(Ilwis::Pixel(479,197,0)) == 0,"value that confirms the input map expression");
        DOTEST(raster->pix2value(Ilwis::Pixel(306,450,0)) == 0,"value that confirms the input map expression");
        DOTEST(raster->pix2value(Ilwis::Pixel(122,110,0)) == 1,"value that confirms the input map expression");
        DOTEST(raster->pix2value(Ilwis::Pixel(502,59,0)) == 1,"value that confirms the input map expression");
        DOTEST(raster->pix2value(Ilwis::Pixel(38,42,0)) == 1,"value that does not confirm the input map expression");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}



void RasterOperations::iffRasterInvalidParamsTest()
{
    try {
        QString expr = QString("iff(12233456789, %1,%2)").arg("InexistingMap.mpr").arg("InexistingMap2.mpr");
        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(!Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void RasterOperations::iffRasterInvalidParamsTest2()
{
    try {
        // soils_sadc.mpa is not a valid input parameter
        QString expr = QString("iff(OutMap3.mpr, %1,%2)").arg("soils_sadc.mpa").arg("1");
        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(!Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

