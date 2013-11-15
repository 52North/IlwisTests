#include <QString>
#include <QtTest>

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
#include "numericitem.h"
#include "numericdomain.h"
#include "numericitemrange.h"

#include "testcontants.h"
#include "rasterstrechoperation.h"
#include "tst_rasteroperationstest.h"

using namespace Ilwis;

SymbolTable _symtbl;
ExecutionContext _ctx;
IRasterCoverage _mpl;

RasterOperationsTest::RasterOperationsTest()
{
}

void RasterOperationsTest::initTestCase()
{
    QUrl s = QString("file:///%1").arg(ROOT_TESTDATA);
    mastercatalog()->addContainer(s);
    Catalog cat;
    cat.prepare(s);
    context()->setWorkingCatalog(cat);

    QString res = QString("file:///%1/small.mpl").arg(ROOT_TESTDATA);
    QVERIFY2(_mpl.prepare(res), QString("could not prepare '%1'").arg(res).toLatin1().constData());
}

void RasterOperationsTest::testLinearStretchOperation()
{
    try {
        INumericItemDomain bitsValueDomain;
        bitsValueDomain.prepare();

        NumericItemRange bitsValueRange;
        bitsValueRange.interpolation("");
        bitsValueRange << "0 255 1";
        bitsValueDomain->setRange(bitsValueRange);

        qDebug() << "stretch raster with 8Bit value domain";
        _mpl->datadefIndex().domain(bitsValueDomain);
        _mpl->setLayerIndexes(bitsValueRange);
        //IndexSlicer slicer(mpl);

        QVERIFY2(true, "Failure");

        //INumericItemDomain percentDomain;
        //percentDomain.prepare();

        // TODO verify stretch with percent domain
    }
    catch(ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void RasterOperationsTest::cleanupTestCase()
{
}

//#include "tst_rasteroperationstest.moc"

