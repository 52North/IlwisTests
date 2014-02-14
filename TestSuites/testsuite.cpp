#include <QtTest>
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

IlwisTestClass *TestSuite::registerTest(IlwisTestClass *test)
{
    if ( _testclasses.find(test->name()) == _testclasses.end()){
          _testclasses[test->name()] = test;
    }
    return test;
}

void TestSuite::run(const QStringList &modules)
{
    QStringList testcases;
    if ( modules.size() == 1 && modules[0] == "all"){
        for(auto testclass : _testclasses) {
            testcases.push_back(static_cast<IlwisTestClass *>(testclass.second)->module());
        }
    }else
        testcases = modules;

    testcases.removeDuplicates();


    for(auto testcase : _testclasses) {
        IlwisTestClass *testclass = static_cast<IlwisTestClass *>(_testclasses[testcase.first]);
        for(const QString& test : testcases) {
            if ( test == testclass->module()) {
                QString outfile = _outputpath + "/" + testclass->module() + ".testlog";
                QStringList testCmd;
                testCmd<<" "<<"-o"<< outfile;
                int ret = QTest::qExec(testclass,testCmd);
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
