#include <QUrl>
#include <QtTest>
#include <QString>
#include <QObject>
#include <QTextStream>

#include "kernel.h"
#include "catalog.h"
#include "symboltable.h"
#include "ilwiscontext.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "numericdomain.h"
#include "numericrange.h"
#include "columndefinition.h"
#include "table.h"
#include "domainitem.h"
#include "itemdomain.h"
#include "textdomain.h"
#include "identifieritem.h"
#include "identifierrange.h"
#include "attributerecord.h"
#include "coverage.h"
#include "feature.h"
#include "featurecoverage.h"
#include "catalogconnector.h"
#include "wfscatalogconnector.h"
#include "wfsconnector.h"
#include "wfs.h"
#include "wfsresponse.h"
#include "wfsfeature.h"
#include "wfscapabilitiesparser.h"
#include "wfsfeaturedescriptionparser.h"
#include "wfsfeatureparser.h"
#include "wfsfeatureconnector.h"
#include "wfsconnectortest.h"
#include "testutils.h"

#include "testsuite.h"

#define WFS_TEST_SERVER_1 "http://ogi.state.ok.us/geoserver/wfs?acceptVersions=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS"
#define WFS_TEST_SERVER_2 "http://nsidc.org/cgi-bin/atlas_north?service=WFS&acceptVersions=1.1.0&request=GetCapabilities"
#define WFS_TEST_SERVER_3 "http://www2.ign.es/sioseinspire?SERVICE=WFS&REQUEST=GetCapabilities"

using namespace Ilwis;
using namespace Wfs;

REGISTER_TEST(WfsConnectorTest);

WfsConnectorTest::WfsConnectorTest(): IlwisTestCase("WfsConnectorTest", "WfsConnectorTest")
{
    QUrl wfsUrl(WFS_TEST_SERVER_1);
    _wfs = new WebFeatureService(wfsUrl);
}

void WfsConnectorTest::shouldRecognizeExceptionReport()
{
    WfsResponse testResponse(Utils::openFile("extensions/testfiles/wfs_exceptionreport.xml"));
    DOTEST2(testResponse.isException(), "Response did not recognized exception report!");
}

void WfsConnectorTest::shouldParseExceptionReportWithDetails()
{
    WfsResponse testResponse(Utils::openFile("extensions/testfiles/wfs_exceptionreport.xml"));
    DOTEST2( !testResponse.parseException().isEmpty(), "No Exception report could be parsed!");
}

void WfsConnectorTest::shouldNotRecognizeExceptionReport()
{
    WfsResponse testResponse(Utils::openFile("extensions/testfiles/wfs_capabilities.xml"));
    DOTEST2( !testResponse.isException(), "Response recognized an exception message!");
}

void WfsConnectorTest::parseCorrectNumberOfFeatureTypesFromCapabilities()
{
    QUrl url("http://localhost/wfs?request=GetCapabilities&service=WFS");
    WfsResponse testResponse(Utils::openFile("extensions/testfiles/wfs_capabilities.xml"));
    WfsCapabilitiesParser parser( &testResponse, url);

    QList<WfsFeature> features;
    parser.parseFeatures(features);
    DOTEST2(features.size() == 2, "Wrong amount of feature types found.");

    QUrlQuery actualQuery1 = features.at(0).urlQuery();
    DOTEST2(actualQuery1.queryItemValue("request") == "GetFeature", QString("Query is incorrect '%1'").arg(actualQuery1.toString()));
    DOTEST2(actualQuery1.queryItemValue("featureName") == "ogi:quad100", QString("Query is incorrect '%1'").arg(actualQuery1.toString()));

    QUrlQuery actualQuery2 = features.at(1).urlQuery();
    DOTEST2(actualQuery2.queryItemValue("request") == "GetFeature", QString("Query is incorrect '%1'").arg(actualQuery2.toString()));
    DOTEST2(actualQuery2.queryItemValue("featureName") == "ogi:quad100_centroids", QString("Query is incorrect '%1'").arg(actualQuery2.toString()));
}

void WfsConnectorTest::shouldCreateITableFromFeatureDescription()
{
    QUrl url("http://ogi.state.ok.us/geoserver/wfs?VERSION=1.1.0&REQUEST=GetFeature&typeName=ogi%3Aquad100");
    WfsFeature featureResource(url); // TODO: replace when resource.getQuery() is implemented
    FeatureCoverage *fcoverage = new FeatureCoverage(featureResource);

    QMap<QString, QString> namespaceMappings;
    WfsResponse featureDescriptionResponse(Utils::openFile("extensions/testfiles/quad100.xsd"));
    WfsFeatureDescriptionParser parser( &featureDescriptionResponse);

    parser.parseSchemaDescription(fcoverage, namespaceMappings);
    ITable table = fcoverage->attributeTable();

    quint32 expected = 13;
    quint32 actual = table->columnCount();
    DOTEST2(actual == expected, QString("Incorrect number of columns (expected %1, was %2).").arg(expected, actual));

    WfsResponse featureResponse(Utils::openFile("extensions/testfiles/featurecollection.xml"));
    WfsFeatureParser featureParser( &featureResponse, fcoverage);
    featureParser.parseFeatureMembers(namespaceMappings);

    // TODO: Add tests here

    delete fcoverage;
}


void WfsConnectorTest::shouldPrepareWfsFeature() {
    //QUrl url("http://localhost/blah/?query=true");
//    QUrl url("http://ogi.state.ok.us/geoserver/wfs?VERSION=1.1.0&REQUEST=GetFeature&typeName=ogi%3Aquad100");
//    WfsFeature featureResource(url); // TODO: replace when resource.getQuery() is implemented
//    featureResource.setName("ogi:quad100");
//    WfsFeatureConnector featureConnector(featureResource);
//    Ilwis::FeatureCoverage *fcoverage = new Ilwis::FeatureCoverage(featureResource);

//    QString failureMsg("Could not load metadata for feature '%1'");
//    QVERIFY2(featureConnector.loadMetaData(fcoverage), failureMsg.arg("CURRENTLY HARD CODED!!").toLatin1().constData());
}

void WfsConnectorTest::testInitialFeatureHasEmptyBBox() {
    QUrl featureUrl("http://localhost/wfs?service=WFS&request=GetFeature&featureName=FeatureType&version=1.1.0");
    WfsFeature feature(featureUrl);
    DOTEST2(feature.bbox().isNull(), "BBox of initial Feature is not null!");
}




void WfsConnectorTest::cleanupTestCase() {
    delete _wfs;
}
