#ifndef WFSMODULETEST_H
#define WFSMODULETEST_H

#include <QTest>
#include "ilwistestclass.h"
#include "testmacros.h"
#include "testsuite.h"

#include "wfstest_global.h"

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
