#include "ilwis.h"
#include "testsuite.h"
#include "kernel.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "raster.h"
#include "pixeliterator.h"
#include "attributerecord.h"
#include "catalog.h"
#include "ilwiscontext.h"
#include "rasteroperations.h"

REGISTER_TEST(RasterOperations);

RasterOperations::RasterOperations() : IlwisTestCase("RasterOperationTest","RasteOperationTest")
{
}

void RasterOperations::initTestCase()
{
    _baseDataPath = TestSuite::instance()->inputDataPath();
    if ( !_baseDataPath.exists())
        throw SkipTest("no data path defined");
    _baseDataOutputPath = TestSuite::instance()->outputDataPath();
    if ( !_baseDataOutputPath.exists())
        throw SkipTest("no data output path defined");
}
