#include <QString>
#include <QFileInfo>
#include <QFile>

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

#include "testsuite.h"
#include "testutils.h"
#include "rasteroperationstest.h"

using namespace Ilwis;

#define IMAGE_TO_STRETCH "tmb3.mpr"

REGISTER_TEST(RasterOperationsTest);

RasterOperationsTest::RasterOperationsTest(): IlwisTestCase("RasterOperationsTest", "RasterOperationsTest")
{
}

void RasterOperationsTest::initTestCase()
{
    QString input = TestSuite::instance()->inputDataPath();
    QUrl s = QUrl::fromLocalFile(input);
    Catalog cat;
    if ( !cat.prepare(s)) {
        QFAIL("Could not prepare working catalog.");
    }
    context()->setWorkingCatalog(cat);

    IRasterCoverage mpl;
    QString res = QString("file:///%1/%2").arg(input).arg(IMAGE_TO_STRETCH);
    DOTEST2(mpl.prepare(res), QString("could not prepare '%1'").arg(res).toLatin1().constData());
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
        DOTEST2(op->execute(&_ctx,_symtbl), "stretching with value limits failed.");
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
        DOTEST2(op->execute(&_ctx,_symtbl), "stretching with percent limits failed.");
    }
    catch(ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


#include "moc_rasteroperationstest.cpp"

