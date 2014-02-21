#include <QUrl>
#include <QtTest>
#include <QString>
#include <QObject>

#include "kernel.h"
#include "catalog.h"
#include "symboltable.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"

#include "ilwisdata.h"

#include "tst_resourcetest.h"

using namespace Ilwis;


ResourceTest::ResourceTest()
{

}

void ResourceTest::initTestCase()
{

}

void ResourceTest::shouldParseLastUrlPartAsName()
{
    QUrl url1("http://localhost/context");
    Resource resource1(url1, itFEATURE);
    QVERIFY2(resource1.name() == "context", QString("Resource name has been parsed incorrectly (was: '%1')").arg(resource1.name()).toLatin1().constData());

    QUrl url2("http://localhost/context/");
    Resource resource2(url2, itFEATURE);
    QVERIFY2(resource2.name() == "context", QString("Resource name has been parsed incorrectly (was: '%1')").arg(resource2.name()).toLatin1().constData());
}

void ResourceTest::shouldIndicateHavingQueryString()
{
    QUrl urlWithQuery("http://localhost/context?query=true&list=first,second&special=#&withSpace=one two");
    Resource resourceWithQuery(urlWithQuery, itUNKNOWN);
    QVERIFY2(resourceWithQuery.hasUrlQuery(), "Resource did not store URL query!");
}

void ResourceTest::shouldIndicateNotHavingQueryString()
{
    QUrl urlWithoutQuery1("http://localhost/context");
    Resource resourceWithQuery1(urlWithoutQuery1, itUNKNOWN);
    QVERIFY2(!resourceWithQuery1.hasUrlQuery(), "Resource has no query string but indicates it has!");

    QUrl urlWithoutQuery2("http://localhost/context?");
    Resource resourceWithQuery2(urlWithoutQuery2, itUNKNOWN);
    QVERIFY2(!resourceWithQuery2.hasUrlQuery(), "Resource has no query string but indicates it has!");
}

void ResourceTest::cleanupTestCase()
{

}

#include "moc_tst_resourcetest.cpp"

