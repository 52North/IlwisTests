#ifndef TESTSUITE_H
#define TESTSUITE_H

class IlwisTestCase;

class TestSuite
{

public:
    TestSuite();
    IlwisTestCase *registerTest(IlwisTestCase * test);
    void run(const QStringList& cases, const QString &inputData, const QString &outputData);
    static TestSuite *instance();
    QString inputDataPath() const;
    QString outputDataPath() const;


private:
    std::map<QString, QObject *> _testclasses;
    QString _outputpath;
    static TestSuite *_instance;
    QString _inputDatapath;
    QString _outputDataPath;

};

#endif // TESTSUITE_H
