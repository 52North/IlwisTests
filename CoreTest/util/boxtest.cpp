#include "kernel.h"
#include "ilwisdata.h"
#include "testsuite.h"
#include "boxtest.h"
#include "geos/geom/Coordinate.h"
#include "coordinate.h"
#include "location.h"
#include "box.h"

REGISTER_TEST(BoxTest);

BoxTest::BoxTest() : IlwisTestCase("boxtest","CoreTest")
{
}

void BoxTest::construction() {
    Ilwis::BoundingBox box(Ilwis::Pixel(10,24), Ilwis::Pixel(56,150));

    DOTEST(box.min_corner() == Ilwis::Pixel(10,24) && box.max_corner() == Ilwis::Pixel(56,150), " basic construction");

    Ilwis::BoundingBox box2(box);

    DOTEST(box2.min_corner() == Ilwis::Pixel(10,24) && box2.max_corner() == Ilwis::Pixel(56,150), " basic copy construction");

    Ilwis::BoundingBox box3("POLYGON(25 27,820 560)");

    DOTEST(box3.min_corner() == Ilwis::Pixel(25,27) && box3.max_corner() == Ilwis::Pixel(820,560), " 2D string construction");

    Ilwis::BoundingBox box4("POLYGON(25 27 28,820 560 100)");

    DOTEST(box4.min_corner() == Ilwis::Pixel(25,27,28) && box4.max_corner() == Ilwis::Pixel(820,560,100), " 3D string construction");

    Ilwis::BoundingBox box5("POLYGON(25,27,820,560,100)");

    DOTEST(box5.isValid() == false, "illegal string construction");
}
