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

    void prepareDatabaseConnection(IOOptions &options);
    void initDatabaseItemByNameFromCatalog();

private slots:
    void loadDataFromPlainTable();
    void changeDataOfPlainTable();
    void initDatabaseItemsFromCatalog();
    void initDatabaseItemsWithoutCatalog();
    void loadDataFromFeatureWithMultipleGeometriesTable();
    void loadDataFromFeatureWithSingleGeometryTable();
    void insertNewFeaturesToExistingTable();
};

}
}
#endif // POSTGRESSTEST_H
