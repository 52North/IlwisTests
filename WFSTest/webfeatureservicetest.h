#ifndef WEBFEATURESERVICETEST_H
#define WEBFEATURESERVICETEST_H

#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

#include "wfstest_global.h"

namespace Ilwis {
namespace Wfs {

class WebFeatureService;

class WebFeatureServiceTest: IlwisTestCase
{
public:
    WebFeatureServiceTest();
private:
    NEW_TEST(WebFeatureServiceTest);

    WebFeatureService *_wfs;

private Q_SLOTS:
    void createWebFeatureService();

    // TODO: perform remote requests here?!

    void cleanupTestCase();

};
}
}

#endif // WEBFEATURESERVICETEST_H
