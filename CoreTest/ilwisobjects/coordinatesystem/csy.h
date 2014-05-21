#ifndef CSYWKT_H
#define CSYWKT_H

#include <QString>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class CsyTests : public IlwisTestCase
{
    Q_OBJECT
public:
    CsyTests();

    NEW_TEST(CsyTests);
private slots:
    void wkt();
};

#endif // CSYWKT_H
