#include <QUrl>
#include <QtTest>
#include <QString>
#include <QObject>
#include <QTextStream>

#include "geos/geom/LinearRing.h"
#include "geos/geom/Polygon.h"

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
#include "connectorinterface.h"
#include "ilwisobjectconnector.h"
#include "catalogexplorer.h"
#include "catalogconnector.h"

#include "wfs.h"
#include "wfsresponse.h"
#include "wfsfeature.h"
#include "wfscapabilitiesparser.h"
#include "wfsparsingcontext.h"
#include "wfsfeaturedescriptionparser.h"
#include "wfsfeatureparser.h"
#include "wfsfeatureconnector.h"
#include "wfsparsertest.h"

#include "testutils.h"
#include "testsuite.h"

using namespace Ilwis;
using namespace Wfs;

REGISTER_TEST(WfsParserTest);

WfsParserTest::WfsParserTest():
    IlwisTestCase("WfsParserTest", "WfsConnectorTest")
{
}

void WfsParserTest::parseCorrectNumberOfFeatureTypesFromCapabilities()
{
    QUrl url("http://localhost/wfs?request=GetCapabilities&service=WFS");
    WfsResponse testResponse(Utils::openFile("testcases/testfiles/wfs_capabilities.xml"));
    WfsCapabilitiesParser parser( &testResponse, url);

    std::vector<Resource> features;
    parser.parseFeatures(features);
    DOTEST2(features.size() == 2, "Wrong amount of feature types found.");

    QUrlQuery actualQuery1 = features.at(0).urlQuery();
    DOTEST2(actualQuery1.queryItemValue("request") == "GetFeature", QString("Query is incorrect '%1'").arg(actualQuery1.toString()));
    DOTEST2(actualQuery1.queryItemValue("typeName") == "ogi:quad100", QString("Query is incorrect '%1'").arg(actualQuery1.toString()));

    QUrlQuery actualQuery2 = features.at(1).urlQuery();
    DOTEST2(actualQuery2.queryItemValue("request") == "GetFeature", QString("Query is incorrect '%1'").arg(actualQuery2.toString()));
    DOTEST2(actualQuery2.queryItemValue("typeName") == "ogi:quad100_centroids", QString("Query is incorrect '%1'").arg(actualQuery2.toString()));
}

void WfsParserTest::shouldParseQuad100FeatureCollection()
{
    WfsFeature featureResource( {"http://ogi.state.ok.us/geoserver/wfs?VERSION=1.1.0&REQUEST=GetFeature&typeName=ogi%3Aquad100"} );
    FeatureCoverage *fcoverage = new FeatureCoverage(featureResource);

    WfsResponse featureDescriptionResponse(Utils::openFile("testcases/testfiles/quad100.xsd"));
    WfsFeatureDescriptionParser parser( &featureDescriptionResponse);

    WfsParsingContext context;
    parser.parseSchemaDescription(fcoverage, context);
    ITable table = fcoverage->attributeTable();

    quint32 expected = 12;
    quint32 actual = table->columnCount();
    DOCOMPARE(actual, expected, "Compare parsed amount of metadata columns.");

    try {
        WfsResponse featureResponse(Utils::openFile("testcases/testfiles/featurecollection_quad100.xml"));
        WfsFeatureParser featureParser( &featureResponse, fcoverage);
        featureParser.context(context);
        featureParser.parseFeatureMembers();
        DOCOMPARE(fcoverage->featureCount(), (unsigned int)5, "Should parse 5 quad100 features.");
    } catch(std::exception &e) {
        std::cout << "Could not parse feature collection: " << e.what() << std::endl;
    }

    QDir baseDataPath = TestSuite::instance()->outputDataPath();
    QUrl outputFeature = QUrl::fromLocalFile(baseDataPath.absolutePath() + "/feature.shp");
    fcoverage->connectTo(outputFeature.toString(), "ESRI Shapefile", "gdal", IlwisObject::cmOUTPUT);
    //fcoverage->store(); // fails!
    delete fcoverage;
}

void WfsParserTest::shouldParseGreenlandElevationContoursFeatureCollection()
{
    WfsFeature featureResource( {"http://nsidc.org/cgi-bin/atlas_north?VERSION=1.1.0&REQUEST=GetFeature&typeName=greenland_elevation_contours"} );
    FeatureCoverage *fcoverage = new FeatureCoverage(featureResource);

    WfsResponse featureDescriptionResponse(Utils::openFile("testcases/testfiles/greenlevel_contours.xsd"));
    WfsFeatureDescriptionParser parser( &featureDescriptionResponse);

    WfsParsingContext context;
    parser.parseSchemaDescription(fcoverage, context);
    ITable table = fcoverage->attributeTable();

    quint32 expected = 3;
    quint32 actual = table->columnCount();
    DOCOMPARE(actual, expected, "Compare parsed amount of metadata columns.");

    try {
        WfsResponse featureResponse(Utils::openFile("testcases/testfiles/featurecollection_greenlevel_contours.xml"));
        WfsFeatureParser featureParser( &featureResponse, fcoverage);
        featureParser.context(context);
        featureParser.parseFeatureMembers();
        DOCOMPARE(fcoverage->featureCount(), (unsigned int)2, "Should parse 2 greenlevel_contours features.");
    } catch(std::exception &e) {
        std::cout << "Could not parse feature collection: " << e.what() << std::endl;
    }
    delete fcoverage;
}


void WfsParserTest::shouldParseSioseINSPIRE_lu_es_14_FeatureCollection()
{
    WfsFeature featureResource( {"http://www2.ign.es/sioseinspire?VERSION=1.1.0&REQUEST=GetFeature&typeName=sioseinspire:lu_es_14"} );
    FeatureCoverage *fcoverage = new FeatureCoverage(featureResource);

    WfsResponse featureDescriptionResponse(Utils::openFile("testcases/testfiles/sioseinspire_lu_es_14.xsd"));
    WfsFeatureDescriptionParser parser( &featureDescriptionResponse);

    WfsParsingContext context;
    parser.parseSchemaDescription(fcoverage, context);
    ITable table = fcoverage->attributeTable();

    quint32 expected = 8;
    quint32 actual = table->columnCount();
    DOCOMPARE(actual, expected, "Compare parsed amount of metadata columns.");

    try {
        WfsResponse featureResponse(Utils::openFile("testcases/testfiles/featurecollection_sioseinspire_lu_es_14.xml"));
        WfsFeatureParser featureParser( &featureResponse, fcoverage);
        featureParser.context(context);
        featureParser.parseFeatureMembers();
        DOCOMPARE(fcoverage->featureCount(), (unsigned int)5, "Should parse 5 greenlevel_contours features.");
    } catch(std::exception &e) {
        std::cout << "Could not parse feature collection: " << e.what() << std::endl;
    }
    delete fcoverage;
}




