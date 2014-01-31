#include <QUrl>
#include <QtTest>
#include <QString>
#include <QObject>
#include <QTextStream>

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
#include "wfsfeature.h"
#include "wfscapabilitiesparser.h"
#include "wfsfeatureconnector.h"
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

void WfsConnectorTest::shouldRecognizeExceptionReport()
{
    WfsResponse testResponse;
    readTestResponseFromFile("extensions/testfiles/wfs_exceptionreport.xml", testResponse);

    try {
        QVERIFY2(testResponse.isException(), "Response did not recognized an exception message!");
    } catch(pugi::xpath_exception e) {
        QFAIL(QString("Could not evaluate xpath: %1").arg(e.what()).toLatin1().constData());
    }
}


void WfsConnectorTest::shouldNotRecognizeExceptionReport()
{
    WfsResponse testResponse;
    readTestResponseFromFile("extensions/testfiles/wfs_capabilities.xml", testResponse);

    try {
        QVERIFY2(!testResponse.isException(), "Response recognized an exception message!");
    } catch(pugi::xpath_exception e) {
        QFAIL(QString("Could not evaluate xpath: %1").arg(e.what()).toLatin1().constData());
    }
}

void WfsConnectorTest::shouldLoadFeatureMetadata()
{
    QUrl url("http://localhost/blah/?query=true");
    Resource featureResource(url, itFEATURE); // TODO: replace when resource.getQuery() is implemented
    WfsFeatureConnector featureConnector(featureResource);

    Ilwis::IlwisObject *feature = featureConnector.create();
    QString failureMsg("Could not load metadata for feature '%1'");
    QVERIFY2(featureConnector.loadMetaData(feature), failureMsg.arg("CURRENTLY HARD CODED!!").toLatin1().constData());
}


void WfsConnectorTest::parseCorrectNumberOfFeatureTypesFromCapabilities()
{

    QXmlStreamReader reader;
    QFile file("extensions/testfiles/wfs_capabilities.xml");
    file.open(QIODevice::ReadOnly);
    reader.setDevice( &file);

    WfsResponse testResponse;
    testResponse.setXmlReader( &reader);

    QUrl url("http://localhost/wfs");
    WfsCapabilitiesParser parser( &testResponse, url);

    try {
        QList<WfsFeature> features;
        parser.parseFeatures(features);
        QVERIFY2(features.size() == 2, "Wrong amount of feature types found.");
    } catch(pugi::xpath_exception e) {
        QFAIL(QString("Could not evaluate xpath: %1").arg(e.what()).toLatin1().constData());
    }

}

void WfsConnectorTest::testInitialFeatureHasEmptyBBox() {
    QUrl featureUrl("http://localhost/wfs?service=WFS&request=GetFeature&featureName=FeatureType&version=1.1.0");
    WfsFeature feature(featureUrl);
    QVERIFY2(feature.bbox().isNull(), "BBox of initial Feature is not null!");
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

void WfsConnectorTest::readTestResponseFromFile(QString path, WfsResponse &response) {
    QFile file(path);
    QVERIFY2(file.open(QIODevice::ReadOnly), QString("Could not find test file '%1'!").arg(path).toLatin1().constData());

    QString content;
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        content.append(line);
    }
    file.close();
    response.setContent(content);
}

void WfsConnectorTest::cleanupTestCase() {
    delete _wfs;
}

#include "moc_tst_wfsconnectortest.cpp"
