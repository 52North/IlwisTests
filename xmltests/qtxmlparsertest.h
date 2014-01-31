#ifndef QTXMLPARSERTEST_H
#define QTXMLPARSERTEST_H

#include <QObject>
#include <QString>

class QtXmlParserTest: public QObject
{
    Q_OBJECT

public:
    QtXmlParserTest();

private Q_SLOTS:
    void initTestCase();
    void testParsingFeatureTypesViaStreamReader();
    void cleanupTestCase();

private:
    void testParsingFeatureTypesViaQuery();
    QString createXPathNamespaceDeclarations(QMap<QString,QString> &mappings);
    QString readTestFile(QString path);

};

#endif // QTXMLPARSERTEST_H
