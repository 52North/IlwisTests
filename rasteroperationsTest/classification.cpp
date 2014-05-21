#include "kernel.h"
#include "ilwiscontext.h"
#include "testsuite.h"
#include "catalog.h"
#include "raster.h"
#include "ilwisoperation.h"
#include "operationhelpergrid.h"
#include "classification.h"
#include "itemdomain.h"
#include "classification/sampleset.h"
#include "ilwiscontext.h"
#include "commandhandler.h"

REGISTER_TEST(Classification);

Classification::Classification() : IlwisTestCase("Classification", "RasterOperationsTest")
{
}

void Classification::initTestCase()
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

void Classification::boxclassification() {
    try{
        QString path = "file:///"+ _baseDataPath.absolutePath() + "/test";
        Ilwis::context()->setWorkingCatalog(Ilwis::ICatalog(path));

        QString expr = QString("aabox=boxclassification(eth.mpl, tempclasses.dom,ethsms.mpr,0.01)");
        Ilwis::ExecutionContext ctx;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx),"executing box classifier)");
        Ilwis::IRasterCoverage raster("ilwis://internalcatalog/aabox");
        raster->connectTo(QString("file:///%1/aabox.mpr").arg(_baseDataPath.absolutePath()), "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
        raster->createTime(Ilwis::Time::now());
        raster->store();
    } catch(const  Ilwis::ErrorObject& err ){
        qDebug() << err.message();
    }
}
