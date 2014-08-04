#ifndef POSTGRESSTEST_H
#define POSTGRESSTEST_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"
#include "postgrestest_global.h"

namespace Ilwis {
namespace Postgresql {


class PostgresTest : public IlwisTestCase
{
   Q_OBJECT

public:
    PostgresTest();
private:
    NEW_TEST(PostgresTest);

    void listNumberOfDriversAvailable();

    void prepareDatabaseConnection(Resource&dbResource);

private slots:
    void initDatabaseItemsFromCatalog();
    void initDatabaseItemsWithoutCatalog();
};

}
}
#endif // POSTGRESSTEST_H
