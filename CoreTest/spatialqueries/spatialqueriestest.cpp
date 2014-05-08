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
     DOTEST( indexes.size() == 2,"select as member of featurecoverage");

}
