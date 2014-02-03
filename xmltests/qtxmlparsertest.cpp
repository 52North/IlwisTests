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

    XmlStreamParser parser( &reader);
    parser.addNamespaceMapping("a", "http://test.ns/a");
    parser.addNamespaceMapping("", "http://test.ns/b"); // default ns

    bool atTestNode = parser.startParsing("test");
    if (!atTestNode && parser.reader()->hasError()) {
        qDebug() << parser.reader()->errorString();
    }
    QVERIFY2(atTestNode, "Starts not at 'test' node.");
}

void QtXmlParserTest::testParsingFeatureTypesViaQuery()
{

//    QMap<QString,QString> namespaces;
//    namespaces["wfs"] = "http://www.opengis.net/wfs";
//    namespaces["ows"] = "http://www.opengis.net/ows";
//    QString xPath(createXPathNamespaceDeclarations(namespaces));
//    xPath.append("doc($xml)/wfs:WFS_Capabilities/wfs:FeatureTypeList/wfs:FeatureType");

    QFile *file = new QFile("extensions/testfiles/wfs_capabilities.xml");
    file->open(QIODevice::ReadOnly);

    XPathParser parser(file);
    parser.addNamespaceMapping("wfs", "http://www.opengis.net/wfs");
    parser.addNamespaceMapping("ows", "http://www.opengis.net/ows"); // default ns

    QXmlResultItems results;
    QString xpath("/wfs:WFS_Capabilities/wfs:FeatureTypeList/wfs:FeatureType");
    QXmlQuery *query = parser.parseAbsolute(xpath);

    if (query->isValid()) {
        query->evaluateTo( &results);
        QXmlItem featureType(results.next());
        while (!featureType.isNull()) {
            debugFeatureType(featureType, query);
            featureType = results.next();
        }
        if (results.hasError()) {
            QFAIL("Evaluating failed.");
        }
    } else {
        QFAIL(QString("Invalid xpath query: %1").arg(xpath).toLatin1().constData());
    }
}

void QtXmlParserTest::debugFeatureType(QXmlItem &featureType, QXmlQuery *ctx) {
    ctx->setFocus(featureType);
    QMap<QString,QString> namespaces;
    namespaces["wfs"] = "http://www.opengis.net/wfs";
    namespaces["ows"] = "http://www.opengis.net/ows";

    QString xPath(createXPathNamespaceDeclarations(namespaces));

    xPath.append("./wfs:Name/string()");
    ctx->setQuery(xPath);
    QString output;
    ctx->evaluateTo(&output);
    qDebug() << output;
//    qDebug() << ctx.setQuery("./wfs:Title/text()");
//    qDebug() << ctx.setQuery("./wfs:Abstract/text()");
//    qDebug() << ctx.setQuery("./wfs:DefaultSRS/text()");
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
