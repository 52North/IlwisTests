#include "locationtest.h"
#include "ilwis.h"
#include "testsuite.h"

REGISTER_TEST(PixelTests);

PixelTests::PixelTests() : IlwisTestClass("LocationTests","CoreTest")
{
}
//----------------------------------------------------------------------------------
void PixelTests::pixelmultiplication()
{
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, z);
    QFETCH(double, parm);
    QFETCH(Ilwis::Pixel, result);
    QVERIFY2(Ilwis::Pixel(x,y,z) * parm == result, "Failure pixel test");
}

void PixelTests::pixelmultiplication_data()
{
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("z");
    QTest::addColumn<double>("parm");
    QTest::addColumn<Ilwis::Pixel>("result");

    QTest::newRow("with positive value") << 100 << 200 << 300 << 100.0 << Ilwis::Pixel(10000,20000,30000);
    QTest::newRow("with negative value") << -100 << 200 << 300 << 100.0 << Ilwis::Pixel(-10000,20000,30000);
    QTest::newRow("with double, integer result") << -100 << 200 << 300 << 0.22 << Ilwis::Pixel(-22,44,66);
    QTest::newRow("with double, fractional result") << -100 << 200 << 300 << 0.31456728 << Ilwis::Pixel(-31,62,94);
}

void PixelTests::pixeloperators()
{
    std::vector<double> v = { 2,-3};
    DOTEST(Ilwis::Pixel(345,543) / 100 == Ilwis::Pixel(3,5), "Pixel division by regular value, 2 dim");
    DOTEST(Ilwis::Pixel(345,543, 890) / 10 == Ilwis::Pixel(34,54,89), "Pixel division by regular value, 2 dim");
    DOTEST(Ilwis::Pixel(345,543) / 0 == Ilwis::Pixel(), "Pixel division by 0 value, should return invalid pixel");
    DOTEST(Ilwis::Pixel(345,543) + v  == Ilwis::Pixel(347, 540), "Pixel addition, vector");
    DOTEST(Ilwis::Pixel(345,543) - v  == Ilwis::Pixel(343, 546), "Pixel substracttion, vector");
    DOTEST(Ilwis::Pixel(345,543,567) - v  == Ilwis::Pixel(343, 546,567), "Pixel substracttion, vector 2d naar 3d pixel");
    v = { 5,6,7};
    DOTEST(Ilwis::Pixel(345,543) - v  == Ilwis::Pixel(340, 537), "Pixel substracttion, vector 3d naar 2d pixel");
    Ilwis::Pixel p = Ilwis::Pixel(345,543);
    p/=3;
    DOTEST( p == Ilwis::Pixel(115, 181), "Pixel division, regular value");
    p/=0;
    DOTEST( p == Ilwis::Pixel(), "Pixel division, zero value");
}

void PixelTests::pixelis3d(){
    Ilwis::Pixel p(100,200);

    QVERIFY2(p.is3D() == false, "Failure pixel test");

    Ilwis::Pixel p2(100,200,300);

    QVERIFY2(p2.is3D() == true, "Failure pixel test");
}

void PixelTests::pixelis0(){
    Ilwis::Pixel p(0,0);

    DOTEST(p.is0() == true, "x=y=0, should be a 0 pixel");

    Ilwis::Pixel p2(100,200);

    DOTEST(p2.is0() == false, "defined pixel, is not a 0 pixel");

    Ilwis::Pixel p3;

    DOTEST(p3.is0() == false, "undefined pixel, is not a 0 pixel");
}

void PixelTests::distance() {
    Ilwis::Pixel p1(122,245);
    double d= p1.distance(Ilwis::Pixel(567,677));
    DOTESTAPP(d,620.200, 001, "regular distance calculation");
    d = p1.distance(p1);
    DOTESTAPP(d,0, 001, "distance to itself, result == 0");
    d = p1.distance(Ilwis::Pixel());
    DOTESTAPP(d,Ilwis::rUNDEF, 001, "illegal distance calc 1");
    p1 = Ilwis::Pixel()    ;
    d = p1.distance(Ilwis::Pixel(567,677));
    DOTESTAPP(d,Ilwis::rUNDEF, 001, "illegal distance calc 2");
}

void PixelTests::initFromVector() {
    std::vector<int> v = { 34,67};
    DOTEST(Ilwis::Pixel(v) == Ilwis::Pixel(34,67),"pixel initialized from 2 element vector");

    v = {56,89,12};
    DOTEST(Ilwis::Pixel(v) == Ilwis::Pixel(56,89,12),"pixel initialized from 3 element vector");

    v = {79,54,88,15};
    DOTEST(Ilwis::Pixel(v) == Ilwis::Pixel(79,54,88),"pixel(3d) initialized from 4 element vector");

    v = {34};
    DOTEST(Ilwis::Pixel(v).isValid() == false,"invalid initialization with a 1 element vector");


}

