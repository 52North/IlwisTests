#ifndef TST_RESOURCETEST_H
#define TST_RESOURCETEST_H

#include <QObject>

class ResourceTest :  public QObject
{
    Q_OBJECT

public:
    ResourceTest();

private Q_SLOTS:

    void initTestCase();
    void shouldParseLastUrlPartAsName();
    void shouldIndicateHavingQueryString();
    void shouldIndicateNotHavingQueryString();
    void cleanupTestCase();

private:

};

#endif // TST_RESOURCETEST_H
