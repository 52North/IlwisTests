#ifndef WEBFEATURESERVICETEST_H
#define WEBFEATURESERVICETEST_H

#include <QTest>
#include "ilwistestclass.h"
#include "testmacros.h"

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
