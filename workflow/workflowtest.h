#ifndef WorkflowTest_H
#define WorkflowTest_H

#include <QTest>
#include "kernel.h"
#include "testsuite.h"
#include "ilwistestclass.h"
#include "testmacros.h"

class WorkflowTest : public IlwisTestCase
{
    Q_OBJECT

public:
    WorkflowTest();
    WorkflowTest(QString* testDataLocation);

private:
    NEW_TEST(WorkflowTest);

private Q_SLOTS:
    void executeStringOperationsWorkflow();
    void executeCalculateNDVIWorkflow();
};



#endif // WorkflowTest_H
