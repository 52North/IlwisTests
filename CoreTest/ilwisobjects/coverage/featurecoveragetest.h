#ifndef FEATURECOVERAGETEST_H
#define FEATURECOVERAGETEST_H


#include <QString>
#include <QDir>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class FeatureCoverageTest : public IlwisTestCase
{
    Q_OBJECT
public:
    FeatureCoverageTest();

    NEW_TEST(FeatureCoverageTest);

private slots:
};

#endif // FEATURECOVERAGETEST_H
