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

    void prepareDatabaseConnection(Resource&dbResource);

    // TODO discuss resolving root for remote catalog container
    void initDatabaseItemByNameFromCatalog();

    void initDatabaseItemsFromCatalog();
    void initDatabaseItemsWithoutCatalog();
    void loadDataFromFeatureWithSingleGeometryTable();
    void loadDataFromFeatureWithMultipleGeometriesTable();
    void loadDataFromPlainTable();
    void changeDataOfPlainTable();


private slots:
    void insertNewFeaturesToExistingTable();

};

}
}
#endif // POSTGRESSTEST_H
