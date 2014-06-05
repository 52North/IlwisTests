#ifndef RASTERCALC_H
#define RASTERCALC_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class Rastercalc : public IlwisTestCase
{
    Q_OBJECT

public:
    Rastercalc();

    NEW_TEST(Rastercalc);

private slots:
    void addition();
    void substract();

};

#endif // RASTERCALC_H
