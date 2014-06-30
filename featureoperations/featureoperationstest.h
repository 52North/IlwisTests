#ifndef FeatureOperations_H
#define FeatureOperations_H

#include <QTest>
#include "ilwistestclass.h"
#include "testmacros.h"

#include "commandhandler.h"
#include "symboltable.h"

class FeatureOperations : public IlwisTestCase
{
    Q_OBJECT

public:
    FeatureOperations();
    FeatureOperations(QString* testDataLocation);

private:
    NEW_TEST(FeatureOperations);



private Q_SLOTS:


    void pointrastercross();
};



#endif // FeatureOperations_H
