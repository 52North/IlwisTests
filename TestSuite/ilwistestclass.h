#ifndef ILWISTESTCLASS_H
#define ILWISTESTCLASS_H

#include <QObject>
#include <QTest>
#include "testsuite_global.h"
#include "testmacros.h"

class TESTSUITESHARED_EXPORT IlwisTestCase : public QObject
{
    Q_OBJECT
public:
    explicit IlwisTestCase(const QString& name, const QString& module, QObject *parent = 0);
    QString name() const;
    QString qualifiedName() const;
    QString module() const;
private:
    QString _name;
    QString _module;
    
signals:
    
public slots:
    
};

#endif // ILWISTESTCLASS_H
