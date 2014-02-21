#include "coordinatetest.h"
#include "testsuite.h"


REGISTER_TEST(CoordinateTest);

CoordinateTest::CoordinateTest() : IlwisTestCase("CoordinateTest","CoreTest")
{
}

void CoordinateTest::coordinateoperators()
{
    DOTEST(Ilwis::Coordinate(345.12,543)  == Ilwis::Coordinate(345.12,543), "Coordinate comparison, equals");
    DOTEST(Ilwis::Coordinate(345.12,543)  != Ilwis::Coordinate(147.79, 239.11), "Coordinate comparison, not equal");

    std::vector<double> v = { 2.67,-3.89};
    DOTEST(Ilwis::Coordinate(867.47,1455.298) / 22.3 == Ilwis::Coordinate(38.9,65.26), "Coordinate division by regular value, 2 dim");
    DOTEST(Ilwis::Coordinate(867.47,1455.298, 270.499) / 22.3 == Ilwis::Coordinate(38.9,65.26,12.13), "Coordinate division by regular value, 2 dim");
    DOTEST(Ilwis::Coordinate(345.6,543.9) / 0 == Ilwis::Coordinate(), "Coordinate division by 0 value, should return invalid Coordinate");
    DOTEST(Ilwis::Coordinate(345.12,543) + v  == Ilwis::Coordinate(347.79, 539.11), "Coordinate addition, vector");
    DOTEST(Ilwis::Coordinate(89.63,11.87) - v  == Ilwis::Coordinate(86.96, 15.76), "Coordinate substracttion, vector");
    DOTEST(Ilwis::Coordinate(89.63,11.87,45.81) - v  == Ilwis::Coordinate(86.96, 15.76,45.81), "Coordinate substracttion, vector 2d naar 3d Coordinate");
    v = { -5.13,6.03,7.46};
    DOTEST(Ilwis::Coordinate(23.90,18.06) - v  == Ilwis::Coordinate(29.03, 12.03), "Coordinate substracttion, vector 3d naar 2d Coordinate");
    Ilwis::Coordinate p = Ilwis::Coordinate(12.6,33.96);
    p/=3;
    DOTEST( p == Ilwis::Coordinate(4.2, 11.32), "Coordinate division, regular value");
    p/=0;
    DOTEST( p == Ilwis::Coordinate(), "Coordinate division, zero value");
}

void CoordinateTest::coordIs3d(){
    Ilwis::Coordinate p(100.57,234.88);

    QVERIFY2(p.is3D() == false, "Failure coord test");

    Ilwis::Coordinate p2(100.6868,200.23,300.1);

    QVERIFY2(p2.is3D() == true, "Failure coord test");
}

void CoordinateTest::coordIs0(){
    Ilwis::Coordinate p(0,0);

    DOTEST(p.is0() == true, "x=y=0, should be a 0 coord");

    Ilwis::Coordinate p2(100,200);

    DOTEST(p2.is0() == false, "defined coord, is not a 0 pixel");

    Ilwis::Coordinate p3;

    DOTEST(p3.is0() == false, "undefined pixel, is not a 0 pixel");
}

void CoordinateTest::vecTests() {
    Ilwis::Coordinate crd(203.89, 99.01, 2.09);

    std::vector<double> v = crd;
    DOTEST(v.size() == 3 && v[0] == 203.89 && v[1] == 99.01 && v[2] == 2.09,"3D vector from 3D coord");

    Ilwis::Coordinate crd2(203.89, 99.01);

    v = crd2;
    DOTEST(v.size() == 2 && v[0] == 203.89 && v[1] == 99.01,"2D vector from 3D coord");

    v = Ilwis::Coordinate();
    DOTEST(v.size() == 0, "Empty vector from invalid coord");



}
