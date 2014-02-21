#ifndef TST_RESOURCETEST_H
#define TST_RESOURCETEST_H

#include <QObject>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class ResourceTests :  public IlwisTestCase
{
    Q_OBJECT

public:
    ResourceTests();

private:
    NEW_TEST(ResourceTests);

private Q_SLOTS:

    void initTestCase();
    void shouldParseLastUrlPartAsName();
    void shouldIndicateHavingQueryString();
    void shouldIndicateNotHavingQueryString();
    void cleanupTestCase();


};

#endif // TST_RESOURCETEST_H
