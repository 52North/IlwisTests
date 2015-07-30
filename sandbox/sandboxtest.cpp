#include <QString>

#include "kernel.h"
#include "symboltable.h"
#include "ilwiscontext.h"
#include "commandhandler.h"
#include "raster.h"

#include "testsuite.h"
#include "sandboxtest.h"

REGISTER_TEST(SandBox);

using namespace Ilwis;

SandBox::SandBox(): IlwisTestCase("SandBox", "SandBoxTest")
{
}

void SandBox::sometest()
{
    try {
        QString expr = QString("aamirvert=mirrorrotateraster(small.mpr,rotate180)");

        Ilwis::ExecutionContext ctx;
        Ilwis::commandhandler()->execute(expr,&ctx);

        Ilwis::IRasterCoverage raster("ilwis://internalcatalog/aamirvert");
        raster->connectTo(makeOutputPath("aamirvert.tif"), "GTiff","gdal",Ilwis::IlwisObject::cmOUTPUT);
        raster->store();
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }

}




