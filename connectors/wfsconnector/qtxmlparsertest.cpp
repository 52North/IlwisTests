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

#include "testsuite.h"

using namespace Ilwis;
using namespace Wfs;


REGISTER_TEST(QtXmlParserTest);

QtXmlParserTest::QtXmlParserTest(): IlwisTestCase("WfsConnectorTest", "XmlParsingTest")
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
    DOTEST2(atTestNode, "Starts not at 'test' node.");
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
    DOTEST2(atTestNode, "Starts not at 'test' node.");
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
    DOTEST2(atSchemaNode, "Starts not at 'schema' node.");
}

void QtXmlParserTest::shouldMoveToElementOnNextLevel()
{
    XmlStreamParser parser(Utils::openFile("extensions/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    if (parser.startParsing("test")) {
        if (parser.moveToNext("a:test")) {
            DOTEST2(parser.moveToNext("a:c"), "Could not find element '//test/a:test/a:c'");
        } else {
            QFAIL("Parser didn't reach a:test node (want to reach '//test/a:test/a:c').");
        }
    } else {
        QFAIL("Starts not at 'test' node.");
    }
}

void QtXmlParserTest::shouldFindElements()
{
    XmlStreamParser parser(Utils::openFile("extensions/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    if (parser.startParsing("test")) {
        DOTEST2(parser.findNextOf( {"a:b"} ), "Could not find element '//test/a:b'");
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
        DOTEST2(parser.moveToNext("node"), "Could not find element '//test/node'");
    } else {
        QFAIL("Starts not at 'test' node.");
    }
}

void QtXmlParserTest::shouldMoveToSecondCNode()
{
    XmlStreamParser parser(Utils::openFile("extensions/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    if (parser.startParsing("test")) {
        if (parser.moveToNext("a:test")) {
            if (parser.moveToNext("a:c")) {
                if (parser.moveToNext("a:c")) {
                    QString errorMsg("Read wrong node: ");
                    errorMsg = errorMsg.append(parser.reader()->name().toString());
                    QString text = parser.readElementText();
                    DOTEST2(text == "another text", errorMsg.toLatin1().constData());
                } else {
                    QFAIL("Parser didn't reach a:c[1] node (want to reach '//test/a:test/a:c[1]/string()')");
                }
            } else {
                QFAIL("Parser didn't reach a:c[0] node (want to reach '//test/a:test/a:c[1]/string()')");
            }
        } else {
            QFAIL("Parser didn't reach a:test node (want to reach '//test/a:test/a:c[1]/string()')");
        }
    } else {
        QFAIL("Parser didn't reach test node (want to reach '//test/a:test/a:c[1]/string()')");
    }
}

void QtXmlParserTest::shouldParseCorrectAttributeValue()
{
    XmlStreamParser parser(Utils::openFile("extensions/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    if (parser.startParsing("test")) {
        if (parser.moveToNext("node")) {
            QXmlStreamAttributes attributes = parser.attributes();
            DOTEST2(attributes.value("foo") == "bar", "Incorrect attribute value.");
        } else {
            QFAIL("Parser didn't reach node node (want to reach '//test/node/@foo')");
        }
    } else {
        QFAIL("Starts not at 'test' node (want to reach '//test/node/@foo')");
    }
}

void QtXmlParserTest::cleanupTestCase()
{

}


#include "moc_qtxmlparsertest.cpp"
