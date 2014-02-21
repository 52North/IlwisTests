#include "sizetest.h"
#include "size.h"

REGISTER_TEST(SizeTest);

SizeTest::SizeTest() : IlwisTestCase("SizeTests","CoreTest")
{
}

void SizeTest::creation() {
    Ilwis::Size<> sz;
    DOTEST(sz.isValid() == false, "invalid size");

    sz = Ilwis::Size<>(100,200,1);
    DOTEST(sz.isValid() && sz.xsize() == 100 && sz.ysize() == 200 && sz.zsize() == 1, "valid creation");

    Ilwis::Size<double> sz2 = { 2.34, 6.78, 9.34};
    DOTEST(sz.isValid() && sz2.xsize() == 2.34 && sz2.ysize() == 6.78 && sz2.zsize() == 9.34, "size with doubles, valid");

    Ilwis::Size<qint32> sz3 = Ilwis::Size<qint32>(-200,-300,1);
    DOTEST(sz3.isValid() == false, "invalid size");

    Ilwis::Size<double> sz4(0,0,0);
    DOTEST(sz4.isNull() == true, "invalid size");



}

void SizeTest::operators() {
    // rethink these operators, x,y,z size == 1 is problematic
//    Ilwis::Size<> sz1(100,200,1);
//    Ilwis::Size<> sz2(20,30,1);

//    sz1 += sz2;
//    DOTEST(sz1.isValid() && sz1 == Ilwis::Size<>(120,230,2), "added two sizes");

//    sz1 -= Ilwis::Size<>(30,40,1);
//    DOTEST(sz1.isValid() && sz1 == Ilwis::Size<>(90, 190,1),"substract size");

//    sz1 *= 0.5;
//    DOTEST(sz1.isValid() && sz1 == Ilwis::Size<>(45, 95,0), "mult sizes");


}

void SizeTest::misc() {
    Ilwis::Size<double> sz(3.45, 2.67, 8.0);

    DOTEST( APPROX(sz.linearSize(), 48,0.001), "volume test");

    Ilwis::Size<> sz2(200,400, 300);
    DOTEST(sz2.contains(24,23,67), "valid contains test");
    DOTEST(sz2.contains(700,23,67) == false, "valid contains test that fails");
}
