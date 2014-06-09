#include "kernel.h"
#include "../TestSuite/testsuite.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "catalog.h"
#include "ilwiscontext.h"
#include "tabletests.h"

REGISTER_TEST(TableTests);

TableTests::TableTests() : IlwisTestCase("TableTests","CoreTest")
{
}

void TableTests::select() {
    Ilwis::ITable rainfalltbl("rainfall.tbt");

    DOTEST(rainfalltbl.isValid(),"loaded rainfall table");

    std::vector<quint32> records = rainfalltbl->select("january == ?");
    DOTEST(records.size() == 2, "Two records with undefined values in january");
}
