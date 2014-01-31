#include <QUrl>
#include <QtTest>
#include <QString>
#include <QObject>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QtXmlPatterns/QXmlResultItems>
#include <QtXmlPatterns/QXmlQuery>
#include <QMapIterator>

#include "qtxmlparsertest.h"
#include "wfsfeature.h"
#include "xmlparser.h"

QtXmlParserTest::QtXmlParserTest()
{

}

void QtXmlParserTest::initTestCase()
{
}

void QtXmlParserTest::testParsingFeatureTypesViaStreamReader()
{

    QFile file("extensions/testfiles/test.xml");
    file.open(QIODevice::ReadOnly);

    QXmlStreamReader reader;
    reader.setDevice( &file);

    XmlParser parser( &reader);
    parser.addNamespaceMapping("wfs", "http://www.opengis.net/wfs");
    parser.addNamespaceMapping("ows", "http://www.opengis.net/ows");


    QVERIFY2(parser.startParsing("test"), "Starts not at 'test' node.");
}

void QtXmlParserTest::testParsingFeatureTypesViaQuery()
{
    QMap<QString,QString> namespaces;
    namespaces["wfs"] = "http://www.opengis.net/wfs";
    namespaces["ows"] = "http://www.opengis.net/ows";
    QString xPath(createXPathNamespaceDeclarations(namespaces));
    xPath.append("doc($xml)/wfs:WFS_Capabilities/wfs:FeatureTypeList/wfs:FeatureType");

    QFile file("extensions/testfiles/wfs_capabilities.xml");
    file.open(QIODevice::ReadOnly);

    QXmlQuery query;
    query.bindVariable("xml", &file);
    query.setQuery(xPath);
    QXmlResultItems result;

    if (query.isValid()) {
        query.evaluateTo( &result);
        QXmlItem item(result.next());
        while (!item.isNull()) {

            item = result.next();
            //debugItem(item);
        }
        if (result.hasError()) {
            QFAIL("Evaluating failed.");
        }
    } else {
        QFAIL(QString("Invalid xpath query: %1").arg(xPath).toLatin1().constData());
    }
}

void debugItem(QXmlItem &item) {
    if (item.isNode()) {
        QXmlItem nodeItem(item.toNodeModelIndex());

    } else {
        QVariant value = item.toAtomicValue();
        value.toChar();
    }
}

void QtXmlParserTest::cleanupTestCase()
{

}

QString QtXmlParserTest::createXPathNamespaceDeclarations(QMap<QString, QString> &mappings)
{
    QString declarationString;
    QMapIterator<QString,QString> iterator(mappings);
    while(iterator.hasNext()) {
        iterator.next();
        QString declaration = QString("declare namespace %1 = \"%2\"; \n ").arg(iterator.key(), iterator.value());
        declarationString.push_back(declaration);
    }
    return declarationString;
}

QString QtXmlParserTest::readTestFile(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    //QVERIFY2(file.open(QIODevice::ReadOnly), QString("Could not find test file '%1'!").arg(path).toLatin1().constData());

    QString content;
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        content.append(line);
    }
    file.close();
    return content;
}


#include "moc_qtxmlparsertest.cpp"
