#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"
#include "ilws3connectortest_global.h"

class DataAccess : public IlwisTestCase
{
    Q_OBJECT
public:
    DataAccess();

private:
    QDir _baseDataPath;
    QDir _baseDataOutputPath;

    NEW_TEST(DataAccess);
private slots:

    void initTestCase();
    void rasters();
    void features();
    void table();
};

#endif // DATAACCESS_H
