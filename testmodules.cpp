#include <QtWidgets/QApplication>
#include <QTest>
#include "kernel.h"
#include "systemtest/systemtest.h"
#include "rasteroperationstest/tst_rasteroperationstest.h"
#include "wfsconnectortest/tst_wfsconnectortest.h"

using namespace Ilwis;

int testSystem()
{
    LoaderTests test; \
    return QTest::qExec( &test); \
}

int testRasterOperations()
{
    RasterOperationsTest test; \
    return QTest::qExec( &test); \
}

int testWfsOperations()
{
    WfsConnectorTest test; \
    return QTest::qExec( &test); \
}

int main(int argc, char *argv[]) \
{ \
    QGuiApplication app(argc, argv); \
    app.setAttribute(Qt::AA_Use96Dpi, true); \

    return 0
            //+ testSystem()
            //+ testRasterOperations()
            + testWfsOperations()
            //+ testMyNotYetImplementedModule()
            ;
}
