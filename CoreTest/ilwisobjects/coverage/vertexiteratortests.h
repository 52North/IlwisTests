#ifndef VERTEXITERATORTESTS_H
#define VERTEXITERATORTESTS_H

#include <QString>
#include <QTest>
#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class VertexIteratorTests : public IlwisTestCase
{
    Q_OBJECT

public:
    explicit VertexIteratorTests();

private:
    NEW_TEST(VertexIteratorTests);

private slots:
    void constructionTests();
    void lineStringTests();
    void pointTests();
    void polygonTests();
};

#endif // VERTEXITERATORTESTS_H
