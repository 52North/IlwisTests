#ifndef WEBFEATURESERVICETEST_H
#define WEBFEATURESERVICETEST_H

#include <QTest>
#include "ilwistestclass.h"
#include "testmacros.h"

class WebFeatureServiceTest: IlwisTestCase
{
public:
    WebFeatureServiceTest();
private:
    NEW_TEST(WebFeatureServiceTest);

private Q_SLOTS:
    void createWebFeatureService();

};

#endif // WEBFEATURESERVICETEST_H
