#ifndef SandBox_H
#define SandBox_H

#include <QTest>
#include "ilwistestclass.h"
#include "testmacros.h"

#include "commandhandler.h"
#include "symboltable.h"

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
