#include <QFileInfo>
#include <QUrl>
#include <QDir>

#include "geos/io/ParseException.h"
#include "geos/geom/GeometryFactory.h"
#include "geos/geom/LinearRing.h"
#include "geos/geom/Polygon.h"

#include "kernel.h"
#include "ilwisobject.h"
#include "ilwisdata.h"
#include "geometries.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"
#include "catalog.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "connectorinterface.h"
#include "ilwisobjectconnector.h"
#include "catalogexplorer.h"
#include "catalogconnector.h"
#include "attributerecord.h"
#include "coordinatesystem.h"
#include "feature.h"
#include "coverage.h"
#include "featurecoverage.h"
#include "featureiterator.h"
#include "feature.h"
#include "geometryhelper.h"

#include "wfsdemo.h"
#include "wfscatalogexplorer.h"
#include "wfstestconstants.h"

#include "testsuite.h"

using namespace Ilwis;
using namespace Wfs;

REGISTER_TEST(WfsDemo);

WfsDemo::WfsDemo():
    IlwisTestCase("WfsDemo", "Demo")
{
}

void WfsDemo::wfsCatalog_prepareAndSetAsWorkingCatalog_hasWfsResourcesRegistered()
{
    try {
        ICatalog cat("http://ogi.state.ok.us/geoserver/wfs?acceptVersions=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS");
        //ICatalog cat("http://nsidc.org/cgi-bin/atlas_north?acceptVersions=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS");

        std::vector<Resource> items = cat->items();
        Resource feature(items.front());
        IFeatureCoverage coverage;
        if ( !coverage.prepare(feature)) {
            QFAIL("Could not prepare coverage.");
        }

        ITable table = coverage->attributeTable();
        //DOCOMPARE(table->columnCount(), (unsigned int)12, "12 attribute columns expected in table.");

    //    FeatureIterator fiter(coverage);
    //    FeatureIterator endIter = end(coverage);
    //    for(; fiter != endIter; ++fiter) {
    //        UPFeatureI& feature = *fiter;
    //        const geos::geom::Geometry* geometry = feature->geometry().get();
    //        std::cout << GeometryHelper::toWKT(geometry);
    //    }

        coverage->connectTo(makeOutputPath("ogi.shp"), "ESRI Shapefile", "gdal", IlwisObject::cmOUTPUT);
        coverage->store();
    } catch (std::exception& e) {
        QFAIL(QString("exception occured: %1").arg(e.what()).toLatin1().constData());
    }

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
