#ifndef IDENTIFIERDOMAINTESTS_H
#define IDENTIFIERDOMAINTESTS_H

#include <QString>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class IdentifierDomainTests : public IlwisTestCase
{
    Q_OBJECT

public:
    explicit IdentifierDomainTests();

private:
    NEW_TEST(IdentifierDomainTests);

private slots:
    void containmentTests();
    void parentTests();
    void alteringTests();

};

#endif // IDENTIFIERDOMAINTESTS_H
