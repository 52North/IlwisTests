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

QtXmlParserTest::QtXmlParserTest(): IlwisTestCase("XmlParsingTest","XmlParsingTest")
{

}

void QtXmlParserTest::initTestCase()
{
}

void QtXmlParserTest::shouldStartParsingAtRootNode()
{
    XmlStreamParser parser(Utils::openFile("testcases/testfiles/test.xml"));
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
    XmlStreamParser parser(Utils::openFile("testcases/testfiles/test_without_xml_header.xml"));
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
    XmlStreamParser parser(Utils::openFile("testcases/testfiles/quad100.xsd"));
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
    XmlStreamParser parser(Utils::openFile("testcases/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    QString pathToReach = "'//test/a:test/a:c'";
    DOTEST2(parser.startParsing("test"), "Starts not at 'test' node.");
    DOTEST2(parser.moveToNext("a:test"), "Parser didn't reach a:test node. Wanted to reach " + pathToReach);
    DOTEST2(parser.moveToNext("a:c"), "Could not find element a:c. Wanted to reach " + pathToReach);
}

void QtXmlParserTest::shouldFindElements()
{
    XmlStreamParser parser(Utils::openFile("testcases/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    DOTEST2(parser.startParsing("test"), "Starts not at 'test' node.");
    DOTEST2(parser.findNextOf( { "a:b" } ), "Could not find element '//test/a:b'");
}

void QtXmlParserTest::shouldMoveToElementOnSameLevel()
{
    XmlStreamParser parser(Utils::openFile("testcases/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    DOTEST2(parser.startParsing("test"), "Starts not at 'test' node.");
    DOTEST2(parser.moveToNext("node"), "Could not find element '//test/node'");
}

void QtXmlParserTest::shouldMoveToEndOfElement()
{
    XmlStreamParser parser(Utils::openFile("testcases/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    QString pathToReach = "'//test/a:test/a:b/a:c'";
    DOTEST2(parser.startParsing("test"), "Starts not at 'test' node.");
    DOTEST2(parser.findNextOf( {"a:c"} ), "Could not find element " + pathToReach);
    DOTEST2(parser.moveToEndOf("a:test"), "Could not find end element of '//test/a:test'");
    DOTEST2(parser.readNextStartElement(), "Missing further start element.");
    DOTEST2(parser.name() == "node", "Expected node name 'node' as current element.");
}

void QtXmlParserTest::shouldMoveToSecondCNode()
{
    XmlStreamParser parser(Utils::openFile("testcases/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    QString pathToReach = "'//test/a:test/a:c[1]/string()'";
    DOTEST2(parser.startParsing("test"), "Parser didn't reach test node. Want to reach " + pathToReach);
    DOTEST2(parser.moveToNext("a:test"), "Parser didn't reach a:test node. Want to reach " + pathToReach);
    DOTEST2(parser.moveToNext("a:c"), "Parser didn't reach a:c[0] node. Want to reach " + pathToReach);
    if (parser.moveToNext("a:c")) {
        QString errorMsg("Read wrong node: ");
        errorMsg = errorMsg.append(parser.reader()->name().toString());
        QString text = parser.readElementText();
        DOTEST2(text == "another text", errorMsg.toLatin1().constData());
    } else {
        QString msg = "Parser didn't reach a:c[1] node. Want to reach " + pathToReach;
        QFAIL(msg.toLatin1().constData());
    }
}

void QtXmlParserTest::shouldParseCorrectAttributeValue()
{
    XmlStreamParser parser(Utils::openFile("testcases/testfiles/test.xml"));
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns
    parser.addNamespaceMapping("a", "http://test.ns/a");

    QString pathToReach = "'//test/node/@foo'";
    DOTEST2(parser.startParsing("test"), "Starts not at 'test' node. Want to reach " + pathToReach);
    if (parser.moveToNext("node")) {
        QXmlStreamAttributes attributes = parser.attributes();
        DOTEST2(attributes.value("foo") == "bar", "Incorrect attribute value.");
    } else {
        QString msg = "Parser didn't reach 'node' node. Want to reach " + pathToReach;
        QFAIL(msg.toLatin1().constData());
    }
}

void QtXmlParserTest::cleanupTestCase()
{

}


#include "moc_qtxmlparsertest.cpp"
