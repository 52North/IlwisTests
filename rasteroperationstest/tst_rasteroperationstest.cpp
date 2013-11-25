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

}

void RasterOperationsTest::cleanupTestCase()
{
    // TODO clean up mastercatalog etc.
}

void RasterOperationsTest::testLinearStretchOperation()
{
    try {
        /*
        INumericItemDomain bitsValueDomain;
        bitsValueDomain.prepare();

        NumericItemRange bitsValueRange;
        bitsValueRange.interpolation("");
        bitsValueRange << "0 255 1";
        bitsValueDomain->setRange(bitsValueRange);

        _mpl->datadefIndex().domain(bitsValueDomain);
        _mpl->setLayerIndexes(bitsValueRange);
         */


        IRasterCoverage mpl;
        QString res = QString("file:///%1/small.mpl").arg(ROOT_TESTDATA);
        QVERIFY2(mpl.prepare(res), QString("could not prepare '%1'").arg(res).toLatin1().constData());

        ExecutionContext ctx;
        Operation op({"stretch_out=linearstretch(small.mpl)"});
        qDebug() << "stretch raster";
        QVERIFY2(op->execute(&ctx,_symtbl), "operation done.");


    }
    catch (const std::length_error& le) {
        qDebug() << "Length error: " << le.what() << '\n';
    }
    catch(ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


//#include "tst_rasteroperationstest.moc"

