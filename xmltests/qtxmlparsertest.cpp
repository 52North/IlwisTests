#include <QUrl>
#include <QtTest>
#include <QString>
#include <QObject>
#include <QXmlItem>
#include <QXmlQuery>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QtXmlPatterns/QXmlResultItems>
#include <QtXmlPatterns/QXmlQuery>
#include <QMapIterator>

#include "qtxmlparsertest.h"
#include "wfsfeature.h"
#include "xmlstreamparser.h"
#include "xpathparser.h"
#include "xmlstreamparser.h"

using namespace Ilwis;
using namespace Wfs;

QtXmlParserTest::QtXmlParserTest()
{

}

void QtXmlParserTest::initTestCase()
{
}

void QtXmlParserTest::shouldStartParsingAtRootNode()
{
    QFile *file = new QFile("extensions/testfiles/test.xml");
    file->open(QIODevice::ReadOnly);

    QXmlStreamReader reader;
    reader.setDevice(file);

    XmlStreamParser parser( &reader);
    parser.addNamespaceMapping("a", "http://test.ns/a");
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns

    bool atTestNode = parser.startParsing("test");
    if (!atTestNode) {
        qDebug() << parser.reader()->name() << " startNode: " << parser.reader()->isStartElement();
    }
    QVERIFY2(atTestNode, "Starts not at 'test' node.");
    file->close();
}

void QtXmlParserTest::shouldMoveToElementOnNextLevel()
{
    QFile *file = new QFile("extensions/testfiles/test.xml");
    file->open(QIODevice::ReadOnly);

    QXmlStreamReader reader;
    reader.setDevice(file);

    XmlStreamParser parser( &reader);
    parser.addNamespaceMapping("a", "http://test.ns/a");
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns

    if (parser.startParsing("test")) {
        if (parser.nextLevelMoveTo("a:test")) {
            QVERIFY2(parser.nextLevelMoveTo("a:c"), "Could not find element '//test/a:test/a:c'");
        }
    } else {
        QFAIL("Starts not at 'test' node.");
    }
}

void QtXmlParserTest::shouldMoveToElementOnSameLevel()
{
    QFile *file = new QFile("extensions/testfiles/test.xml");
    file->open(QIODevice::ReadOnly);

    QXmlStreamReader reader;
    reader.setDevice(file);

    XmlStreamParser parser( &reader);
    parser.addNamespaceMapping("a", "http://test.ns/a");
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns

    if (parser.startParsing("test")) {
        if (parser.nextLevelMoveTo("a:test")) {
            QVERIFY2(parser.currentLevelMoveTo("node"), "Could not find element '//test/node'");
        }
    } else {
        QFAIL("Starts not at 'test' node.");
    }
}

void QtXmlParserTest::shouldParseCorrectAttributeValue()
{
    QFile *file = new QFile("extensions/testfiles/test.xml");
    file->open(QIODevice::ReadOnly);

    QXmlStreamReader reader;
    reader.setDevice(file);

    XmlStreamParser parser( &reader);
    parser.addNamespaceMapping("a", "http://test.ns/a");
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns

    if (parser.startParsing("test")) {
        if (parser.nextLevelMoveTo("a:test")) {
            if (parser.currentLevelMoveTo("node")) {
                QXmlStreamAttributes attributes = parser.attributes();
                QVERIFY2(attributes.value("foo") == "bar", "Incorrect attribute value.");
            }
        }
    } else {
        QFAIL("Starts not at 'test' node.");
    }
}

void QtXmlParserTest::cleanupTestCase()
{

}

#include "moc_qtxmlparsertest.cpp"
