#ifndef LOCATIONTEST_H
#define LOCATIONTEST_H

#include <QString>
#include <QTest>
#include "kernel.h"
#include "geos/geom/Coordinate.h"
#include "location.h"
#include "coordinate.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class PixelTests : public IlwisTestClass
{
    Q_OBJECT

public:
    PixelTests();

private:
    NEW_TEST(PixelTests);

private Q_SLOTS:
    void pixelmultiplication_data();
    void pixelmultiplication();
    void pixeloperators();


    void pixelis3d();
    void pixelis0();

    void initFromVector();


    void distance();
};

#endif // LOCATIONTEST_H
