#include <QUrl>
#include <QtTest>
#include <QString>
#include <QObject>

#include "kernel.h"
#include "ilwisdata.h"
#include "domain.h"
#include "coverage.h"
#include "polygon.h"
#include "columndefinition.h"
#include "geometry.h"
#include "attributerecord.h"
#include "feature.h"
#include "featurecoverage.h"
#include "wfsconnector.h"
#include "wfs.h"
#include "wfsresponse.h"
#include "tst_wfsconnectortest.h"

#define WFS_TEST_SERVER_1 "http://ogi.state.ok.us/geoserver/wfs?VERSION=1.1.0&REQUEST=GetCapabilities&SERVICE=WFS"
#define WFS_TEST_SERVER_2 "http://nsidc.org/cgi-bin/atlas_north?service=WFS&version=1.1.0&request=GetCapabilities"
#define WFS_TEST_SERVER_3 "http://www2.ign.es/sioseinspire?SERVICE=WFS&REQUEST=GetCapabilities"

using namespace Ilwis;
using namespace Wfs;

WfsConnectorTest::WfsConnectorTest()
{
    QUrl wfsUrl(WFS_TEST_SERVER_1);
    _wfs = new WebFeatureService(wfsUrl);
}


void WfsConnectorTest::initTestCase() {
}


void WfsConnectorTest::getCapabilities() {
    /*
    QUrl url(WFS_TEST_SERVER_1);
    QNetworkReply *reply =_nam->get(QNetworkRequest(url));

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec();

    QString response(reply->readAll());
    qDebug() << response;
    */

    _wfs->getCapabilities();
}

void WfsConnectorTest::getFeature() {

}



void WfsConnectorTest::cleanupTestCase() {
    delete _wfs;
}

#include "moc_tst_wfsconnectortest.cpp"
