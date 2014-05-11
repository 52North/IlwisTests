#include "kernel.h"
#include "ilwisdata.h"
#include "geos/geom/Coordinate.h"
#include "coordinate.h"
#include "location.h"
#include "box.h"
#include "coordinatesystem.h"
#include "testsuite.h"
#include "csy.h"

REGISTER_TEST(CsyTests);

CsyTests::CsyTests() : IlwisTestCase("CsyTest","CoreTest")
{
}

void CsyTests::wkt() {
    Ilwis::ICoordinateSystem csy;
    DOTEST(csy.prepare("code=proj4:+proj=utm +zone=29 +a=6378249.2 +b=6356515 +towgs84=-23,259,-9,0,0,0,0") == true,"loading from proj4 definition");

    QString swkt = csy->toWKT(4);
    if ( swkt == "?")
        return;
}
