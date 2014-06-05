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

void TableTests::initTestCase()
{
    try{
        _baseDataPath = TestSuite::instance()->inputDataPath();
        if ( !_baseDataPath.exists())
            throw SkipTest("no data path defined");
        _baseDataOutputPath = TestSuite::instance()->outputDataPath();
        if ( !_baseDataOutputPath.exists())
            throw SkipTest("no data output path defined");
        Ilwis::ICatalog cat(QUrl::fromLocalFile(_baseDataPath.absolutePath()).toString());
        Ilwis::context()->setWorkingCatalog(cat);
    } catch (const Ilwis::ErrorObject& err){
        qDebug() << err.message();
    }

}

void TableTests::select() {
    Ilwis::ITable rainfalltbl("rainfall.tbt");

    DOTEST(rainfalltbl.isValid(),"loaded rainfall table");

    std::vector<quint32> records = rainfalltbl->select("january == ?");
    DOTEST(records.size() == 2, "Two records with undefined values in january");
}
