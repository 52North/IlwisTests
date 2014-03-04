#ifndef WFSRESPONSETEST_H
#define WFSRESPONSETEST_H

#include "kernel.h"
#include "testmacros.h"
#include "ilwistestclass.h"

namespace Ilwis {
namespace Wfs {


class WfsResponseTest: IlwisTestCase
{
    Q_OBJECT

public:
    WfsResponseTest();

private:
    NEW_TEST(WfsResponseTest);

private slots:
    void shouldRecognizeExceptionReport();
    void shouldParseExceptionReportWithDetails();
    void shouldNotRecognizeExceptionReport();
};
}

}

#endif // WFSRESPONSETEST_H
