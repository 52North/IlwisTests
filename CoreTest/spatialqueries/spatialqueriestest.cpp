#include "ilwis.h"
#include "../TestSuite/testsuite.h"
#include "kernel.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "raster.h"
#include "coverage.h"
#include "geos/geom/LineString.h"
#include "ellipsoid.h"
#include "projection.h"
#include "coordinatesystem.h"
#include "attributerecord.h"
#include "feature.h"
#include "featurecoverage.h"
#include "featureiterator.h"
#include "vertexiterator.h"
#include "geometryhelper.h"
#include "ilwiscontext.h"
#include "catalog.h"
#include "spatialqueriestest.h"

REGISTER_TEST(SpatialQueriesTest);

SpatialQueriesTest::SpatialQueriesTest() : IlwisTestCase("SpatialQueriesTest","CoreTest")
{
}

void SpatialQueriesTest::initTestCase()
{
    _baseDataPath = TestSuite::instance()->inputDataPath();
    if ( !_baseDataPath.exists())
        throw SkipTest("no data path defined");
    _baseDataOutputPath = TestSuite::instance()->outputDataPath();
    if ( !_baseDataOutputPath.exists())
        throw SkipTest("no data output path defined");
}

void SpatialQueriesTest::basic() {
     Ilwis::context()->setWorkingCatalog(Ilwis::ICatalog(QString("file:///%1").arg(_baseDataPath.absolutePath())));
     QString expr = "script bb=indexes from Kenya.mpa where contains(\"multipoint(39.434229 -1.262508,34.560120 -0.212529)\") and SQKM < 17000.00";
     Ilwis::SymbolTable tbl;
     Ilwis::ExecutionContext ctx;
     Ilwis::commandhandler()->execute(expr, &ctx, tbl);
     Indices indexes = tbl.getValue<Indices>(ctx._results[0]);
     DOTEST( indexes.size() == 1,"double condition, one spatial, one attribute");

     Ilwis::IFeatureCoverage fc("kenya.mpa");
     indexes = fc->select("contains(\"multipoint(39.434229 -1.262508,34.560120 -0.212529)\")");
     DOTEST( indexes.size() == 2,"select with contain as member of featurecoverage");

     indexes = fc->select("intersects(\"linestring(34.486176 1.628373, 36.447845 0.544293,40.655109 -3.753312)\")");
     DOTEST( indexes.size() == 4,"select with intersect as member of featurecoverage");

     indexes = fc->select("covers(\"polygon((35.905805 0.518481, 35.983239 -1.636774,37.828757 -1.817454,37.828757 0.518481,35.905805 0.518481))\")");
     DOTEST( indexes.size() == 2,"select with covers as member of featurecoverage");

     indexes = fc->select("coveredby(\"point(37.183473 3.177059)\")");
     DOTEST( indexes.size() == 1,"select with coveredby as member of featurecoverage");

     indexes = fc->select("disjoint(\"polygon((35.905805 0.518481, 35.983239 -1.636774,37.828757 -1.817454,37.828757 0.518481,35.905805 0.518481))\")");
     DOTEST( indexes.size() == 4,"select with disjoint as member of featurecoverage");

}
