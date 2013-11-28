#ifndef TST_RASTEROPERATIONSTEST_H
#define TST_RASTEROPERATIONSTEST_H

#include <QObject>

#include "commandhandler.h"
#include "symboltable.h"

namespace Ilwis {

class RasterOperationsTest : public QObject
{
    Q_OBJECT

public:
    RasterOperationsTest();
    RasterOperationsTest(QString* testDataLocation);

private Q_SLOTS:
    void initTestCase();
    void testLinearStretchWithValueLimits();
    void testLinearStretchWithPercentLimits();
    void cleanupTestCase();


private:
    SymbolTable _symtbl;
    ExecutionContext _ctx;

};

}
#endif // TST_RASTEROPERATIONSTEST_H
