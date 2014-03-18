#include "kernel.h"
#include "catalog.h"
#include "symboltable.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"
#include "wfsmoduletest.h"
#include "wfstestconstants.h"

using namespace Ilwis;

REGISTER_TEST(WfsModuleTest);

WfsModuleTest::WfsModuleTest(): IlwisTestCase("WfsConnectorModuleTest", "WfsConnectorTest")
{
}

void WfsModuleTest::recognizeWfsModule()
{
    QString url(WFS_TEST_SERVER_1);

    QUrl s(url);
    Catalog cat;
    //bool prepared = cat.prepare(s);
    //DOTEST2(prepared, QString("could not prepare WFS '%1'").arg(url));
   // context()->setWorkingCatalog(cat);

}
