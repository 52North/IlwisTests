
#include "kernel.h"
#include "ilwisdata.h"
#include "juliantimetests.h"
#include "testsuite.h"

REGISTER_TEST(JulianTimeTests);

JulianTimeTests::JulianTimeTests() : IlwisTestCase("JulianTimeTests", "CoreTest")
{
}

void JulianTimeTests::constructionTime() {
    Ilwis::Time t1(2014,2,17,14,51,10);
    Ilwis::Time t2("2014-02-17T14:51:10");
    Ilwis::Time t3("20140217T145110");
    Ilwis::Time t4(2456706.118865741);
    Ilwis::Time t5("37-2020-09");

    DOTEST(t1 == t2,"Equal times 1");
    DOTEST(t1 == t3,"Equal times 2");
    DOTEST(t1 == t4,"Equal times 3");
    double v = t1;
    DOTEST(APPROX(v, 2456706.118865741, .0000001), "Equal times 4");
    DOTEST(t5 == Ilwis::Time(), "Invalid time");

    Ilwis::Time t6("04:15:23");
    double t = t6;
    DOTEST(APPROX(t, 0.177349132, 00001), "no date, fraction of a day");
}

void JulianTimeTests::getters()
{
    Ilwis::Time t1(2014,2,17);
    Ilwis::Time t2("2004");
    Ilwis::Time t3("2010-06-23T12:30:09");

    DOTEST(t1.isLeapYear() == false, "2014 is no leap year");
    DOTEST(t2.isLeapYear() , "2004 is a leap year");
    DOTEST(t3.get(Ilwis::Time::tpYEAR) == 2010, "Year is 2010");
    DOTEST(t3.get(Ilwis::Time::tpMONTH) == 6, "Month is 6");
    DOTEST(t3.get(Ilwis::Time::tpDAYOFMONTH) == 23, "Day of the month is 23");
    DOTEST(t3.get(Ilwis::Time::tpDAYOFTHEWEEK) == 3, "Day of the week is 3");
    DOTEST(t3.get(Ilwis::Time::tpHOUR) == 12, "Hours is 12");
    DOTEST(t3.get(Ilwis::Time::tpMINUTE) == 30, "Minutes is 30");
    DOTEST(int(t3.get(Ilwis::Time::tpSECOND)) == 9, "Seconds is 9");

}

void JulianTimeTests::conversions()
{
    Ilwis::Time t1("20130418T094503");
    QDateTime qt1(QDate(2013,04,18),QTime(9,45,03));

    QString s = t1.toString();
    DOTEST(s == "2013-04-18T09:45:03","String conversion");
    DOTEST(t1 == qt1, "Automatic conversion to QDateTime");
}

void JulianTimeTests::operations(){
    Ilwis::Time t1("20130418T094503");
    Ilwis::Time t2("20130420T094503");
    Ilwis::Time t3("20130420T120903");
    Ilwis::Duration d1("2D");
    Ilwis::Duration d2("2D2h24m");

    DOTEST(t1 + d1 == t2, "Adding 2 days to time");
    DOTEST(t1 + d2 == t3, "Adding complex duration");

    //TODO
    // test for subtraction; tests for comparison
}

void JulianTimeTests::timeInterval() {
    Ilwis::Time t1("2013-04-18T09:45:03");
    Ilwis::Time t2("2013-04-20T12:09:03");
    Ilwis::Time t3("2013-04-19T09:10:40");
    Ilwis::TimeInterval ti("20130418T094503", "20130420T120903", Ilwis::Duration("4h"));
    IlwisTypes tp = ti.valueType();
    DOTEST(tp == itDATETIME, "Correct value type");
    DOTEST(ti.begin() == t1, "Starts correct");
    DOTEST(ti.end() == t2, "end correct");
    DOTEST(ti.contains(t3), "Includes correct value, date/time based");
    DOTEST(ti.contains(t3 + Ilwis::Duration("10D")) == false, "Excludes correct value");

    Ilwis::Time t4("12:30");
    Ilwis::Time t5("14:20");
    Ilwis::Time t6("13:15");
    Ilwis::TimeInterval ti2(t4,t5);
    DOTEST(ti2.contains(t6), "Includes correct value, time based");




}
