#ifndef QTXMLPARSERTEST_H
#define QTXMLPARSERTEST_H

class QObject;
class QString;
class QXmlItem;
class QXmlQuery;

class QtXmlParserTest: public QObject
{
    Q_OBJECT

public:
    QtXmlParserTest();

private Q_SLOTS:
    void initTestCase();
    void testParsingFeatureTypesViaQuery();
    void cleanupTestCase();

private:
    void testParsingFeatureTypesViaStreamReader();
    QString createXPathNamespaceDeclarations(QMap<QString,QString> &mappings);
    QString readTestFile(QString path);


    void debugFeatureType(QXmlItem &featureType, QXmlQuery *ctx);

};

#endif // QTXMLPARSERTEST_H
