#ifndef ILWIS3CONNECTORTEST_H
#define ILWIS3CONNECTORTEST_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"
#include "ilwis3connectortest_global.h"

class Ilwis3connectorTest : public IlwisTestCase
{
      Q_OBJECT

public:
    Ilwis3connectorTest();

    NEW_TEST(Ilwis3connectorTest);

private slots:
    void loaderGeometryThings();
    void loaderCsy();
    void loadCoverages();
    void domainLoadingConstructing();
    void tables();
};

#endif // ILWIS3CONNECTORTEST_H
