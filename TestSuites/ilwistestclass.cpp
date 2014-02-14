#include "ilwistestclass.h"

IlwisTestClass::IlwisTestClass(const QString &name, const QString& module, QObject *parent) : QObject(parent), _name(name), _module(module)
{
}

QString IlwisTestClass::name() const
{
    return _name;
}

QString IlwisTestClass::module() const
{
    return _module;
}
