#include "thematicdomaintests.h"
#include "connectorinterface.h"
#include "ilwisobject.h"
#include "ilwisdata.h"
#include "domain.h"
#include "domainitem.h"
#include "itemdomain.h"
#include "identifieritem.h"
#include "thematicitem.h"
#include "identifierrange.h"
#include "testsuite.h"

REGISTER_TEST(ThematicDomainTests);

ThematicDomainTests::ThematicDomainTests():
    IlwisTestCase("ThematicDomainTests", "CoreTest")
{
}

void ThematicDomainTests::constructionTests()
{
    try{
    Ilwis::ThematicRange foxes;
    foxes << "grey fox|1.0.3|a really grey fox" <<
             "desert fox|1.2.3|living in the desert, not dessert" <<
             "snow fox|4.3.1" << "dancing fox";
    Ilwis::IThematicDomain wildlife;
    wildlife.prepare();
    wildlife->range(new Ilwis::ThematicRange(foxes));
    wildlife->setTheme("Foxes");

    DOTEST(wildlife->contains("desert fox") == Ilwis::Domain::cSELF, "Containment 1: found in range");
    DOTEST(wildlife->contains("blue fox") == Ilwis::Domain::cNONE, "Containment 2: not found in range");
    DOTEST(wildlife->count() == 4, "Counted right number of elements");
    DOTEST(wildlife->theme() == "Foxes", "Found  right theme name");
    DOTEST(wildlife->item("snow fox")->raw() == 2, "Found item at right position");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void ThematicDomainTests::parentTests()
{
    try{
    Ilwis::ThematicRange foxes;
    foxes << "grey fox|1.0.3|a really grey fox" <<
             "desert fox|1.2.3|living in the desert, not dessert";

    Ilwis::ThematicRange moreFoxes;
    moreFoxes << "grey fox|1.0.3|a really grey fox" <<
            "desert fox|1.2.3|living in the desert, not dessert" <<
            "snow fox|4.3.1" << "dancing fox";

    Ilwis::IThematicDomain themChild;
    themChild.prepare();
    themChild->setRange(foxes);

    Ilwis::IThematicDomain themParent;
    themParent.prepare();
    themParent->setRange(moreFoxes);

    themChild->setParent(themParent);
    themChild->setStrict(false);

    DOTEST(themChild->contains("snow fox") == Ilwis::Domain::cPARENT, "Item found in parent");
    DOTEST(themChild->contains("grey fox") == Ilwis::Domain::cSELF, "Item found in own range");
    DOTEST(themChild->contains("blue fox") == Ilwis::Domain::cNONE, "No item found in any range");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void ThematicDomainTests::alteringTests()
{
    try{
    Ilwis::ThematicRange roos;
    roos << "kangaroo|1.3.2|a normal kangaroo" <<
            "red giant kangaroo|5.0.1|a red giant kangaroo" <<
            "wallaby|1.0.2|a little but funny kangaroo";

    Ilwis::IThematicDomain ozwild;
    ozwild.prepare();
    ozwild->setRange(roos);

    ozwild->addItem(new Ilwis::ThematicItem({"joey"}));
    DOTEST(ozwild->contains("joey") == Ilwis::Domain::cSELF, "item has been added");
    DOTEST(ozwild->count() == 4, "Correct number of items counted after adding");

    ozwild->removeItem("wallaby");
    DOTEST(ozwild->contains("wallaby") == Ilwis::Domain::cNONE, "item has been removed");
    DOTEST(ozwild->count() == 3, "Correct number of items counted after deleting");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }

}
