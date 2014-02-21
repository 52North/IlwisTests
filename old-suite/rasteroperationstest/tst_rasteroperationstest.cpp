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

#include "testutils.h"
#include "rasterstrechoperation.h"
#include "tst_rasteroperationstest.h"

using namespace Ilwis;

class QFileInfo;

#define IMAGE_TO_STRETCH "tmb3.mpr"

RasterOperationsTest::RasterOperationsTest()
{
}

void RasterOperationsTest::initTestCase()
{
    QUrl s = QString("file:///%1").arg(ROOT_TESTDATA);
    Catalog cat;
    cat.prepare(s);
    context()->setWorkingCatalog(cat);

    IRasterCoverage mpl;
    QString res = QString("file:///%1/%2").arg(ROOT_TESTDATA).arg(IMAGE_TO_STRETCH);
    QVERIFY2(mpl.prepare(res), QString("could not prepare '%1'").arg(res).toLatin1().constData());
}

void RasterOperationsTest::cleanupTestCase()
{
}

void RasterOperationsTest::testLinearStretchWithValueLimits()
{
    try {
        qDebug() << "stretch raster";
        QString expr = QString("stretch_out=linearstretch(%1, 70, 120)").arg(IMAGE_TO_STRETCH);

        Operation op(expr);
        QVERIFY2(op->execute(&_ctx,_symtbl), "stretching with value limits failed.");
    }
    catch(ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void RasterOperationsTest::testLinearStretchWithPercentLimits() {
    try {
        qDebug() << "stretch raster";
        QString expr = QString("stretch_out=linearstretch(%1, 10)").arg(IMAGE_TO_STRETCH);

        Operation op(expr);
        QVERIFY2(op->execute(&_ctx,_symtbl), "stretching with percent limits failed.");
    }
    catch(ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


#include "moc_tst_rasteroperationstest.cpp"

