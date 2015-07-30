
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QUrl>
#include <QDir>

#include "kernel.h"
#include "raster.h"
#include "catalog.h"
#include "symboltable.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"

#include "ilwisoperation.h"

#include "itemrange.h"
#include "domainitem.h"
#include "itemdomain.h"

#include "interval.h"
#include "numericdomain.h"
#include "intervalrange.h"
#include "coverage.h"
#include "featurecoverage.h"
#include "feature.h"
#include "raster.h"
#include "pixeliterator.h"



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


try{
    Ilwis::IRasterCoverage raster("const_ras.tif");
    double v = raster->pix2value(Ilwis::Pixel(100,1900));
    Ilwis::Operation operation({"aabig=log(capereduced.tif)"});
    Ilwis::SymbolTable syms;
    Ilwis::ExecutionContext ctx;
    operation->execute(&ctx, syms);
    Ilwis::IRasterCoverage raster2("ilwis://internalcatalog/aabig");
    raster2->connectTo(QUrl("file:///d:/Projects/Ilwis/Ilwis4/testdata/aabig.tif"),"GTiff","gdal", Ilwis::IlwisObject::cmOUTPUT);
    raster2->store();
    } catch (const Ilwis::ErrorObject& err){
        qDebug() << err.message();
    }

}



