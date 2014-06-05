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
#include "ellipsoid.h"
#include "projection.h"
#include "coordinatesystem.h"
#include "attributerecord.h"
#include "feature.h"
#include "featurecoverage.h"
#include "featureiterator.h"
#include "storingdata.h"

REGISTER_TEST(StoringData);

StoringData::StoringData() : IlwisTestCase("Storing data", "Ilwis3ConnectorTest")
{
}
