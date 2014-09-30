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
#include "connectorinterface.h"
#include "ilwisobjectconnector.h"
#include "catalogexplorer.h"
#include "catalogconnector.h"

#include "wfscatalogexplorer.h"
#include "wfscatalogexplorertest.h"
#include "wfstestconstants.h"

#include "testutils.h"
#include "testsuite.h"

using namespace Ilwis;
using namespace Wfs;

REGISTER_TEST(WfsCatalogExplorerTest);

WfsCatalogExplorerTest::WfsCatalogExplorerTest():
    IlwisTestCase("WfsCatalogExplorerTest", "WfsConnectorTest")
{
}

void WfsCatalogExplorerTest::initTestCase() {
    ICatalog cat;
    if (!cat.prepare(WFS_TEST_SERVER_1))
        throw SkipTest(QString("Could not prepare WFS '%1'").arg(WFS_TEST_SERVER_1).toStdString());
    context()->setWorkingCatalog(cat);
}

void WfsCatalogExplorerTest::sandbox() {
    QString url("http://localhost/wfs?ACCEPTVERSIONS=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS");
    QUrl capabilitiesUrl(url);
    Resource wfsCatalog(capabilitiesUrl, itCATALOG);
    qDebug() << wfsCatalog.container();
}

void WfsCatalogExplorerTest::canUseValidWfsUrlWithCapitalParameters() {
    QString url("http://localhost/wfs?ACCEPTVERSIONS=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS");
    QUrl capabilitiesUrl(url);
    Resource wfsCatalog(capabilitiesUrl, itCATALOG);
    WfsCatalogExplorer connector(wfsCatalog);
    DOTEST2(connector.canUse(wfsCatalog), QString("Explorer indicates it can't use valid WFS: %1").arg(url));
}

void WfsCatalogExplorerTest::canUseValidWfsUrlWithMixedCapitalParameters() {
    QString url("http://localhost/wfs?acceptVersions=1.1.0&request=GetCapabilities&service=WFS");
    Resource wfs1(url, itCATALOG);
    WfsCatalogExplorer connector(wfs1);
    DOTEST2(connector.canUse(wfs1), QString("Explorer indicates it can't use valid WFS: %1").arg(url));
}

