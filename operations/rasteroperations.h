#ifndef RASTEROPERATIONSTEST_H
#define RASTEROPERATIONSTEST_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class RasterOperations : public IlwisTestCase
{
    Q_OBJECT
public:
    RasterOperations();

    NEW_TEST(RasterOperations);
private:
    QDir _baseDataPath;
    QDir _baseDataOutputPath;
private slots:
    void initTestCase();
};

#endif // RASTEROPERATIONSTEST_H
