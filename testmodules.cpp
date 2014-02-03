#include <QtWidgets/QApplication>
#include <QTest>

//#include "systemtest/systemtest.h"
#include "core/catalog/tst_resourcetest.h"
#include "rasteroperationstest/tst_rasteroperationstest.h"
#include "wfsconnectortest/tst_wfsconnectortest.h"
#include "xmltests/qtxmlparsertest.h"

using namespace Ilwis;

/*
int testSystem()
{
    LoaderTests test; \
    return QTest::qExec( &test); \
}
*/

int testResource()
{
    ResourceTest test; \
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

int testQtXmlParserOperations()
{
    QtXmlParserTest test; \
    return QTest::qExec( &test);
}

int main(int argc, char *argv[]) \
{ \
    QGuiApplication app(argc, argv); \
    app.setAttribute(Qt::AA_Use96Dpi, true); \

    return 0
            //+ testSystem()
            //+ testResource()
            //+ testRasterOperations()
            + testWfsOperations()
            //+ testQtXmlParserOperations()
            //+ testMyNotYetImplementedModule()

            ;
}
