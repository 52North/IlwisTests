#ifndef SIZETEST_H
#define SIZETEST_H

#include <QString>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"
#include "testsuite.h"

class SizeTest : public IlwisTestCase
{
    Q_OBJECT

public:
    SizeTest();
private:
   NEW_TEST(SizeTest);

private slots:
    void creation();
    void operators();
    void misc();
};

#endif // SIZETEST_H
