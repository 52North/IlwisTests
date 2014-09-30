#ifndef WCSTEST_H
#define WCSTEST_H


#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class WCSTest : public IlwisTestCase
{
       Q_OBJECT
public:
    WCSTest();

    NEW_TEST(WCSTest);


private slots:
    void getCapabilities();
};

#endif // WCSTEST_H
