#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each

#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QUrl>
#include <QDir>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include "kernel.h"
#include "raster.h"
#include "catalog.h"
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
#include "coverage.h"
#include "featurecoverage.h"
#include "feature.h"
#include "raster.h"
#include "pixeliterator.h"

#include "testsuite.h"
#include "workflowtest.h"

REGISTER_TEST(WorkflowTest);

using namespace Ilwis;
using namespace boost;

WorkflowTest::WorkflowTest(): IlwisTestCase("Workflow", "WorkflowTest")
{
}

void WorkflowTest::sometest()
{
    try {
        //ESPIlwisObject o = mastercatalog()->get(mastercatalog()->url2id({"ilwis://operations/mirrorrotateraster"}, itSINGLEOPERATION));

        // to be set from API when creating an empty workflow
        OperationResource operation({"ilwis://operations/wf_test"}, itWORKFLOW);
        Ilwis::IWorkflow workflow(operation);

        workflow->setProperty("longname", "First Workflow Operation");
        workflow->setProperty("keywords", {"keyword1, workflow"});

        NodeProperties operation1;
        QUrl url1 = QUrl("ilwis://operations/stringreplace");
        //QUrl url1 = QUrl("ilwis://operations/mirrorrotateraster");
        operation1.id = mastercatalog()->url2id(url1, itSINGLEOPERATION);
        OVertex op1Id = workflow->addOperation(operation1);

        NodeProperties operation2;
        QUrl url2 = QUrl("ilwis://operations/stringsub");
        //QUrl url2 = QUrl("ilwis://operations/mirrorrotateraster");
        operation2.id = mastercatalog()->url2id(url2, itSINGLEOPERATION);
        OVertex op2Id = workflow->addOperation(operation2);

        EdgeProperties properties;
        properties.inputIndexNextStep = 1;
        properties.outputIndexLastStep = 1;
        OEdge flow1 = workflow->addOperationFlow(op1Id, op2Id, properties);

        workflow->debugPrintGraph();

        quint64 workflowId = workflow->createMetadata();
        qDebug() << "workflow-metadata-id: " << workflowId;

        // output_find = stringfind(source,searchtext,[,begin])
        // stringsub(output_find,begin,[,end])
        //
        // out_parameter_name1 = stringfind("foo42bar", "42");
        // result = stringsub("foo42bar", out_parameter_name1, 3)
        QString expectedSyntax = "wf_test(source,searchtext)";

        qDebug() << workflow->source()["syntax"];

        /*
        qDebug() << "do some workflow changes ...";
        workflow->removeOperation(op1Id);
        workflow->removeOperation(op2Id);

        // TODO

        quint64 sameWorkflowId = workflow->createMetadata();
        QVERIFY2(workflowId == sameWorkflowId, "workflow ids are different!");
        */

        /*
        Ilwis::IGeoReference grf("code=georef:type=corners,csy=epsg:21037,envelope=-3.02456e+06 -4.55547e+06 6.47259e+06 4.39692e+06,gridsize=1188 1120,name=grf1");
        QString expr = QString("aa5resbic=resample(n000302.mpr,grf1,bicubic)");
        //QString expr = QString("aa5resbic=resample(average_monthly_temperature_january_5.mpr,plate102.grf,bicubic)");
        //QString expr = QString("aa5resbic=resample(small3.mpr,aeqsmall.grf,bicubic)");

        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "resample done.");

        // Ilwis::IRasterCoverage raster("ilwis://internalcatalog/aa5resbic.ilwis");
        Ilwis::IRasterCoverage raster("ilwis://internalcatalog/aa5resbic");
        QString outputFile = makeOutputPath("aatransformed.mpa");
        qDebug() << "write to: " << outputFile;

        raster->connectTo(outputFile, "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
        raster->createTime(Ilwis::Time::now());
        raster->store();
        */



        /*
  18 ;     Error ;     Fr Jul 31 11:25:59 2015 ; metadata of transformcoordinates not properly initialized
  18 ; 207 : quint64 Ilwis::CommandHandler::findOperationId(const Ilwis::OperationExpression&) const ; commandhandler.cpp
         *
  16 ;     Error ;     Fr Jul 31 11:25:59 2015 ; Invalid property number of points for pointrastercrossing operation
  17 ;     Error ;     Fr Jul 31 11:25:59 2015 ; metadata of transformcoordinates not properly initialized

        QString expr = QString("aatransformed=transformcoordinates(Kenya.mpa, utm37.csy)");
        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable symTable;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx, symTable),"executed transformcoordinates)");
        Ilwis::IFeatureCoverage transformed("ilwis://internalcatalog/aatransformed");

        QString outputFile = makeOutputPath("aatransformed.mpa");
        qDebug() << "write to: " << outputFile;
        transformed->connectTo(outputFile, "vectormap","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
        transformed->createTime(Ilwis::Time::now());
        transformed->store();


        */

        /*
  16 ;     Error ;     Fr Jul 31 11:19:40 2015 ; Could not open for reading C:/Users/henning/AppData/Local/TestRunner/cache/gridblock_4.Ya9252
  16 ; 104 : bool Ilwis::GridBlockInternal::loadFromCache() ; grid.cpp
         *
  15 ;     Error ;     Fr Jul 31 11:19:37 2015 ; Couldnt allocate memory for raster
  16 ;     Error ;     Fr Jul 31 11:19:40 2015 ; Could not open for reading C:/Users/henning/AppData/Local/TestRunner/cache/gridblock_4.Ya9252
  17 ;     Error ;     Fr Jul 31 11:19:40 2015 ; Grid block is out of bounds
         *
        QString expr = "mirvert=mirrorrotateraster(f41078a1.tif,rotate180)";
        ExecutionContext ctx;
        commandhandler()->execute(expr, &ctx);
//        IRasterCoverage raster("ilwis://internalcatalog/mirvert");
        IRasterCoverage raster("ilwis://internalcatalog/mirvert.ilwis");
        QString outputFile = makeOutputPath("f41078a1_mirvert.tif");
        qDebug() << "write to: " << outputFile;

//        raster->prepare();
        raster->connectTo(outputFile, "GTiff", "gdal", IlwisObject::cmOUTPUT);
        raster->store();
        */

        /*
  15 ;     Error ;     Fr Jul 31 12:09:40 2015 ; Cann't find suitable factory for mirvert.ilwis
  16 ;     Error ;     Fr Jul 31 12:09:40 2015 ; Couldnt create ilwisobject ilwis://internalcatalog/mirvert
        QString expr = "mirvert=mirrorrotateraster(small.mpr,rotate180)";

        ExecutionContext ctx;
        commandhandler()->execute(expr, &ctx);
        IRasterCoverage raster("ilwis://internalcatalog/mirvert");
        //IRasterCoverage raster("ilwis://internalcatalog/mirvert.ilwis");
        raster.prepare();
        */

    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }


    /*
    try{
        Ilwis::IRasterCoverage raster("const_ras.tif");
        double v = raster->pix2value(Ilwis::Pixel(100,1900));
        Ilwis::Operation operation({"aabig=log(capereduced.tif)"});
        Ilwis::SymbolTable syms;
        Ilwis::ExecutionContext ctx;
        operation->execute(&ctx, syms);
        Ilwis::IRasterCoverage raster2("ilwis://internalcatalog/aabig");
        raster2->connectTo(QUrl("file:///d:/Projects/Ilwis/Ilwis4/testdata/aabig.tif"),"GTiff","gdal", Ilwis::IlwisObject::cmOUTPUT);
        raster2->store();
    } catch (const Ilwis::ErrorObject& err){
        qDebug() << err.message();
    }
*/
}

