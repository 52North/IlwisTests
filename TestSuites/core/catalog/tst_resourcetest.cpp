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
#include "testsuite.h"

using namespace Ilwis;

REGISTER_TEST(ResourceTests);

ResourceTests::ResourceTests():
    IlwisTestCase("ResourceTests","CoreTests")
{

}

void ResourceTests::initTestCase()
{

}

void ResourceTests::shouldParseLastUrlPartAsName()
{
    QUrl url1("http://localhost/context");
    Resource resource1(url1, itFEATURE);
    DOTEST(resource1.name() == "context", QString("Resource name has been parsed incorrectly (was: '%1')").arg(resource1.name()));

    QUrl url2("http://localhost/context/");
    Resource resource2(url2, itFEATURE);
    // TODO: fails! this is a bug in Resource class
    DOTEST(resource2.name() == "context", QString("Resource name has been parsed incorrectly (was: '%1')").arg(resource2.name()));
}

void ResourceTests::shouldIndicateHavingQueryString()
{
    QUrl urlWithQuery("http://localhost/context?query=true&list=first,second&special=#&withSpace=one two");
    Resource resourceWithQuery(urlWithQuery, itUNKNOWN);
    DOTEST(resourceWithQuery.hasUrlQuery(), "Resource did not store URL query!");
}

void ResourceTests::shouldIndicateNotHavingQueryString()
{
    QUrl urlWithoutQuery1("http://localhost/context");
    Resource resourceWithQuery1(urlWithoutQuery1, itUNKNOWN);
    DOTEST(!resourceWithQuery1.hasUrlQuery(), "Resource has no query string but indicates it has!");

    QUrl urlWithoutQuery2("http://localhost/context?");
    Resource resourceWithQuery2(urlWithoutQuery2, itUNKNOWN);
    DOTEST(!resourceWithQuery2.hasUrlQuery(), "Resource has no query string but indicates it has!");
}

void ResourceTests::cleanupTestCase()
{

}
