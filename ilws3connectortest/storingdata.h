#ifndef STORINGDATA_H
#define STORINGDATA_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"
#include "ilws3connectortest_global.h"

class StoringData : public IlwisTestCase
{
    Q_OBJECT

public:
    StoringData();

    NEW_TEST(StoringData);

private slots:

};

#endif // STORINGDATA_H
