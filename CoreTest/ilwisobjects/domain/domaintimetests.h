#ifndef DOMAINTIMETESTS_H
#define DOMAINTIMETESTS_H

#include <QString>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class DomainTimeTests : public IlwisTestCase
{
    Q_OBJECT
public:
    explicit DomainTimeTests();

private:
    NEW_TEST(DomainTimeTests);
    
private slots:
    void construction();
};

#endif // DOMAINTIMETESTS_H
