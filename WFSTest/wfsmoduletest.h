#ifndef WFSMODULETEST_H
#define WFSMODULETEST_H

#include <QTest>
#include "ilwistestclass.h"
#include "testmacros.h"
#include "testsuite.h"

#define WFS_TEST_SERVER_1 "http://ogi.state.ok.us/geoserver/wfs?acceptVersions=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS"
#define WFS_TEST_SERVER_2 "http://nsidc.org/cgi-bin/atlas_north?service=WFS&acceptVersions=1.1.0&request=GetCapabilities"
#define WFS_TEST_SERVER_3 "http://www2.ign.es/sioseinspire?SERVICE=WFS&REQUEST=GetCapabilities"

class WfsModuleTest: public IlwisTestCase
{
public:
    WfsModuleTest();

private:
    NEW_TEST(WfsModuleTest);

private Q_SLOTS:

    void recognizeWfsModule();
};

#endif // WFSMODULETEST_H
