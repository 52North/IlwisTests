#ifndef SPATIALQUERIESTEST_H
#define SPATIALQUERIESTEST_H

#include <QString>
#include <QDir>
#include "kernel.h"
#include "geos/geom/Coordinate.h"
#include "coordinate.h"
#include "ilwistestclass.h"

class SpatialQueriesTest : public IlwisTestCase
{
    Q_OBJECT
public:
    SpatialQueriesTest();

    NEW_TEST(SpatialQueriesTest);

private slots:

    void initTestCase();
    void basic();
private:
    QDir _baseDataPath;
    QDir _baseDataOutputPath;
};

#endif // SPATIALQUERIESTEST_H
