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
    QString folder = TestSuite::instance()->inputDataPath();

    if ( !QFileInfo(folder).exists())
        throw SkipTest("no data path defined");
    _baseDataPath = QDir(folder);
    QString ss = _baseDataPath.absolutePath();
    folder  = TestSuite::instance()->outputDataPath();

    if ( !QFileInfo(folder).exists())
        throw SkipTest("no data output path defined");
     _baseDataOutputPath = QDir(folder);

    Ilwis::ICatalog cat(QUrl::fromLocalFile(_baseDataPath.absolutePath()).toString());
    Ilwis::context()->setWorkingCatalog(cat);
}

QString IlwisTestCase::makeInputPath(const QString& filename){
    QString path = _baseDataPath.absolutePath();
#ifdef Q_OS_WIN
    path = "/" + path;
#endif
    if ( filename != "")
        return "file://" + path +"/" + filename;
    return "file://" + path;
}

QString IlwisTestCase::makeOutputPath(const QString& filename){
    QString path = _baseDataOutputPath.absolutePath();
#ifdef Q_OS_WIN
    path = "/" + path;
#endif
    if ( filename != "")
        return "file://" + path +"/" + filename;
    return "file://" + path;
}
