#include <QtTest>
#include <QDirIterator>
#include "kernel.h"
#include "errorobject.h"
#include "ilwistestclass.h"
#include "testsuite.h"
//#include "core/util/locationtest.h"
#include <iostream>

TestSuite *TestSuite::_instance = 0;

TestSuite::TestSuite()
{
    //registerTest(new PixelTests());

    QString path = QCoreApplication::applicationDirPath();
    path += "/log";
    QDir dir(path);
    if ( !dir.exists()){
        dir.mkdir(path);
    }
    path += "/testlog";
    dir.setPath(path);
    if ( !dir.exists()){
        dir.mkdir(path);
    }
    _outputpath = path;
}

void TestSuite::addModules() {

    QString path = QCoreApplication::applicationDirPath() + "/testcases/";
    QDir folder(path);
    QDirIterator dirWalker(folder, QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);
    while(dirWalker.hasNext()) {
        dirWalker.next();
        QFileInfo file(dirWalker.filePath());
        if ( file.suffix() == "so" || file.suffix().toLower() == "dll"){
            QLibrary lib;
            lib.setFileName(file.absoluteFilePath());
            bool ok =lib.load();
            if (!ok)
             qDebug() << lib.errorString();
        }

    }
}
IlwisTestCase *TestSuite::registerTest(IlwisTestCase *test)
{
    if ( _testclasses.find(test->name()) == _testclasses.end()){
          _testclasses[test->name()] = test;
    }
    return test;
}

void TestSuite::run(const QStringList &modules, const QString& inputData, const QString& outputData)
{
    try {
    Ilwis::initIlwis(Ilwis::rmTEST);
    _inputDatapath = inputData;
    _outputDataPath = outputData != "" ? outputData : inputData;

    QStringList testcases;
    if ( modules.size() == 1 && modules[0] == "all"){
        for(auto testclass : _testclasses) {
            testcases.push_back(static_cast<IlwisTestCase *>(testclass.second)->module());
        }
    }else
        testcases = modules;

    testcases.removeDuplicates();

    int failcount = 0;
    int casefailcount = 0;
    int runcount = 0;
    int errcount = 0;
    int skipcount = 0;
    int fail = 0;
    for(auto testcase : _testclasses) {
        IlwisTestCase *testclass = static_cast<IlwisTestCase *>(_testclasses[testcase.first]);
        for(const QString& test : testcases) {

            if ( test == testclass->module() || test == testclass->qualifiedName()) {
                QString outfile = _outputpath + "/" + testclass->module() + ".testlog";
                QStringList testCmd;
                testCmd<<" "<<"-o"<< outfile;
                try{
                    fail = QTest::qExec(testclass,testCmd);
                }catch(SkipTest){
                    skipcount++;
                }catch(std::exception e){
                    errcount++;
                    std::cout << QString("ERROR: %1 threw a exception (%2) \n").arg(testclass->name(), e.what()).toStdString();
                }
                //statistic
                runcount++;
                if (fail > 0) failcount++;
                casefailcount += fail;
            }
        }
    }
    std::cout << QString("Total: ran %1 tests, %2 failed, %3 errors, %4 skipped, %5 test cases failed \n")
                 .arg(runcount).arg(failcount).arg(errcount).arg(skipcount).arg(casefailcount).toStdString();
    } catch(const Ilwis::ErrorObject& err){
        qDebug() << err.message();
    }
}

TestSuite *TestSuite::instance()
{
    if ( _instance == 0){
        _instance = new TestSuite();
        _instance->addModules();
    }
    return _instance;
}

QString TestSuite::inputDataPath() const
{

    return _inputDatapath;
}

QString TestSuite::outputDataPath() const
{
    return _outputDataPath;
}
