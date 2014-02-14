#ifndef TESTSUITE_H
#define TESTSUITE_H

class TestSuite
{
public:
    TestSuite();
    IlwisTestClass *registerTest(IlwisTestClass * test);
    void run(const QStringList& cases);
    static TestSuite *instance();

private:
    std::map<QString, QObject *> _testclasses;
    QString _outputpath;
    static TestSuite *_instance;
};

#endif // TESTSUITE_H
