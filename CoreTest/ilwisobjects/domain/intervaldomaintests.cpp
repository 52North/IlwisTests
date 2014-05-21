#include "intervaldomaintests.h"
#include "connectorinterface.h"
#include "ilwisobject.h"
#include "ilwisdata.h"
#include "domain.h"
#include "domainitem.h"
#include "itemdomain.h"
#include "interval.h"
#include "intervalrange.h"
#include "testsuite.h"


REGISTER_TEST(IntervalDomainTests);

IntervalDomainTests::IntervalDomainTests():
    IlwisTestCase("IntervalDomainTests", "CoreTest")
{
}

void IntervalDomainTests::constructionTests()
{
    try{
    Ilwis::IntervalRange rng1;
    rng1 << "first|300|500|10" << "second|600|850|10" << "third|850|1400|5";

    Ilwis::IIntervalDomain inDom;
    inDom.prepare();
    inDom->setRange(rng1);

    DOTEST(inDom->contains(500) == Ilwis::Domain::cSELF, "Numeric value found in range");
    DOTEST(inDom->contains(410) == Ilwis::Domain::cSELF, "Numeric value found in range");
    DOTEST(inDom->contains(510) == Ilwis::Domain::cNONE, "Numeric value not in range");

    inDom->setTheme("Heights");
    DOTEST(inDom->theme() == "Heights", "Theme set correctly");

    DOTEST(inDom->count() == 3, "Item count correct");
    DOTEST(inDom->item("second")->raw() == 2, "Item found at expected place");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}


void IntervalDomainTests::parentTests()
{
    try{
    Ilwis::IntervalRange rng1;
    rng1 << "first|300|500|10" << "second|600|850|10";

    Ilwis::IntervalRange rng2;
    rng2 << "first|300|500|10" << "second|600|850|10" << "third|850|1400|5";

    Ilwis::IIntervalDomain chilDom;
    chilDom.prepare();
    chilDom->setRange(rng1);

    Ilwis::IIntervalDomain parentDom;
    parentDom.prepare();
    parentDom->setRange(rng2);


    chilDom->setParent(parentDom);
    chilDom->setStrict(false);

    DOTEST(chilDom->contains(950) == Ilwis::Domain::cPARENT, "Value found in parent");
    DOTEST(chilDom->contains(370) == Ilwis::Domain::cSELF, "Value found in child");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void IntervalDomainTests::alteringTests()
{
    try{
    Ilwis::IntervalRange rng1;
    rng1 << "first|300|500|10";

    Ilwis::IIntervalDomain interDom;
    interDom.prepare();
    interDom->setRange(rng1);

    Ilwis::NumericRange adde{510,620,10};

    interDom->addItem(new Ilwis::Interval(QString("second"), adde));

    DOTEST(interDom->contains(610) == Ilwis::Domain::cSELF, "Found added value");
    DOTEST(interDom->count() == 2, "Counted right number of elements");

    interDom->removeItem("first");
    DOTEST(interDom->contains(340) == Ilwis::Domain::cNONE, "Didn't find removed value");
    DOTEST(interDom->count() == 1, "Counted right number of elements");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }

}
