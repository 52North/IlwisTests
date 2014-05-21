#ifndef GDALCONNECTORTEST_H
#define GDALCONNECTORTEST_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class GDALConnectorTest : public IlwisTestCase
{
    Q_OBJECT
public:

    GDALConnectorTest();
private:
    NEW_TEST(GDALConnectorTest);
    QDir _baseDataPath;
    QDir _baseDataOutputPath;



private slots:
    void initTestCase();

    void tableLoadTests();
    void tableStoreTests();
    void rasterLoadTests();
    void rasterStoreTests();
    void featureLoadTests();
    void featureStoreTests();
   // void catalogLoadTests();
};

#endif // GDALCONNECTORTEST_H
