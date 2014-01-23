#include <QUrl>
#include <QtTest>
#include <QString>
#include <QObject>

#include "pugixml/pugixml_global.h"
#include "pugixml/pugixml.hpp"

#include "kernel.h"
#include "catalog.h"
#include "symboltable.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"

#include "ilwisdata.h"
#include "domain.h"
#include "coverage.h"
#include "polygon.h"
#include "columndefinition.h"
#include "geometry.h"
#include "attributerecord.h"
#include "feature.h"
#include "featurecoverage.h"
#include "catalogconnector.h"
#include "wfscatalogconnector.h"
#include "wfsconnector.h"
#include "wfs.h"
#include "wfsresponse.h"
#include "tst_wfsconnectortest.h"

#define WFS_TEST_SERVER_1 "http://ogi.state.ok.us/geoserver/wfs?acceptVersions=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS"
#define WFS_TEST_SERVER_2 "http://nsidc.org/cgi-bin/atlas_north?service=WFS&acceptVersions=1.1.0&request=GetCapabilities"
#define WFS_TEST_SERVER_3 "http://www2.ign.es/sioseinspire?SERVICE=WFS&REQUEST=GetCapabilities"

using namespace Ilwis;
using namespace Wfs;

WfsConnectorTest::WfsConnectorTest()
{
    QUrl wfsUrl(WFS_TEST_SERVER_1);
    _wfs = new WebFeatureService(wfsUrl);
}


void WfsConnectorTest::initTestCase() {
    QString url(WFS_TEST_SERVER_1);

    QUrl s(url);
    Catalog cat;
    boolean prepared = cat.prepare(s);
    QVERIFY2(prepared, QString("could not prepare WFS '%1'").arg(url).toLatin1().constData());
    context()->setWorkingCatalog(cat);
}


void WfsConnectorTest::parseFeatureTypesFromCapabilities() {

    pugi::xml_document doc;

    // use the following three lines to get Capabilities from remote
//    WfsResponse *response = _wfs->getCapabilities();
//    QString capabilities = response->getContent();
//    std::istringstream cs(capabilities.toStdString());
//    doc.load(cs);

    // the following line uses capabilities from file
    doc.load_file("extensions/testfiles/wfs_capabilities.xml");

    pugi::xpath_node_set featureTypes = doc.select_nodes("/*/FeatureTypeList/FeatureType");
    std::for_each (featureTypes.begin(), featureTypes.end(), [](pugi::xpath_node featureType) {

        // TODO: compile to xpath_query objects

        qDebug() << "featureType name: " << featureType.node().child("Name").text().as_string();
    });

    QVERIFY2(featureTypes.size() == 2, "Wrong amount of feature types found.");

}


void WfsConnectorTest::sandbox() {
    QString url("http://localhost/wfs?ACCEPTVERSIONS=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS");
    QUrl capabilitiesUrl(url);
    Resource wfsCatalog(capabilitiesUrl, itCATALOG);
    qDebug() << wfsCatalog.container();
}

void WfsConnectorTest::canUseValidWfsUrlWithCapitalParameters() {
    QString url("http://localhost/wfs?ACCEPTVERSIONS=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS");
    QUrl capabilitiesUrl(url);
    Resource wfsCatalog(capabilitiesUrl, itCATALOG);
    WfsCatalogConnector connector(wfsCatalog);
    QVERIFY2(connector.canUse(wfsCatalog), QString("Connector indicates it can't use valid WFS: %1").arg(url).toLatin1().constData());
}

void WfsConnectorTest::canUseValidWfsUrlWithMixedCapitalParameters() {
    QString url("http://localhost/wfs?acceptVersions=1.1.0&request=GetCapabilities&service=WFS");
    Resource wfs1(url, itCATALOG);
    WfsCatalogConnector connector(wfs1);
    QVERIFY2(connector.canUse(wfs1), QString("Connector indicates it can't use valid WFS: %1").arg(url).toLatin1().constData());
}



void WfsConnectorTest::cleanupTestCase() {
    delete _wfs;
}

#include "moc_tst_wfsconnectortest.cpp"
