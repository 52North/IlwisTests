#ifndef WFSTEST_H
#define WFSTEST_H

#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class PostgresDemo: public IlwisTestCase
{
    Q_OBJECT
    
public:
    PostgresDemo();

private:
    NEW_TEST(PostgresDemo);

private Q_SLOTS:
    void storeRailsAsShapeFile();
    void storeStatesAsShapeFile();

};

#endif // WFSTEST_H
