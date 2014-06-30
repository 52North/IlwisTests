#ifndef TABLETESTS_H
#define TABLETESTS_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class TableTests : public IlwisTestCase
{
    Q_OBJECT
public:
    TableTests();

private:
   NEW_TEST(TableTests);

private slots:
   void select();
};

#endif // TABLETESTS_H
