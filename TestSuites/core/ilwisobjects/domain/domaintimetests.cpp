#include "domaintimetests.h"
#include "connectorinterface.h"
#include "ilwisobject.h"
#include "ilwisdata.h"
#include "domain.h"
#include "numericrange.h"
#include "numericdomain.h"
#include "domainhelper.h"
#include "testsuite.h"

REGISTER_TEST(DomainTimeTests);

DomainTimeTests::DomainTimeTests() :
    IlwisTestCase("DomainTimeTests", "CoreTest")
{
}

void DomainTimeTests::construction()
{
    //Ilwis::TimeInterval ti("20081104","20100130");
    Ilwis::Time t2("20090412");
    Ilwis::Time t3("20160707");
    Ilwis::Time t4 = t2 - Ilwis::Duration("2Y");
    Ilwis::Time t5 = t2 + Ilwis::Duration("10Y");
    QString aa = t4.toString();
    aa = t5.toString();
    Ilwis::INumericDomain dom;
    dom.prepare();
    dom->range(new Ilwis::TimeInterval("20081104","20100130"));
    Ilwis::ITimeDomain dm;
    dm.prepare();
    dm->range(new Ilwis::TimeInterval(t4,t5));

    DOTEST(dom->valueType() == itDATE, "correctly set");
    DOCOMPARE(dom->impliedValue(IVARIANT(t2)).value<Ilwis::Time>().toString(), QString("2009-04-12"), "testing representation");
    DOTEST(dom->contains(IVARIANT(t2)) == Ilwis::Domain::cSELF, "testing containment 1");
    DOTEST(dom->contains(IVARIANT(t3)) == Ilwis::Domain::cNONE, "testing containment 2");

    dom->setParent(dm);
    DOTEST(dom->contains(IVARIANT(t3)) == Ilwis::Domain::cPARENT, "testing containment 3");

    Ilwis::ITimeDomain dm2;
    dm2.prepare("time");

}
