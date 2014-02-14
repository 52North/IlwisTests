#ifndef TESTMACROS_H
#define TESTMACROS_H

#define DOTEST(action,message) \
qDebug() << message; \
QVERIFY2(action,"Failure")

#define NEW_TEST(name) \
static name *dummy_name

#define REGISTER_TEST(name) \
    name *name::dummy_name = static_cast<name *>(TestSuite::instance()->registerTest(new name()))

#define DOTESTAPP(v1,v2, delta, message)  \
    qDebug() << message; \
    QVERIFY2(std::abs(v1 - v2) < delta,"Failure")

#endif // TESTMACROS_H
