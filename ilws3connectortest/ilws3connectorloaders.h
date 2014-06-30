#ifndef ILWS3CONNECTORTEST_H
#define ILWS3CONNECTORTEST_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"
#include "ilws3connectortest_global.h"

class Ilws3connectorTest : public IlwisTestCase
{
      Q_OBJECT

public:
    Ilws3connectorTest();

    NEW_TEST(Ilws3connectorTest);

private slots:
    void loaderGeometryThings();
    void loaderCsy();
    void loadCoverages();
    void domainLoadingConstructing();
    void tables();
};

#endif // ILWS3CONNECTORTEST_H
