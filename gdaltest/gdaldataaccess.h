#ifndef GDALDATAACCESS_H
#define GDALDATAACCESS_H

#include <QString>
#include <QTest>
#include <QDir>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class GdalDataAccess : public IlwisTestCase
{
    Q_OBJECT
public:
    GdalDataAccess();

private:
    QDir _baseDataPath;
    QDir _baseDataOutputPath;

    NEW_TEST(GdalDataAccess);
private slots:

    void initTestCase();
    void accessingFeatureData();
    void tableAccess();
    void accessingRasterData();
};

#endif // DATAACCESS_H
