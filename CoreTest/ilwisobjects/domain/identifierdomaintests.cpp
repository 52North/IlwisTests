#include "identifierdomaintests.h"
#include "connectorinterface.h"
#include "ilwisobject.h"
#include "ilwisdata.h"
#include "domain.h"
#include "domainitem.h"
#include "itemdomain.h"
#include "identifieritem.h"
#include "identifierrange.h"
#include "testsuite.h"


REGISTER_TEST(IdentifierDomainTests);

IdentifierDomainTests::IdentifierDomainTests():
    IlwisTestCase("IdentifierDomainTests", "CoreTest")
{
}

void IdentifierDomainTests::containmentTests()
{
   try{
   Ilwis::NamedIdentifierRange identRange;
   identRange << "Pretoria" << "Lusaka" << "Luanda" << "Windhoek" << "Harare";
   Ilwis::INamedIdDomain iddomain;
   iddomain.prepare();
   iddomain->range(new Ilwis::NamedIdentifierRange(identRange));
   iddomain->setTheme("Southern African capitals");

   DOTEST(iddomain->contains("Lusaka") == Ilwis::Domain::cSELF, "Containment 1: Should be in range");
   DOTEST(iddomain->contains("Ouagadougou") == Ilwis::Domain::cNONE, "Containment 2: Should not be in range");
   DOTEST(iddomain->theme() == "Southern African capitals", "Right theme set");

   Ilwis::NamedIdentifierRange identRange2;
   identRange2 << "Mogadiscio" << "Khartoum" << "Brazzaville" << "Freetown";
   Ilwis::INamedIdDomain idParent;
   idParent.prepare();
   idParent->setRange(identRange2);
   DOTEST(idParent->contains("Freetown") == Ilwis::Domain::cSELF, "Containment 3: (setRange) Can find it in range;");

   DOTEST(idParent->ilwisType() == itITEMDOMAIN, "Right Ilwis type ITEMDOMAIN");
   DOTEST(idParent->item("Khartoum")->raw() == 1, "Found item with right raw index");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void IdentifierDomainTests::parentTests()
{
    try{
    Ilwis::NamedIdentifierRange rng1;
    rng1 << "Pretoria" << "Lusaka" << "Luanda";
    Ilwis::NamedIdentifierRange rng2;
    rng2 << "Pretoria" << "Lusaka" << "Luanda" << "Windhoek" << "Harare" << "Mogadiscio";

    Ilwis::INamedIdDomain idChild;
    idChild.prepare();
    idChild->setRange(rng1);

    Ilwis::INamedIdDomain idParent;
    idParent.prepare();
    idParent->setRange(rng2);

    idChild->setParent(idParent);
    idChild->setStrict(false);

    DOTEST(idChild->contains("Windhoek") == Ilwis::Domain::cPARENT, "Found item in parent");
    DOTEST(idChild->contains("Luanda") == Ilwis::Domain::cSELF, "Found item in self");
    DOTEST(idChild->contains("Ouagadougou") == Ilwis::Domain::cNONE, "Didn't find item, which is not in range");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void IdentifierDomainTests::alteringTests()
{
    try{
    Ilwis::NamedIdentifierRange rng1;
    rng1 << "Pretoria" << "Lusaka" << "Luanda" << "Windhoek" << "Harare";

    Ilwis::INamedIdDomain namedId;
    namedId.prepare();
    namedId->setRange(rng1);

    namedId->addItem(new Ilwis::NamedIdentifier("Libreville"));
    DOTEST(namedId->contains("Libreville") == Ilwis::Domain::cSELF, "content added to domain");
    DOTEST(namedId->count() == 6, "Counted right number of elements after add");

    namedId->removeItem("Luanda");
    DOTEST(namedId->contains("Luanda") == Ilwis::Domain::cNONE, "content removed from domain");
    DOTEST(namedId->count() == 5, "Counted right number of elements after remove");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}
