#ifndef PIXELITERATORTEST_H
#define PIXELITERATORTEST_H

#include <QString>
#include <QDir>
#include "kernel.h"
#include "geos/geom/Coordinate.h"
#include "coordinate.h"
#include "ilwistestclass.h"

class PixelIteratorTest : public IlwisTestCase
{
    Q_OBJECT

public:
    PixelIteratorTest();

    NEW_TEST(PixelIteratorTest);

private slots:
    void ziterator();
    void rasterSelection();
};

#endif // PIXELITERATORTEST_H
