#include "ilwis.h"
#include "testsuite.h"
#include "kernel.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "postgrestest.h"

REGISTER_TEST(PostgresTest);

PostgresTest::PostgresTest() : IlwisTestCase("PostgresConnectorTest", "PostgresConnectorTest")
{
}

void PostgresTest::construction() {
    QStringList lst = QSqlDatabase::drivers();
    qDebug() <<lst.size();
}
