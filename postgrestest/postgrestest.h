#ifndef POSTGRESSTEST_H
#define POSTGRESSTEST_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"
#include "postgrestest_global.h"

class PostgresTest : public IlwisTestCase
{
   Q_OBJECT

public:
    PostgresTest();
private:
    NEW_TEST(PostgresTest);

private slots:

    void construction();
    void testBigSelection();
};

#endif // POSTGRESSTEST_H
