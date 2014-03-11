#include <QFileInfo>
#include <QUrl>

#include "geos/io/ParseException.h"
#include "geos/geom/GeometryFactory.h"
#include "geos/geom/LinearRing.h"
#include "geos/geom/Polygon.h"

#include "kernel.h"
#include "ilwisdata.h"
#include "geometries.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"
#include "catalog.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "attributerecord.h"
#include "coordinatesystem.h"
#include "feature.h"
#include "coverage.h"
#include "featurecoverage.h"

#include "wfscatalogconnector.h"

#include "wfsdemo.h"
#include "wfstestconstants.h"
#include "testsuite.h"

REGISTER_TEST(WfsDemo);

using namespace Ilwis;
using namespace Wfs;

WfsDemo::WfsDemo(): IlwisTestCase("WfsDemo", "Demo")
{
}

void WfsDemo::wfsCatalog_prepareAndSetAsWorkingCatalog_hasWfsResourcesRegistered()
{

//    Catalog cat;
//    if ( !cat.prepare( { WFS_TEST_SERVER_1 })) {
//        QFAIL("Unable to prepare catalog.");
//    }
//    context()->setWorkingCatalog(cat);

//    std::list<Resource> items = context()->workingCatalog()->items();
//    qDebug() << items.size();
}

void WfsDemo::wfsCatalog_prepareFeatureCoverageViaUrl_validFeatureCoverage()
{
//    QUrl wfsUrl(WFS_TEST_SERVER_1);
//    Resource wfsInstance(wfsUrl, itFEATURE);
//    ConnectorInterface *connector = WfsCatalogConnector::create(wfsInstance, false);
//    if ( !connector->loadItems()) {
//        QFAIL("Could not load catalog items and register them to the kernel.");
//    }

//    QUrl okmunibnd("http://ogi.state.ok.us/geoserver/wfs?request=GetFeature&service=WFS&typeName=ogi:okmunibnd");
//    Resource feature(okmunibnd, itFEATURE);
//    feature.prepare();
//    if ( !feature.isValid()) {
//        QFAIL("Prepared an invalid feature.");
//    }
//    IFeatureCoverage coverage;
//    if ( !coverage.prepare(feature)) {
//        QFAIL("Could not prepare coverage.");
//    }

}
