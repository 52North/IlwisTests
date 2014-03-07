#ifndef TST_WFSCONNECTORTEST_H
#define TST_WFSCONNECTORTEST_H

#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

#include "wfs.h"

using namespace Ilwis;
using namespace Wfs;

class QUrl;

class WfsCatalogConnectorTest : public IlwisTestCase
{
    Q_OBJECT

public:
    WfsCatalogConnectorTest();

private:
    NEW_TEST(WfsCatalogConnectorTest);

private Q_SLOTS:

    void sandbox();
    void initTestCase();
    void canUseValidWfsUrlWithCapitalParameters();
    void canUseValidWfsUrlWithMixedCapitalParameters();

};

#endif // TST_WFSCONNECTORTEST_H
