#ifndef TESTMACROS_H
#define TESTMACROS_H

#define DOTEST(action, message) \
qDebug() << message; \
QVERIFY2(action, "Failure")

#define DOTEST2(action, failureMsg) \
QVERIFY2(action, QString(failureMsg).toLatin1().constData())

#define NEW_TEST(name) \
static name *dummy_name

#define REGISTER_TEST(name) \
    name *name::dummy_name = static_cast<name *>(TestSuite::instance()->registerTest(new name()))

#define DOTESTAPP(v1,v2, delta, message)  \
    qDebug() << message; \
    QVERIFY2(std::abs(v1 - v2) < delta, "Failure")

#define APPROX(v1,v2,delta) (std::abs(v1 - v2) < delta)

#endif // TESTMACROS_H
