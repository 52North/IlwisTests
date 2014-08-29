#ifndef SandBox_H
#define SandBox_H

#include <QTest>
#include "ilwistestclass.h"
#include "testmacros.h"

#include "commandhandler.h"
#include "symboltable.h"

/**
 * The sandbox tester is only meant for local experimenting. None of the tests will be part of the formal
 * tests of ilwis. All test here maybe changed, deleted by anyone. It is part of the test framework though
 * so it will work in that context
 *
 */
class SandBox : public IlwisTestCase
{
    Q_OBJECT

public:
    SandBox();
    SandBox(QString* testDataLocation);

private:
    NEW_TEST(SandBox);



private Q_SLOTS:


    void sometest();
};



#endif // SandBox_H
