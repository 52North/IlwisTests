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
#include "numericdomain.h"

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
    QDir input = TestSuite::instance()->inputDataPath();
    ICatalog cat(QUrl::fromLocalFile(input.absolutePath()).toString());
    context()->setWorkingCatalog(cat);

    IRasterCoverage mpl;
    DOTEST2(mpl.prepare(IMAGE_TO_STRETCH), QString("could not prepare '%1'").arg(IMAGE_TO_STRETCH));
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

