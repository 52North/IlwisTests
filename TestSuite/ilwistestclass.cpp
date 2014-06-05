#include "kernel.h"
#include "catalog.h"
#include "testsuite.h"
#include "ilwiscontext.h"
#include "ilwistestclass.h"
#include "oshelper.h"

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

void IlwisTestCase::initTestCase()
{
    QString path = TestSuite::instance()->inputDataPath();

    QDir folder( Ilwis::OSHelper::operatingSystem() == "windows" ? path : "/" + path);
    if ( !folder.exists())
        throw SkipTest("no data path defined");
    _baseDataPath = QDir(folder);
    QString ss = _baseDataPath.absolutePath();
    path  = TestSuite::instance()->outputDataPath();

    folder = QDir( Ilwis::OSHelper::operatingSystem() == "windows" ? path : "/" + path);
    if ( !folder.exists())
        throw SkipTest("no data output path defined");
     _baseDataOutputPath = path;

    Ilwis::ICatalog cat(QUrl::fromLocalFile(_baseDataPath.absolutePath()).toString());
    Ilwis::context()->setWorkingCatalog(cat);
}

