#include <QtWidgets/QApplication>
#include <QTest>
#include "kernel.h"
#include "rasteroperationstest/tst_rasteroperationstest.h"

using namespace Ilwis;

int main(int argc, char *argv[]) \
{ \
    QGuiApplication app(argc, argv); \
    app.setAttribute(Qt::AA_Use96Dpi, true); \
    RasterOperationsTest test; \
    return QTest::qExec( &test, argc, argv); \
}





