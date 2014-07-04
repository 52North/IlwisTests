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
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx), "mirror rotate mirrvert failed.");

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
