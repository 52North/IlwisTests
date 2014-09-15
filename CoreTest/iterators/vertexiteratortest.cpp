#include "geos/geom/Geometry.h"
#include "geos/geom/Coordinate.h"
//#include "geos/geom/Coordinate.inl"
#include "geos/geom/LineString.h"
#include "geos/geom/Point.h"
#include "geos/geom/Polygon.h"
#include "geos/io/ParseException.h"
#include "coverage.h"
#include "errorobject.h"
#include "featurecoverage.h"
#include "feature.h"
#include "vertexiterator.h"
#include "geometryhelper.h"
#include "../TestSuite/testsuite.h"
#include "vertexiteratortest.h"

REGISTER_TEST(VertexIteratorTest);

VertexIteratorTest::VertexIteratorTest() : IlwisTestCase("VertexIterator","CoreTest")
{
}

void VertexIteratorTest::initTestCase()
{
    _baseDataPath = TestSuite::instance()->inputDataPath();
    if ( !_baseDataPath.exists())
        throw SkipTest("no data path defined");
    _baseDataOutputPath = TestSuite::instance()->outputDataPath();
    if ( !_baseDataOutputPath.exists())
        throw SkipTest("no data output path defined");
}

void VertexIteratorTest::constructionTests()
{
    try{
    Ilwis::VertexIterator vertices("Linestring(16.34 78.90, 14.55 74.23, 10.98 66.90)");
    std::vector<geos::geom::Coordinate> coords;
    while(vertices != end(vertices))
    {
        coords.push_back(*vertices);
        ++vertices;
    }

    DOTEST(coords.size() == 3, "Iterated over right number of vertices");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void VertexIteratorTest::lineStringTests()
{
    try{
    Ilwis::VertexIterator vertices1("Linestring(16.34 78.90, 14.55 74.23, 10.98 66.90)");
    Ilwis::VertexIterator vertices2("Linestring(16.34 78.05, 14.13 74.23, 10.04 66.90)");
    Ilwis::VertexIterator vertices21("Linestring(16.34 78.05, 14.13 74.23, 10.04 66.90)");      //same as vertices2
    Ilwis::VertexIterator vertices3("Multilinestring((16.34 78.05, 14.13 74.23), (10.04 66.90, 56.02 34.03))");
    Ilwis::VertexIterator vertices4("Multilinestring((16.34 78.05, 14.13 74.23), (10.04 66.90, 56.02 34.03))"); //same as vertices3

    geos::geom::Coordinate coordSingle{vertices1[0]};
    DOTEST(coordSingle.toString() == vertices1[0].toString(), "Copied the right coordinate from linepoint");
    geos::geom::Coordinate coords{vertices4[2]};
    DOTEST(coords.toString() == vertices4[2].toString(), "Copied the right coordinate from linepoint");

    DOTEST((vertices21 == vertices2) == true, "Same set of data" );
    DOTEST((vertices3 == vertices4) == true, "Same set of data" );
    DOTEST((vertices1 == vertices2) == false, "Not the same iterators" );
    DOTEST((vertices1 != vertices2) == true, "Not the same iterators" );

    ++vertices1;
    DOTEST((vertices1 > vertices2) == true, "Iter1 has an higher index than Iter2" );
    DOTEST((vertices2 > vertices1) == false, "Iter2 has not an higher index than Iter1" );
    --vertices1;
    ++vertices2;
    DOTEST((vertices1 < vertices2) == true, "Iter2 has now an higher index than Iter1" );
    DOTEST((vertices2 < vertices1) == false, "Iter1 has now not an higher index than Iter2" );

    DOTEST((vertices3 <= vertices4) == true, "Iter 3 has a smaller or equal index to Iter4");

    vertices4+=4;
    DOTEST((vertices3 <= vertices4) == true, "Iter 3 still has a smaller or equal index to Iter4");
    DOTEST((vertices4 <= vertices3) == false, "Iter 4 now has not a smaller or equal index to Iter4");

    vertices3+=4;
    DOTEST((vertices3 >= vertices4) == true, "Iter 3 has a bigger or equal index to Iter4");

    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void VertexIteratorTest::pointTests()
{
    try{
    QString coords {"MULTIPOINT(16.34 78.90, 14.55 74.23, 10.98 66.90)"};
    Ilwis::VertexIterator singlePoint("POINT(16.34 78.90)");
    Ilwis::VertexIterator singlePoint2("POINT(16.34 78.90)");
    Ilwis::VertexIterator multiPoint1(coords);
    Ilwis::VertexIterator multiPoint2("MULTIPOINT(16.67 18.90, 14.45 70.83, 10.98 66.90)");
    Ilwis::VertexIterator multiPoint3(coords);

    geos::geom::Coordinate coordSingle{singlePoint[0]};
    geos::geom::Coordinate coordMulti{multiPoint1[1]};


    DOTEST(coordSingle.toString() == singlePoint[0].toString(), "Copied the right coordinate from single point");
    DOTEST(coordMulti.toString() == multiPoint1[1].toString(), "Copied the right coordinate from multi point");
    coordSingle = *multiPoint3;
    DOTEST(coordSingle.toString() == multiPoint3[0].toString(), "Copied the right referenced coordinate from multi point");
    coordSingle = *singlePoint;
    DOTEST(coordSingle.toString() == singlePoint[0].toString(), "Copied the right referenced coordinate from multi point");

    DOTEST((singlePoint == singlePoint2) == true, "Iterators have the same point." );
    DOTEST((multiPoint1 == multiPoint3) == true, "Iterators have the same points." );
    DOTEST((multiPoint1 == multiPoint2) == false, "Not the same iterators" );
    DOTEST((multiPoint1 != multiPoint2) == true, "Not the same iterators" );

    ++multiPoint1;
    DOTEST((multiPoint1 > multiPoint2) == true, "Iter1 has an higher index than Iter2" );
    DOTEST((multiPoint2 > multiPoint1) == false, "Iter2 has not an higher index than Iter1" );
    --multiPoint1;
    ++multiPoint2;
    DOTEST((multiPoint1 < multiPoint2) == true, "Iter2 has now an higher index than Iter1" );
    DOTEST((multiPoint2 < multiPoint1) == false, "Iter1 has now not an higher index than Iter2" );
    --multiPoint2;

    DOTEST((multiPoint1 <= multiPoint2) == true, "Iter 1 has a smaller or equal index to Iter2");

    multiPoint2+=4;
    DOTEST((multiPoint1 <= multiPoint2) == true, "Iter 1 still has a smaller or equal index to Iter2");
    DOTEST((multiPoint2 <= multiPoint1) == false, "Iter 2 now has not a smaller or equal index to Iter1");

    multiPoint1+=4;
    DOTEST((multiPoint1 >= multiPoint2) == true, "Iter 1 has a bigger or equal index to Iter2");
    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }
}

void VertexIteratorTest::polygonTests()
{
    try{
    Ilwis::VertexIterator poly1("POLYGON ((30 10, 40 40, 20 40, 10 20, 30 10))");
    Ilwis::VertexIterator poly2("POLYGON ((10 10, 30 20, 40 30, 10 20, 10 10))");
    Ilwis::VertexIterator poly3("POLYGON ((30 10, 40 40, 20 40, 10 20, 30 10))");
    Ilwis::VertexIterator poly4("MULTIPOLYGON(((40 40, 20 45, 45 30, 40 40)),((20 35, 10 30, 10 10, 30 5, 45 20, 20 35), (30 20, 20 15, 20 25, 30 20)))");



    geos::geom::Coordinate coord1{*poly1};
    geos::geom::Coordinate coord2{*poly1};

    DOTEST(poly1 == poly3, "They have the same set of data");

    DOTEST(coord1.toString() == coord2.toString(), "Reference the same coordinate");
    ++poly1;
    coord1 = *poly1;
    DOTEST(coord1.toString() != coord2.toString(), "Don't reference the same coordinate");
    DOTEST(coord1.toString() == poly1[1].toString(), "Copied the right coordinate");


    DOTEST((poly1 == poly2) == false, "Not the same iterators" );
    DOTEST(poly1 != poly2, "Not the same iterators" );

    ++poly1;
    DOTEST((poly1 > poly2) == true, "Iter1 has an higher index than Iter2" );
    DOTEST((poly2 > poly1) == false, "Iter2 has not an higher index than Iter1" );
    poly1-=2;
    ++poly2;
    DOTEST((poly1 < poly2) == true, "Iter2 has now an higher index than Iter1" );
    DOTEST((poly2 < poly1) == false, "Iter1 has now not an higher index than Iter2" );
    --poly2;

    DOTEST((poly1 <= poly2) == true, "Iter 1 has a smaller or equal index to Iter2");

    poly2+=4;
    DOTEST((poly1 <= poly2) == true, "Iter 1 still has a smaller or equal index to Iter2");
    DOTEST((poly2 <= poly1) == false, "Iter 2 now has not a smaller or equal index to Iter1");

    poly1+=4;
    DOTEST((poly1 >= poly2) == true, "Iter 1 has a bigger or equal index to Iter2");

    int countSubGeom = 1; // start count at 1 because the start geom is already a sub geom;
    int countHoles= 0;
    while(poly4 != end(poly4)){
        if ( poly4.nextSubGeometry()){
            ++countSubGeom;
            if ( poly4.isInteriorVertex())
                ++countHoles;
        }
        ++poly4;
    }
    DOTEST((countSubGeom) == 3 && countHoles == 1, "2 polygons, one hole");

    } catch (Ilwis::ErrorObject& err){
        QString error = "Test threw exception : " + err.message();
        QFAIL(error.toLatin1());
    }



}





