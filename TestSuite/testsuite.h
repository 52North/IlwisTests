#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <exception>
#include <string>
#include "testsuite_global.h"

class TESTSUITESHARED_EXPORT SkipTest: public std::exception{
    private:
        std::string _what;
    public:
        SkipTest(std::string what):_what(what){}
        ~SkipTest() throw() {}
        const char *what() const throw(){return _what.c_str();}
};

class IlwisTestCase;

class TESTSUITESHARED_EXPORT TestSuite
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

    void addModules();
};

#endif // TESTSUITE_H
