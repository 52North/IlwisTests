#ifndef RASTEROPERATIONS_H
#define RASTEROPERATIONS_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class RasterOperations : public IlwisTestCase
{
    Q_OBJECT

    NEW_TEST(RasterOperations);

public:
    RasterOperations();
private slots:
    void testMirrorRotate();
    void testResample();

    void iffRasterTest();
    void iffRasterGeorefTest();
    void iffRasterInvalidParamsTest();
    void iffRasterInvalidParamsTest2();
};

#endif // RASTEROPERATIONS_H
