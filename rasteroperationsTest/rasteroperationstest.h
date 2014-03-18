#ifndef RASTEROPERATIONSTEST_H
#define RASTEROPERATIONSTEST_H

#include <QTest>
#include "ilwistestclass.h"
#include "testmacros.h"

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

#endif // RASTEROPERATIONSTEST_H
