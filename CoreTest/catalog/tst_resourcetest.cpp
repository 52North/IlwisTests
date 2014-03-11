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
    DOTEST2(resource1.name() == "context", QString("Resource name has not been parsed correctly (was: '%1')").arg(resource1.name()));

    QUrl url2("http://localhost/context/");
    Resource resource2(url2, itFEATURE);
    DOTEST2(resource2.name() == "", QString("Resource name has not been parsed correctly (empty name"));
}

void ResourceTests::shouldIndicateHavingQueryString()
{
    QUrl urlWithQuery("http://localhost/context?query=true&list=first,second&special=#&withSpace=one two");
    Resource resourceWithQuery(urlWithQuery, itUNKNOWN);
    DOTEST2(resourceWithQuery.hasUrlQuery(), "Resource did not store URL query!");
}

void ResourceTests::shouldIndicateNotHavingQueryString()
{
    QUrl urlWithoutQuery1("http://localhost/context");
    Resource resourceWithQuery1(urlWithoutQuery1, itUNKNOWN);
    DOTEST2(!resourceWithQuery1.hasUrlQuery(), "Resource wrongly indicates it has a query string ");

    QUrl urlWithoutQuery2("http://localhost/context?");
    Resource resourceWithQuery2(urlWithoutQuery2, itUNKNOWN);
    DOTEST2(!resourceWithQuery2.hasUrlQuery(), "Resource wrongly indicates it has a query string ");
}

void ResourceTests::cleanupTestCase()
{

}
