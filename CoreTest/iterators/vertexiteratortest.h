#ifndef VERTEXITERATORTEST_H
#define VERTEXITERATORTEST_H

#include <QString>
#include <QDir>
#include "kernel.h"
#include "geos/geom/Coordinate.h"
#include "coordinate.h"
#include "ilwistestclass.h"

class VertexIteratorTest : public IlwisTestCase
{
    Q_OBJECT
public:
    VertexIteratorTest();

   NEW_TEST(VertexIteratorTest);

private slots:

   void initTestCase();
   void constructionTests();
   void lineStringTests();
   void pointTests();
   void polygonTests();
private:
    QDir _baseDataPath;
    QDir _baseDataOutputPath;
};

#endif // VERTEXITERATORTEST_H
