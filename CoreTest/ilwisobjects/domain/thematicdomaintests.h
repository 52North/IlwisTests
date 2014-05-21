#ifndef THEMATICDOMAINTESTS_H
#define THEMATICDOMAINTESTS_H

#include <QString>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class ThematicDomainTests : public IlwisTestCase
{
    Q_OBJECT

public:
    explicit ThematicDomainTests();

private:
    NEW_TEST(ThematicDomainTests);

private slots:
    void constructionTests();
    void parentTests();
    void alteringTests();

};

#endif // THEMATICDOMAINTESTS_H

