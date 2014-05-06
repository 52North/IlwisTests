#ifndef INTERVALDOMAINTESTS_H
#define INTERVALDOMAINTESTS_H

#include <QString>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class IntervalDomainTests : public IlwisTestCase
{
    Q_OBJECT

public:
    explicit IntervalDomainTests();

private:
    NEW_TEST(IntervalDomainTests);

private slots:
    void constructionTests();
    void parentTests();
    void alteringTests();

};

#endif // INTERVALDOMAINTESTS_H
