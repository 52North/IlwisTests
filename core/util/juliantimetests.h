#ifndef JULIANTIMETESTS_H
#define JULIANTIMETESTS_H

#include <QString>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class JulianTimeTests : public IlwisTestCase
{
    Q_OBJECT

public:
    JulianTimeTests();
private:
    NEW_TEST(JulianTimeTests);

private slots:
    void constructionTime();
    void getters();
    void conversions();

    void operations();
    void timeInterval();
};

#endif // JULIANTIMETESTS_H
