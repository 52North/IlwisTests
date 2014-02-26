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
#include "catalogconnector.h"

#include "wfsschemainfo.h"
#include "wfscatalogconnector.h"
#include "wfscatalogconnectortest.h"

#include "testutils.h"
#include "testsuite.h"

#define WFS_TEST_SERVER_1 "http://ogi.state.ok.us/geoserver/wfs?acceptVersions=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS"

using namespace Ilwis;
using namespace Wfs;

REGISTER_TEST(WfsCatalogConnectorTest);

WfsCatalogConnectorTest::WfsCatalogConnectorTest(): IlwisTestCase("WfsCatalogConnectorTest", "WfsConnectorTest")
{
}

void WfsCatalogConnectorTest::initTestCase() {

    // TODO: test against 'wfs-test://extensions/testfiles/wfs_capabilities.xml'?

    QString url(WFS_TEST_SERVER_1);

    QUrl s(url);
    Catalog cat;
    if (!cat.prepare(s))
        throw SkipTest(QString("could not prepare WFS '%1'").arg(url).toStdString());
    context()->setWorkingCatalog(cat);
}

void WfsCatalogConnectorTest::sandbox() {
    QString url("http://localhost/wfs?ACCEPTVERSIONS=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS");
    QUrl capabilitiesUrl(url);
    Resource wfsCatalog(capabilitiesUrl, itCATALOG);
    qDebug() << wfsCatalog.container();
}

void WfsCatalogConnectorTest::canUseValidWfsUrlWithCapitalParameters() {
    QString url("http://localhost/wfs?ACCEPTVERSIONS=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS");
    QUrl capabilitiesUrl(url);
    Resource wfsCatalog(capabilitiesUrl, itCATALOG);
    WfsCatalogConnector connector(wfsCatalog);
    DOTEST2(connector.canUse(wfsCatalog), QString("Connector indicates it can't use valid WFS: %1").arg(url));
}

void WfsCatalogConnectorTest::canUseValidWfsUrlWithMixedCapitalParameters() {
    QString url("http://localhost/wfs?acceptVersions=1.1.0&request=GetCapabilities&service=WFS");
    Resource wfs1(url, itCATALOG);
    WfsCatalogConnector connector(wfs1);
    DOTEST2(connector.canUse(wfs1), QString("Connector indicates it can't use valid WFS: %1").arg(url));
}

