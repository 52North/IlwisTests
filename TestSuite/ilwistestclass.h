#ifndef ILWISTESTCLASS_H
#define ILWISTESTCLASS_H

#include <QObject>
#include <QTest>
#include <QDir>
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

protected:
    QDir _baseDataPath;
    QDir _baseDataOutputPath;
    QString makeInputPath(const QString &filename);
    QString makeOutputPath(const QString &filename);
private:
    QString _name;
    QString _module;

    
signals:
    
public slots:
    
private slots:
    void initTestCase();
};

#endif // ILWISTESTCLASS_H
