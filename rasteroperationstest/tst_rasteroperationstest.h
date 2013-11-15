#ifndef TST_RASTEROPERATIONSTEST_H
#define TST_RASTEROPERATIONSTEST_H

#include <QObject>

class RasterOperationsTest : public QObject
{
    Q_OBJECT

public:
    RasterOperationsTest();
    RasterOperationsTest(QString* testDataLocation);

private Q_SLOTS:
    void initTestCase();
    void testLinearStretchOperation();
    void cleanupTestCase();
};


#endif // TST_RASTEROPERATIONSTEST_H
