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

#include "testutils.h"
#include "qtxmlparsertest.h"
#include "wfsfeature.h"
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
    XmlStreamParser parser(Utils::openFile("extensions/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    bool atTestNode = parser.startParsing("test");
    if (!atTestNode) {
        qDebug() << "at node: " << parser.reader()->name() << " startNode: " << parser.reader()->isStartElement();
        qDebug() << "error: " << parser.reader()->error() << ": " << parser.reader()->errorString();
    }
    QVERIFY2(atTestNode, "Starts not at 'test' node.");
}

void QtXmlParserTest::shouldStartParsingAtRootNodeWhenNoXmlHeaderPresent()
{
    XmlStreamParser parser(Utils::openFile("extensions/testfiles/test_without_xml_header.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    bool atTestNode = parser.startParsing("test");
    if (!atTestNode) {
        qDebug() << "at node: " << parser.reader()->name() << " startNode: " << parser.reader()->isStartElement();
        qDebug() << "error: " << parser.reader()->error() << ": " << parser.reader()->errorString();
    }
    QVERIFY2(atTestNode, "Starts not at 'test' node.");
}

void QtXmlParserTest::shouldStartParsingXmlSchemaAtRootNode()
{
    XmlStreamParser parser(Utils::openFile("extensions/testfiles/quad100.xsd"));
    parser.addNamespaceMapping("xsd", "http://www.w3.org/2001/XMLSchema");

    bool atSchemaNode = parser.startParsing("xsd:schema");
    if (!atSchemaNode) {
        qDebug() << "at node: " << parser.reader()->name() << " startNode: " << parser.reader()->isStartElement();
        qDebug() << "error: " << parser.reader()->error() << ": " << parser.reader()->errorString();
    }
    QVERIFY2(atSchemaNode, "Starts not at 'schema' node.");
}

void QtXmlParserTest::shouldMoveToElementOnNextLevel()
{
    XmlStreamParser parser(Utils::openFile("extensions/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

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
    XmlStreamParser parser(Utils::openFile("extensions/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

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
    XmlStreamParser parser(Utils::openFile("extensions/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

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
