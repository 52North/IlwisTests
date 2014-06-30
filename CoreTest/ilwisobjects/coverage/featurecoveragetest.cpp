#include "kernel.h"
#include "testsuite.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "raster.h"
#include "coverage.h"
#include "ellipsoid.h"
#include "projection.h"
#include "coordinatesystem.h"
#include "attributerecord.h"
#include "feature.h"
#include "featurecoverage.h"
#include "geometryhelper.h"
#include "numericdomain.h"
#include "domainitem.h"
#include "itemdomain.h"
#include "identifieritem.h"
#include "identifierrange.h"
#include "juliantime.h"
#include "featurecoveragetest.h"

REGISTER_TEST(FeatureCoverageTest);

FeatureCoverageTest::FeatureCoverageTest() : IlwisTestCase("FeatureCoverageTest" , "CoreTest")
{
}




