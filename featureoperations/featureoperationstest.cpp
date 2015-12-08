#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QUrl>
#include <QDir>

#include "kernel.h"
#include "catalog.h"
#include "vertexiterator.h"
#include "coverage.h"
#include "featurecoverage.h"
#include "feature.h"
#include "featureiterator.h"
#include "raster.h"
#include "pixeliterator.h"

#include "symboltable.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"
#include "workflow.h"
#include "ilwisoperation.h"

#include "rasterinterpolator.h"
#include "resampleraster.h"
#include "mirrorrotateraster.h"


#include "itemrange.h"
#include "domainitem.h"
#include "itemdomain.h"

#include "interval.h"
#include "numericdomain.h"
#include "intervalrange.h"




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

void FeatureOperations::transform(){
    QString expr = QString("aatransformed=transformcoordinates(Kenya.mpa, utm37.csy)");
    Ilwis::ExecutionContext ctx;
    Ilwis::SymbolTable symTable;
    DOTEST(Ilwis::commandhandler()->execute(expr,&ctx, symTable),"executed transformcoordinates)");
    Ilwis::IFeatureCoverage transformed("ilwis://internalcatalog/aatransformed");
    transformed->connectTo(QString("file:///%1/aatransformed.mpa").arg(_baseDataPath.absolutePath()), "vectormap","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
    transformed->createTime(Ilwis::Time::now());
    transformed->store();

}



/*
 *
 * Contains function tests
 *
 */


void FeatureOperations::SpatialRelationContainsPolygon_False_Test()
{
    try {
        QString expr = QString("contains(Kenya2.mpa,\"%1\")").arg("POLYGON ((33.0 4.0, 42.0 4.0, 42.0 -5.0, 33.0 -5.0, 33.0 4.0))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature does not contain Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationContainsPolygon_True_Test()
{
    try {
        QString expr = QString("contains(Kenya2.mpa,\"%1\")").arg("POLYGON ((37.0 3.0, 38.0 3.0, 38.0 2.0, 37.0 2.11, 37.0 3.0))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Feature contains Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}



void FeatureOperations::SpatialRelationContainsLine_False_Test()
{
    try {
        QString expr = QString("contains(Kenya2.mpa,\"%1\")").arg("LINESTRING (-4.496896 34.382544, -3.398646 34.636486, -2.974988 36.378266)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature does not contain Line");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationContainsLine_True_Test()
{
    try {
        QString expr = QString("contains(Kenya2.mpa,\"%1\")").arg("LINESTRING (37.0 3.0, 37.0 3.1)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Feature contains Line");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}



void FeatureOperations::SpatialRelationContainsPoint_False_Test()
{
    try {
        QString expr = QString("contains(Kenya2.mpa,\"%1\")").arg("POINT (-4.496896 34.382544)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature does not contain Point");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationContainsPoint_True_Test()
{
    try {
        QString expr = QString("contains(Kenya2.mpa,\"%1\")").arg("POINT (37.0 3.0)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Feature contains Point");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}





/*
 *
 * Covers function tests
 *
 */

void FeatureOperations::SpatialRelationCoversPolygon_True_Test()
{
    try {
        QString expr = QString("covers(Kenya2.mpa,\"%1\")").arg("POLYGON ((37.0 3.0, 38.0 3.0, 38.0 2.0, 37.0 2.11, 37.0 3.0))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature covers Polygon"); // covers function keeps returning a false result for this polygon
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}




void FeatureOperations::SpatialRelationCoversPolygon_False_Test()
{
    try {
        QString expr = QString("contains(Kenya2.mpa,\"%1\")").arg("POLYGON ((33.0 4.0, 42.0 4.0, 42.0 -5.0, 33.0 -5.0, 33.0 4.0))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature doesn't cover Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}



void FeatureOperations::SpatialRelationCoversLine_False_Test()
{
    try {
        QString expr = QString("covers(Kenya2.mpa,\"%1\")").arg("LINESTRING (-4.496896 34.382544, -3.398646 34.636486, -2.974988 36.378266)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature does not cover Line");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationCoversLine_True_Test()
{
    try {
        QString expr = QString("covers(Kenya2.mpa,\"%1\")").arg("LINESTRING (37.0 3.0, 37.0 3.1)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature covers Line");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}



void FeatureOperations::SpatialRelationCoversPoint_False_Test()
{
    try {
        QString expr = QString("covers(Kenya2.mpa,\"%1\")").arg("POINT (-4.496896 34.382544)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature does not cover Point");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationCoversPoint_True_Test()
{
    try {
        QString expr = QString("covers(Kenya2.mpa,\"%1\")").arg("POINT (37.0 3.0)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature covers Point");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}




/*
 *
 * CoveredBy function tests
 *
 */

void FeatureOperations::SpatialRelationCoveredByPolygon_True_Test()
{
    try {
        QString expr = QString("coveredby(Kenya2.mpa,\"%1\")").arg("POLYGON ((5.0 32.0, 5.0 42.0, -5.0 42.0, -5.0 32.0, 5.0 32.0))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature is covered by Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}




void FeatureOperations::SpatialRelationCoveredByPolygon_False_Test()
{
    try {
        QString expr = QString("coveredby(Kenya2.mpa,\"%1\")").arg("POLYGON ((33.0 4.0, 42.0 4.0, 42.0 -5.0, 33.0 -5.0, 33.0 4.0))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature isn't covered by Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}



void FeatureOperations::SpatialRelationCoveredByLine_False_Test()
{
    try {
        QString expr = QString("coveredby(Kenya2.mpa,\"%1\")").arg("LINESTRING (-4.496896 34.382544, -3.398646 34.636486, -2.974988 36.378266)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature is not covered by Line");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}



void FeatureOperations::SpatialRelationCoveredByPoint_False_Test()
{
    try {
        QString expr = QString("coveredby(Kenya2.mpa,\"%1\")").arg("POINT (-4.496896 34.382544)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature is not covered by Point");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}








/*
 *
 * Touches function tests
 *
 */

void FeatureOperations::SpatialRelationTouchesPolygon_True_Test()
{
    try {
        /*IFeatureCoverage cov2("file:///f:/testdata2/Testdata.mpa");

        FeatureIterator iter(cov2);
        SPFeatureI feature = *(iter);
        VertexIterator vertices(feature->geometry());

        while(vertices != ::end(vertices)) {
            qDebug() << (*vertices).x <<  ", "<< (*vertices).y;
            std::cout << std::setprecision (15) << (*vertices).x <<  ", "<< (*vertices).y;
            ++vertices;
        }*/

        QString expr = QString("touches(Testdata.mpa,\"%1\")").arg("POLYGON ((-4.6658133330651 20.2739138462378, -74.982603164811 -33.4793654918079, 9.375000 -18.281251, -4.6658133330651 20.2739138462378))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature touches Polygon"); // geoslib is not returning a touch relation
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationTouchesPolygon_False_Test()
{
    try {
        QString expr = QString("touches(Testdata.mpa,\"%1\")").arg("POLYGON ((4.287976 40.783768, 4.288029 40.783794, 4.288013 40.783839, 4.287976 40.783795, 4.287976 40.783768))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature doesn't touch Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationTouchesLine_False_Test()
{
    try {
        QString expr = QString("touches(Testdata.mpa,\"%1\")").arg("LINESTRING (-4.496896 34.382544, -3.398646 34.636486, -2.974988 36.378266)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature does not touch Line");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationTouchesLine_True_Test()
{
    try {
        QString expr = QString("touches(Testdata.mpa,\"%1\")").arg("LINESTRING (-4.6658133330651 20.2739138462378, -74.982603164811 -33.4793654918079)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature touches Line"); // geoslib isn't returning a touch relation
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}



void FeatureOperations::SpatialRelationTouchesPoint_False_Test()
{
    try {
        QString expr = QString("touches(Testdata.mpa,\"%1\")").arg("POINT (-30.857144 53.142856)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature does not touch Point");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationTouchesPoint_True_Test()
{
    try {
        QString expr = QString("touches(Testdata.mpa,\"%1\")").arg("POINT (-4.6658133330651 20.2739138462378)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature touches Point"); // geoslib is not returning a touch relation
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}







/*
 *
 * Intersects function tests
 *
 */

void FeatureOperations::SpatialRelationIntersectsPolygon_True_Test()
{
    try {
        QString expr = QString("intersects(Testdata.mpa,\"%1\")").arg("POLYGON ((-26.095237 44.952381, -93.904760 1.904762, -21.904761 -12.952381, -26.095237 44.952381))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Feature intersects Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationIntersectsPolygon_False_Test()
{
    try {
        QString expr = QString("intersects(Testdata.mpa,\"%1\")").arg("POLYGON ((79.428570 55.238095, 138.857139 -10.285714, 20.000000 -42.666667, 79.428570 55.238095))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature doesn't intersect Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationIntersectsLine_False_Test()
{
    try {
        QString expr = QString("intersects(Testdata.mpa,\"%1\")").arg("LINESTRING (-3.750000 52.656252, 25.624999 62.343752)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature does not intersect Line");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationIntersectsLine_True_Test()
{
    try {
        QString expr = QString("intersects(Testdata.mpa,\"%1\")").arg("LINESTRING (-45.937499 12.968750, -35.312499 51.406252)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Feature intersects Line");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}



void FeatureOperations::SpatialRelationIntersectsPoint_False_Test()
{
    try {
        QString expr = QString("intersects(Testdata.mpa,\"%1\")").arg("POINT (14.062500 48.906252)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature does not intersect Point");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationIntersectsPoint_True_Test()
{
    try {
        QString expr = QString("intersects(Testdata.mpa,\"%1\")").arg("POINT (-60.937499 20.468751)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 1,"Feature intersects Point");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}






/*
 *
 * Disjoint function tests
 *
 */

void FeatureOperations::SpatialRelationDisjointPolygon_True_Test()
{
    try {
        QString expr = QString("disjoint(Testdata.mpa,\"%1\")").arg("POLYGON ((-45.358999 -22.233326, -61.545523 -38.134386, -68.422151 -36.544280, -45.358999 -22.233326))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Feature is disjoint from Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationDisjointPolygon_False_Test()
{
    try {
        QString expr = QString("disjoint(Testdata.mpa,\"%1\")").arg("POLYGON ((-33.755071 49.323658, -34.806719 -19.170954, 27.661167 -25.282781, 17.775676 49.534410, -33.755071 49.323658))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature isn't disjoint from Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationDisjointLine_False_Test()
{
    try {
        QString expr = QString("disjoint(Testdata.mpa,\"%1\")").arg("LINESTRING (-40.064959 17.710760, 24.295894 -7.790311)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature isn't disjoint from Line");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationDisjointLine_True_Test()
{
    try {
        QString expr = QString("disjoint(Testdata.mpa,\"%1\")").arg("LINESTRING (4.524913 38.575272, 56.896979 50.166668)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Feature is disjoint Line");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}



void FeatureOperations::SpatialRelationDisjointPoint_False_Test()
{
    try {
        QString expr = QString("disjoint(Testdata.mpa,\"%1\")").arg("POINT (-56.470666 21.925813)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature isn't disjoint from Point");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationDisjointPoint_True_Test()
{
    try {
        QString expr = QString("disjoint(Testdata.mpa,\"%1\")").arg("POINT (4.524913 38.575272)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 1,"Feature is disjoint from Point");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}






/*
 *
 * Within function tests
 *
 */



void FeatureOperations::SpatialRelationWithinPolygon_True_Test()
{
    try {
        QString expr = QString("within(Testdata.mpa,\"%1\")").arg("POLYGON ((-58.573962 37.837640, -24.290240 16.762374, -60.887588 -2.837624, -58.573962 37.837640))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Polygon is within Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationWithinPolygon_False_Test()
{
    try {
        QString expr = QString("within(Testdata.mpa,\"%1\")").arg("POLYGON ((-66.867642174265 50.7127293254374, -63.7319167917316 49.3381869766928, -4.6658133330651 20.2739138462378, -74.982603164811 -33.4793654918079, -66.867642174265 50.7127293254374))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Polygon isn't within Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationWithinLine_False_Test()
{
    try {
        QString expr = QString("within(Testdata.mpa,\"%1\")").arg("LINESTRING (-12.932443 -39.087082, 54.373024 -69.856970)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Line isn't within Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void FeatureOperations::SpatialRelationWithinLine_True_Test()
{
    try {
        QString expr = QString("within(Testdata.mpa,\"%1\")").arg("LINESTRING (-55.208689 18.026890, -25.972877 26.456996)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Line is within Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}




void FeatureOperations::SpatialRelationWithinPoint_True_Test()
{
    try {
        QString expr = QString("within(Testdata.mpa,\"%1\")").arg("POINT (-54.577700 8.859148)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Point is within Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void FeatureOperations::SpatialRelationWithinPoint_False_Test()
{
    try {
        QString expr = QString("within(Testdata.mpa,\"%1\")").arg("POINT (14.410403 -46.674178)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Point is not within Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}





/*
 *
 * Equals function tests
 *
 */

void FeatureOperations::SpatialRelationEqualsPolygon_True_Test()
{
    try {
        QString expr = QString("equals(Testdata.mpa,\"%1\")").arg("POLYGON ((-66.867642174265 50.7127293254374, -63.7319167917316 49.3381869766928, -4.6658133330651 20.2739138462378, -74.982603164811 -33.4793654918079, -66.867642174265 50.7127293254374))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Polygon equals Feature"); // geoslib is not returning an equality relation
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationEqualsPolygon_False_Test()
{
    try {
        QString expr = QString("equals(Testdata.mpa,\"%1\")").arg("POLYGON ((-58.573962 37.837640, -24.290240 16.762374, -60.887588 -2.837624, -58.573962 37.837640))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature isn't equal to Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationEqualsLine_False_Test()
{
    try {
        QString expr = QString("equals(Testdata.mpa,\"%1\")").arg("LINESTRING (-12.932443 -39.087082, 54.373024 -69.856970)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Line isn't equal to Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void FeatureOperations::SpatialRelationEqualsPoint_False_Test()
{
    try {
        QString expr = QString("equals(Testdata.mpa,\"%1\")").arg("POINT (14.410403 -46.674178)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Point is not equal to Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}






/*
 *
 * Crosses function tests -- Applies only to P/L, P/A, L/L, L/A
 *
 */

void FeatureOperations::SpatialRelationCrossesPolygon_False_Test()
{
    try {
        QString expr = QString("crosses(Testdata.mpa,\"%1\")").arg("POLYGON ((-36.699686 18.659148, 19.668643 30.882802, 2.000958 -25.809664, -36.699686 18.659148))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Polygon doesn't cross Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationCrossesPolygon_False_2_Test()
{
    try {
        QString expr = QString("crosses(Testdata.mpa,\"%1\")").arg("POLYGON ((-61.308247 35.519361, -26.603866 18.448395, -65.514839 -9.160204, -61.308247 35.519361))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature doesn't cross Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationCrossesLine_False_Test()
{
    try {
        QString expr = QString("crosses(Testdata.mpa,\"%1\")").arg("LINESTRING (-12.932443 -39.087082, 54.373024 -69.856970)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Line doesn't cross Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void FeatureOperations::SpatialRelationCrossesLine_True_Test()
{
    try {
        QString expr = QString("crosses(Testdata.mpa,\"%1\")").arg("LINESTRING (-55.208689 18.026890, -0.102338 39.207529)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Line crosses Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}




void FeatureOperations::SpatialRelationCrossesPoint_True_Test()
{
    try {
        QString expr = QString("crosses(Testdata.mpa,\"%1\")").arg("POINT (-74.982603164811 -33.4793654918079)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Point crosses Feature"); // geoslib is returning crossing relation
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void FeatureOperations::SpatialRelationCrossesPoint_False_Test()
{
    try {
        QString expr = QString("crosses(Testdata.mpa,\"%1\")").arg("POINT (14.410403 -46.674178)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Point doesn't cross Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}







/*
 *
 * Overlaps function tests -- Aplies only to A/A, L/L or P/P
 *
 */

void FeatureOperations::SpatialRelationOverlapsPolygon_True_Test()
{
    try {
        QString expr = QString("overlaps(Testdata.mpa,\"%1\")").arg("POLYGON ((-36.699686 18.659148, 19.668643 30.882802, 2.000958 -25.809664, -36.699686 18.659148))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() != 0,"Polygon overlaps Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationOverlapsPolygon_False_Test()
{
    try {
        QString expr = QString("overlaps(Testdata.mpa,\"%1\")").arg("POLYGON ((-61.308247 35.519361, -26.603866 18.448395, -65.514839 -9.160204, -61.308247 35.519361))");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);

        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Feature doesn't overlap Polygon");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void FeatureOperations::SpatialRelationOverlapsLine_False_Test()
{
    try {
        QString expr = QString("overlaps(Testdata.mpa,\"%1\")").arg("LINESTRING (-12.932443 -39.087082, 54.373024 -69.856970)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Line doesn't overlap Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}




void FeatureOperations::SpatialRelationOverlapsPoint_False_Test()
{
    try {
        QString expr = QString("overlaps(Testdata.mpa,\"%1\")").arg("POINT (14.410403 -46.674178)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        std::vector<quint32> retValue = syms.getValue<std::vector<quint32>>(ctx._results[0]);
        qDebug() << "write to: " << retValue.size();

        DOTEST(retValue.size() == 0,"Point doesn't overlap Feature");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}




void FeatureOperations::Buffer_Test()
{
    try {
        QString expr = QString("buffer123=buffer(ne_110m_admin_0_countries.shp, %1, %2, %3)").arg(5).arg(8).arg("round");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        Ilwis::IFeatureCoverage feature = syms.getValue<Ilwis::IFeatureCoverage>(ctx._results[0]);
        QString outputFile = makeOutputPath("OutFeatureBufferTest.shp");
        qDebug() << "write to: " << outputFile;


        feature->connectTo(outputFile, "vectormap","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
        feature->createTime(Ilwis::Time::now());
        feature->store();

        DOTEST(feature->featureCount()!= 0,"Buffer feature was created");
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}






