#ifndef NUMERICDOMAINTESTS_H
#define NUMERICDOMAINTESTS_H

#include <QString>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class NumericDomainTests : public IlwisTestCase
{
   Q_OBJECT
public:
   explicit NumericDomainTests();

private:
    NEW_TEST(NumericDomainTests);

private slots:
    void numberIsInRange();
    void numberNotInRange();
    void negativeRange();
    void testTypes();
    void shouldFindInParent();
    void resolutionUnequalParent();
                                      };

#endif // NUMERICDOMAINTESTS_H
