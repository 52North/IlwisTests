#include "kernel.h"
#include "ilwiscontext.h"
#include "testsuite.h"
#include "catalog.h"
#include "raster.h"
#include "ilwisoperation.h"
#include "operationhelpergrid.h"
#include "operationoverloads.h"
#include "rastercalc.h"

REGISTER_TEST(Rastercalc);

Rastercalc::Rastercalc() : IlwisTestCase("Calc", "RasterOperationsTest")
{
}

void Rastercalc::addition() {

    Ilwis::IRasterCoverage map1;
    DOTEST(map1.prepare(QString("file:///%1/U_1001A.NTF").arg(_baseDataPath.absolutePath())),"loading erdas imagine file");

      Ilwis::IRasterCoverage cov = map1 + 100.0;
    DOCOMPARE(cov->pix2value(Ilwis::Pixel(0,0)),225.0,"Checking pix(269,339)");
    DOCOMPARE(cov->pix2value(Ilwis::Pixel(269,339)),139.0,"Checking pix(269,339)");
    DOCOMPARE(cov->pix2value(Ilwis::Pixel(29,996)),127.0,"Checking pix(29,996)");
}
