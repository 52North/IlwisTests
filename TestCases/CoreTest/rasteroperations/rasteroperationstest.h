#ifndef TST_RASTEROPERATIONSTEST_H
#define TST_RASTEROPERATIONSTEST_H

#include <QObject>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

#include "commandhandler.h"
#include "symboltable.h"

namespace Ilwis {

class RasterOperationsTest : public IlwisTestCase
{
    Q_OBJECT

public:
    RasterOperationsTest();
    RasterOperationsTest(QString* testDataLocation);

private:
    NEW_TEST(RasterOperationsTest);

    SymbolTable _symtbl;
    ExecutionContext _ctx;

private Q_SLOTS:
    void initTestCase();
    void testLinearStretchWithValueLimits();
    void testLinearStretchWithPercentLimits();
    void cleanupTestCase();

};

}
#endif // TST_RASTEROPERATIONSTEST_H
