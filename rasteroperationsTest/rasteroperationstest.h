#ifndef RASTEROPERATIONSTEST_H
#define RASTEROPERATIONSTEST_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"
#include "symboltable.h"


class RasterOperationsTest : public IlwisTestCase
{
    Q_OBJECT

public:
    RasterOperationsTest();

private:
    NEW_TEST(RasterOperationsTest);

   // SymbolTable _symtbl;
  //  ExecutionContext _ctx;


private slots:
  //  void testLinearStretchWithValueLimits();
  //  void testLinearStretchWithPercentLimits();

    void testMirrorRotate();
    void testResample();
};


#endif // RASTEROPERATIONSTEST_H
