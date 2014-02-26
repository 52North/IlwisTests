#ifndef QTXMLPARSERTEST_H
#define QTXMLPARSERTEST_H

class QFile;
class QObject;
class QString;
class QXmlItem;
class QXmlQuery;

#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

class QtXmlParserTest: public IlwisTestCase
{
    Q_OBJECT

public:
    QtXmlParserTest();

private:
    NEW_TEST(QtXmlParserTest);

private Q_SLOTS:
    void initTestCase();
    void shouldStartParsingAtRootNode();
    void shouldStartParsingAtRootNodeWhenNoXmlHeaderPresent();
    void shouldStartParsingXmlSchemaAtRootNode();
    void shouldMoveToElementOnNextLevel();
    void shouldFindElements();
    void shouldMoveToElementOnSameLevel();
    void shouldMoveToSecondCNode();
    void shouldParseCorrectAttributeValue();
    void cleanupTestCase();

};

#endif // QTXMLPARSERTEST_H
