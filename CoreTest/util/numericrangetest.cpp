#include "numericrangetest.h"
#include "ilwis.h"
#include "testsuite.h"
#include "numericrange.h"
#include "rangeiterator.h"

REGISTER_TEST(NumericRangeTest);

NumericRangeTest::NumericRangeTest() : IlwisTestCase("NumericRangeTest","CoreTest")
{
}

void NumericRangeTest::construction() {
    Ilwis::NumericRange rng1(-200,500);
    DOTEST(rng1.min() == -200 && rng1.max() == 500, "Basic construction");

    Ilwis::NumericRange rng2(1000,200);
    DOTEST(rng2.isValid() == false, "Basic construction, invalid range");

    Ilwis::NumericRange rng3;
    rng3.min(0);
    rng3.max(100);
    DOTEST(rng3.min() == 0 && rng3.max() == 100, "Construction with setters");

    Ilwis::NumericRange rng4(rng3);
    DOTEST(rng4.min() == 0 && rng4.max() == 100, "Copy construction");

    std::unique_ptr<Ilwis::NumericRange> rng5(static_cast<Ilwis::NumericRange *>(rng4.clone()));
    DOTEST(rng5->min() == 0 && rng5->max() == 100, "Basic copy construction");
}

void NumericRangeTest::operations() {
    Ilwis::NumericRange rng1(-200,500);
    DOTEST(rng1.contains(200),"basic contains test");
    DOTEST(rng1.contains(-2000) == false,"basic contains test, fails");

    Ilwis::NumericRange rng2(-200,500, 0.5);
    DOTEST(rng2.contains(200),"contains test with fractional step");
    DOTEST(rng2.contains(500.3) == false,"contains test with fractional step, should fail");

    Ilwis::NumericRange rng3(-50,30);
    DOTEST(rng3.contains(&rng3),"contains test with other range");

    DOTEST(rng3.distance() == 80, "max distance in range");
    rng3 += 40;
    DOTEST(rng3.max() == 40 && rng3.min() == -50, "extending the range with a new boundary, upper");
    rng3 +=-20;
    DOTEST(rng3.min() == -50 && rng3.max() == 40, "extending the range with a new boundary, lower, should be unchanged");

    Ilwis::NumericRange rng4(-300,-220);
    Ilwis::NumericRange rng5(-300,-100);
    Ilwis::NumericRange rng6(400,2000);
    Ilwis::NumericRange rng7(700,2000);
    Ilwis::NumericRange rng8(-700,2000);

    DOTEST(rng4 < rng1  , "range is smaller");
    DOTEST((rng5 < rng1) == false , "range overlaps, test should fail");
    DOTEST((rng6 > rng1) == false , "range overlaps, test should fail");
    DOTEST((rng7 > rng1)  , "range is larger");
    DOTEST((rng8 > rng1) == false , "range is bigger on both sides. should fail");

    DOTEST(rng2.ensure(2.67) == 2.5, "values are forced into the acceptable resolution");

}

void NumericRangeTest::rangeIterator() {
    Ilwis::NumericRange rng(-200,500,10);
    std::vector<double> elements;
    for(auto number : rng){
        elements.push_back(number);    ;
    }
    DOTEST(elements.size() == 71, "71 elements in the range");
    Ilwis::NumericRangeIterator iter(&rng);
    double v = *(iter + 10);
    DOTEST(v==-100, "plus operation, element 10 is -100");
    iter += 55;
    v = *(iter -25);
    DOTEST(v == 100,"minus operation, element 20 is 100");

    Ilwis::NumericRange rng2(0,100);
    Ilwis::NumericRangeIterator iter2(&rng2);
    v = *(iter2 + 1000);
    DOTEST(v == Ilwis::rUNDEF,"ranges with zero resolution cant be iterated, all results are rUNDEF");
}
