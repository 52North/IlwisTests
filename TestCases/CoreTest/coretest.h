#ifndef CORETEST_H
#define CORETEST_H

#include <QObject>
#include <QLibrary>
#include "coretest_global.h"

class CORETESTSHARED_EXPORT CoreTest
{
    
public:
    CoreTest();

    //Q_PLUGIN_METADATA(IID "n52.ilwis.ilwisscript" FILE  "ilwisscript.json")
};

//extern "C" CORETESTSHARED_EXPORT void runTests();
#endif // CORETEST_H
