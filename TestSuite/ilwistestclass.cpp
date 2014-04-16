#include "ilwistestclass.h"

IlwisTestCase::IlwisTestCase(const QString &name, const QString& module, QObject *parent) :
    QObject(parent), _name(name), _module(module){
}

QString IlwisTestCase::name() const
{
    return _name;
}

QString IlwisTestCase::qualifiedName() const
{
    return _module + "::" + _name;
}

QString IlwisTestCase::module() const
{
    return _module;
}
