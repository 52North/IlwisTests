#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QUrl>
#include <QDir>

#include "kernel.h"
#include "raster.h"
#include "catalog.h"
#include "symboltable.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"

#include "ilwisoperation.h"

#include "itemrange.h"
#include "domainitem.h"
#include "itemdomain.h"

#include "interval.h"
#include "numericdomain.h"
#include "intervalrange.h"
#include "feature.h"
#include "featurecoverage.h"

#include "testsuite.h"
#include "testutils.h"
#include "featureoperationstest.h"

REGISTER_TEST(FeatureOperations);

FeatureOperations::FeatureOperations(): IlwisTestCase("FeatureOperations", "FeatureOperationsTest")
{
}

void FeatureOperations::pointrastercross() {

    QString expr = QString("aacrosspoints=pointrastercrossing(ETH_M_TOWN.mpp, average_monthly_temperature.mpl, band)");
    Ilwis::ExecutionContext ctx;
    Ilwis::SymbolTable symTable;
    DOTEST(Ilwis::commandhandler()->execute(expr,&ctx, symTable),"executed pointrastercrossing)");
    Ilwis::IFeatureCoverage crossedpoints("ilwis://internalcatalog/aacrosspoints");
    crossedpoints->connectTo(QString("file:///%1/aacrosspoints.mpp").arg(_baseDataPath.absolutePath()), "vectormap","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
    crossedpoints->createTime(Ilwis::Time::now());
    crossedpoints->store();
}




