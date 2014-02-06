#include <QUrl>
#include <QtTest>
#include <QString>
#include <QObject>
#include <QTextStream>

#include "kernel.h"
#include "catalog.h"
#include "symboltable.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"

#include "ilwisdata.h"
#include "domain.h"
#include "coverage.h"
#include "columndefinition.h"
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
    QFile *file = new QFile("extensions/testfiles/wfs_exceptionreport.xml");
    file->open(QIODevice::ReadOnly);
    testResponse.setDevice(file);

    QVERIFY2(testResponse.isException(), "Response did not recognized exception report!");
    file->close(); // no delete as file is owned by response
}

void WfsConnectorTest::shouldParseExceptionReportWithDetails()
{
    WfsResponse testResponse;
    QFile *file = new QFile("extensions/testfiles/wfs_exceptionreport.xml");
    file->open(QIODevice::ReadOnly);
    testResponse.setDevice(file);

    QString exceptionLog = testResponse.parseException();
    QVERIFY2( !exceptionLog.isEmpty(), "No Exception report could be parsed!");
    qDebug() << "parsed exception report (to verify): " << exceptionLog;
    file->close(); // no delete as file is owned by response
}

void WfsConnectorTest::shouldNotRecognizeExceptionReport()
{
    WfsResponse testResponse;
    QFile *file = new QFile("extensions/testfiles/wfs_capabilities.xml");
    file->open(QIODevice::ReadOnly);
    testResponse.setDevice(file);

    QVERIFY2( !testResponse.isException(), "Response recognized an exception message!");
    file->close(); // no delete as file is owned by response
}

void WfsConnectorTest::shouldLoadFeatureMetadata()
{
    //QUrl url("http://localhost/blah/?query=true");
    QUrl url("http://ogi.state.ok.us/geoserver/wfs?VERSION=1.1.0&REQUEST=GetFeature&typeName=ogi%3Aquad100");
    Resource featureResource(url, itFEATURE); // TODO: replace when resource.getQuery() is implemented
    WfsFeatureConnector featureConnector(featureResource);

    Ilwis::IlwisObject *feature = featureConnector.create();
    QString failureMsg("Could not load metadata for feature '%1'");
    QVERIFY2(featureConnector.loadMetaData(feature), failureMsg.arg("CURRENTLY HARD CODED!!").toLatin1().constData());
}


void WfsConnectorTest::parseCorrectNumberOfFeatureTypesFromCapabilities()
{
    WfsResponse testResponse;
    QFile *file = new QFile("extensions/testfiles/wfs_capabilities.xml");
    file->open(QIODevice::ReadOnly);
    testResponse.setDevice(file);

    QUrl url("http://localhost/wfs");
    WfsCapabilitiesParser parser( &testResponse, url);

    QList<WfsFeature> features;
    parser.parseFeatures(features);
    QVERIFY2(features.size() == 2, "Wrong amount of feature types found.");
    file->close(); // no delete as file is owned by response
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


void WfsConnectorTest::cleanupTestCase() {
    delete _wfs;
}

#include "moc_tst_wfsconnectortest.cpp"
