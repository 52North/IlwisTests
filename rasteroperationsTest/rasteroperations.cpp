#include "kernel.h"
#include "ilwiscontext.h"
#include "testsuite.h"
#include "catalog.h"
#include "raster.h"
#include "ilwisoperation.h"
#include "rasteroperations.h"

REGISTER_TEST(RasterOperations);

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

    QString expr = QString("aa5resbic=resample(average_monthly_temperature.mpl,plate102.grf,bicubic)");
    Ilwis::ExecutionContext ctx;
    Ilwis::SymbolTable syms;
    DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "resample done.");

    Ilwis::IRasterCoverage raster("ilwis://internalcatalog/aa5resbic");
    raster->connectTo(QString("file:///%1/aa5resbic.mpl").arg(_baseDataPath.absolutePath()), "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
    raster->createTime(Ilwis::Time::now());
    raster->store();
}