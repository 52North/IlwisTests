#ifndef COORDINATETEST_H
#define COORDINATETEST_H

#include <QString>
#include "kernel.h"
#include "geos/geom/Coordinate.h"
#include "coordinate.h"
#include "ilwistestclass.h"

class CoordinateTest : public IlwisTestCase
{
    Q_OBJECT

public:
    CoordinateTest();

private:
    NEW_TEST(CoordinateTest);

private Q_SLOTS:
    void coordinateoperators();

    void coordIs3d();
    void coordIs0();
    void vecTests();
};

#endif // COORDINATETEST_H
