#ifndef TST_WFSCONNECTORTEST_H
#define TST_WFSCONNECTORTEST_H

#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

#include "wfs.h"

using namespace Ilwis;
using namespace Wfs;

class QUrl;

class WfsConnectorTest : public IlwisTestCase
{
    Q_OBJECT

public:
    WfsConnectorTest();

private:
    NEW_TEST(WfsConnectorTest);
    void shouldCreateITableFromFeatureDescription();


private Q_SLOTS:
    void parseCorrectNumberOfFeatureTypesFromCapabilities();
    void shouldPrepareWfsFeature();
    void testInitialFeatureHasEmptyBBox();

};

#endif // TST_WFSCONNECTORTEST_H
