#include "raster.h"
#include "testsuite.h"
#include "table.h"
#include "ellipsoid.h"
#include "featurecoverage.h"
#include "feature.h"
#include "geometryhelper.h"
#include "numericdomain.h"
#include "domainitem.h"
#include "itemdomain.h"
#include "identifieritem.h"
#include "identifierrange.h"
#include "juliantime.h"
#include "featureiterator.h"

#include "featurecoveragetest.h"

REGISTER_TEST(FeatureCoverageTest);

using namespace Ilwis;

FeatureCoverageTest::FeatureCoverageTest() : IlwisTestCase("FeatureCoverageTest" , "CoreTest")
{
}

void FeatureCoverageTest::testVariants() {
    Ilwis::IFeatureCoverage featureCoverage;
    featureCoverage.prepare();

    Ilwis::ICoordinateSystem csy("code=proj4:+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs");

    Ilwis::Envelope env(Ilwis::LatLon(50,-30), Ilwis::LatLon(-50, 60));
    featureCoverage->coordinateSystem(csy);
    featureCoverage->envelope(env);

    Ilwis::ITimeDomain dom;
    dom.prepare();
    dom->range(new Ilwis::TimeInterval("20090101", "20110101"));
    std::vector<QString> times = {"20090101","20090131","20090602","20090703", "20100109","20110101"};

    featureCoverage->attributeDefinitionsRef().addColumn("population", "value");
    featureCoverage->attributeDefinitionsRef().setSubDefinition(dom,times);

    Ilwis::SPFeatureI feature1 = featureCoverage->newFeature(0);

    geos::geom::Geometry *geom = Ilwis::GeometryHelper::fromWKT("Linestring(40 20, 10 12, -20 -10)", featureCoverage->coordinateSystem().ptr());
    feature1->geometry(geom);
    feature1("population", 200);

    geom = Ilwis::GeometryHelper::fromWKT("Linestring(30 10, 10 15, -23 -12)",featureCoverage->coordinateSystem().ptr());

    feature1->createSubFeature("20090101", geom);

    auto *attrdef = new Ilwis::FeatureAttributeDefinition();
    attrdef->addColumn("temperature", "value");
    featureCoverage->attributeDefinitionsRef().featureAttributeDefinition(attrdef);

    feature1["20090101"]("temperature", 26.5);

    double v = feature1["20090101"]("temperature").toDouble();

    FeatureIterator featureIter(featureCoverage);
    featureIter.flow(FeatureIterator::fDEPTHFIRST);

    while(featureIter != featureIter.end()) {
        SPFeatureI f = (*featureIter);
        f->geometry(); // test if geometry is null
        DOTEST(true, "geometry of (sub)feature not null.");
        featureIter++; // move to next
    }






}


