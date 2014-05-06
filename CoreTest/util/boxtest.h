#ifndef BOXTEST_H
#define BOXTEST_H

#include <QString>
#include <QTest>
#include "testmacros.h"
#include "ilwistestclass.h"

class BoxTest : public IlwisTestCase
{
    Q_OBJECT

public:
    BoxTest();

    NEW_TEST(BoxTest)    ;

private slots:
    void construction();
};

#endif // BOXTEST_H
