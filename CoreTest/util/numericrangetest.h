#ifndef NUMERICRANGETEST_H
#define NUMERICRANGETEST_H

#include <QString>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class NumericRangeTest : public IlwisTestCase
{
    Q_OBJECT
public:
    NumericRangeTest();

private:
    NEW_TEST(NumericRangeTest);

private Q_SLOTS:

    void construction();
    void operations();
    void rangeIterator();
};

#endif // NUMERICRANGETEST_H
