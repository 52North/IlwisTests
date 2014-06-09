#ifndef RASTERCOVERAGETEST_H
#define RASTERCOVERAGETEST_H

#include <QString>
#include <QDir>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class RasterCoverageTest : public IlwisTestCase
{
        Q_OBJECT
public:
    RasterCoverageTest();


    NEW_TEST(RasterCoverageTest);

private slots:
    void bands();
};

#endif // RASTERCOVERAGETEST_H
