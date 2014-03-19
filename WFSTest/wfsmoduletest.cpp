#include "kernel.h"
#include "catalog.h"
#include "symboltable.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"

#include "wfsmoduletest.h"
#include "wfstestconstants.h"

#include "testsuite.h"

using namespace Ilwis;

REGISTER_TEST(WfsModuleTest);

WfsModuleTest::WfsModuleTest():
    IlwisTestCase("WfsModuleTest", "WfsConnectorTest")
{
}

void WfsModuleTest::recognizeWfsModule()
{
    QString url = WFS_TEST_SERVER_1;

    ICatalog cat(url);
    bool prepared = cat.prepare();
    DOTEST2(prepared, QString("could not prepare remote WFS '%1'").arg(url));
    context()->setWorkingCatalog(cat);

    std::vector<Resource> items = cat->items();
    DOTEST2(items.size() > 0, "No WFS resources had been registered in the catalog.");
}
