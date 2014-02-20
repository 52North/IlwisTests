#include <QtTest>
#include "kernel.h"
#include "ilwistestclass.h"
#include "testsuite.h"
//#include "core/util/locationtest.h"

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

IlwisTestCase *TestSuite::registerTest(IlwisTestCase *test)
{
    if ( _testclasses.find(test->name()) == _testclasses.end()){
          _testclasses[test->name()] = test;
    }
    return test;
}

void TestSuite::run(const QStringList &modules, const QString& inputData, const QString& outputData)
{
    Ilwis::initIlwis();
    _inputDatapath = inputData;
    _outputDataPath = outputData == "" ? outputData : inputData;

    QStringList testcases;
    if ( modules.size() == 1 && modules[0] == "all"){
        for(auto testclass : _testclasses) {
            testcases.push_back(static_cast<IlwisTestCase *>(testclass.second)->module());
        }
    }else
        testcases = modules;

    testcases.removeDuplicates();


    for(auto testcase : _testclasses) {
        IlwisTestCase *testclass = static_cast<IlwisTestCase *>(_testclasses[testcase.first]);
        for(const QString& test : testcases) {
            if ( test == testclass->module()) {
                QString outfile = _outputpath + "/" + testclass->module() + ".testlog";
                QStringList testCmd;
                testCmd<<" "<<"-o"<< outfile;
                QTest::qExec(testclass,testCmd);
            }
        }
    }
}

TestSuite *TestSuite::instance()
{
    if ( _instance == 0)
        _instance = new TestSuite();
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
