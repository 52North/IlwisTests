#include "numericdomaintests.h"
#include "connectorinterface.h"
#include "ilwisobject.h"
#include "ilwisdata.h"
#include "domain.h"
#include "numericrange.h"
#include "numericdomain.h"
#include "domainhelper.h"
#include "testsuite.h"

REGISTER_TEST(NumericDomainTests);

NumericDomainTests::NumericDomainTests():
    IlwisTestCase("NumericDomainTests", "CoreTest")
{
}

void NumericDomainTests::numberIsInRange()
{
    try{
    Ilwis::INumericDomain numbers;
    numbers.prepare();
    numbers->range( new Ilwis::NumericRange(10, 50, 1));

    DOTEST(numbers->contains(27) == Ilwis::Domain::cSELF, "number is in range");
    DOTEST(numbers->contains(10) == Ilwis::Domain::cSELF, "low boundary is in range");
    DOTEST(numbers->contains(50) == Ilwis::Domain::cSELF, "high boundary is in range");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void NumericDomainTests::numberNotInRange()
{
    try{
    Ilwis::INumericDomain numbers;
    numbers.prepare();
    numbers->range( new Ilwis::NumericRange(10, 50, 1));

    DOTEST(numbers->contains(85) == Ilwis::Domain::cNONE, "number is not in range");
    DOTEST(numbers->contains(51) == Ilwis::Domain::cNONE, "(high boundary + 1) is not in range");
    DOTEST(numbers->contains(9) == Ilwis::Domain::cNONE, "(low boundary - 1) is not in range");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void NumericDomainTests::negativeRange()
{
    try{
    Ilwis::INumericDomain numbers;
    numbers.prepare();
    numbers->range( new Ilwis::NumericRange(-5, 10, 1));

    DOTEST(numbers->contains(-1) == Ilwis::Domain::cSELF, "Success, negative number in range");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void NumericDomainTests::testTypes()
{
    try{
    Ilwis::INumericDomain numbers;
    numbers.prepare();
    numbers->range( new Ilwis::NumericRange(5, 67, 1));

    DOTEST(numbers->ilwisType() == itNUMERICDOMAIN, "Success, it is Numeric Domain Type");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void NumericDomainTests::shouldFindInParent()
{
    try{
    Ilwis::INumericDomain parentDom;
    parentDom.prepare();
    parentDom->range( new Ilwis::NumericRange(5, 98, 1));

    Ilwis::INumericDomain childDom;
    childDom.prepare();
    childDom->range( new Ilwis::NumericRange(10, 42, 1));

    childDom->setParent(parentDom);

    DOTEST(childDom->contains(5) == Ilwis::Domain::cPARENT, "Number found in parent.");
    DOTEST(childDom->contains(20) == Ilwis::Domain::cSELF, "Number found in itself.");
    DOTEST(childDom->contains(1) == Ilwis::Domain::cNONE, "Number neither found in itself nor in parent.");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void NumericDomainTests::resolutionUnequalParent()
{
    try{
    Ilwis::INumericDomain parentDom;
    parentDom.prepare();
    parentDom->range( new Ilwis::NumericRange(5, 98, 1));

    Ilwis::INumericDomain childDom;
    childDom.prepare();
    childDom->range( new Ilwis::NumericRange(10, 42, 0.3));

    childDom->setParent(parentDom);

    DOTEST(childDom->contains(65) == Ilwis::Domain::cPARENT, "Number found in parent.");
    DOTEST(childDom->contains(10.6) == Ilwis::Domain::cSELF, "Number found in self, with different range to parent");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

