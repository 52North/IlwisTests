#include <QString>
#include <QtTest>

#include "kernel.h"
#include "raster.h"
#include "symboltable.h"

#include "ilwisoperation.h"

#include "itemrange.h"
#include "domainitem.h"
#include "itemdomain.h"
#include "numericitem.h"
#include "numericdomain.h"
#include "numericitemrange.h"

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

    INumericItemDomain bitsValueDomain;
    bitsValueDomain.prepare();

    NumericItemRange bitValueRange;
    bitValueRange << "0 255 1";
    bitsValueDomain->setRange(bitValueRange);

    qDebug() << "stretch raster with 8Bit value domain";
    mpl->datadefIndex().domain(bitsValueDomain);
    mpl->setLayerIndexes(bitValueRange);
    //IndexSlicer slicer(mpl);

    QVERIFY2(true, "Failure");

    INumericItemDomain percentDomain;
    percentDomain.prepare();

    // TODO verify stretch with percent domain
}


//#include "tst_rasteroperationstest.moc"

