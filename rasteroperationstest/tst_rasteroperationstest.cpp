#include <QString>
#include <QtTest>

#include "kernel.h"
#include "raster.h"
#include "symboltable.h"
#include "ilwisoperation.h"
#include "rasterstrechoperation.h"
#include "tst_rasteroperationstest.h"

using namespace Ilwis;

#define ROOT_TESTDATA "D:/data/coding/ilwis/testdata"

RasterOperationsTest::RasterOperationsTest()
{
}

void RasterOperationsTest::testLinearStretchOperation()
{

    SymbolTable symtbl;
    ExecutionContext ctx;

    IRasterCoverage mpl;
    QString res = QString("file:///%1/small.mpl").arg(ROOT_TESTDATA);
    mpl.prepare(res);

    QVERIFY2(false, "Failure");
}

//#include "tst_rasteroperationstest.moc"

