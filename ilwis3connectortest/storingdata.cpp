#include "ilwis.h"
#include "../TestSuite/testsuite.h"
#include "raster.h"
#include "table.h"
#include "ellipsoid.h"
#include "projection.h"
#include "coordinatesystem.h"
#include "featurecoverage.h"
#include "feature.h"
#include "featureiterator.h"
#include "storingdata.h"

REGISTER_TEST(StoringData);

StoringData::StoringData() : IlwisTestCase("StoringData", "Ilwis3ConnectorTest")
{
}

void StoringData::storeGdalFormats(){
//    Ilwis::IRasterCoverage map1;
//    DOTEST(map1.prepare(makeInputPath("PR_2003_allyear.bsq")), "loading bsq");

//    map1->name("aaraster2");
//    map1->connectTo(makeOutputPath("aaraster2.mpl"), "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
//    map1->createTime(Ilwis::Time::now());
//    map1->store();

    Ilwis::IRasterCoverage map2;
    DOTEST(map2.prepare(makeInputPath("GCL_INT.tif")), "loading tif");

    map2->name("aaraster3");
    map2->connectTo(makeOutputPath("aaraster2.mpl"), "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
    map2->createTime(Ilwis::Time::now());
    map2->store();
}
