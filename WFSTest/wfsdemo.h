#ifndef WFSTEST_H
#define WFSTEST_H

#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

#include "wfstest_global.h"

class WFSTESTSHARED_EXPORT WfsDemo: public IlwisTestCase
{
    Q_OBJECT
    
public:
    WfsDemo();

    void wfsCatalog_prepareAndSetAsWorkingCatalog_hasWfsResourcesRegistered();
    void wfsCatalog_prepareFeatureCoverageViaUrl_validFeatureCoverage();

private:
    NEW_TEST(WfsDemo);

private Q_SLOTS:

};

#endif // WFSTEST_H
