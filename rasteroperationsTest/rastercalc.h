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
    void initTestCase();
    void addition();
    void substract();
private:
    QDir _baseDataPath;
    QDir _baseDataOutputPath;
};

#endif // RASTERCALC_H
