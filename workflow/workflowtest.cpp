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

void WorkflowTest::executeStringOperationsWorkflow()
{
    try {
        OperationResource operation({"ilwis://operations/wf_test"}, itWORKFLOW);
        Ilwis::IWorkflow workflow(operation);

        workflow->setLongName("Workflow Creation");
        QVERIFY2(workflow->getLongName() == "Workflow Creation", "long name is not correct");
        workflow->setKeywords({"keyword1, workflow"});

        NodeProperties operation1;
        QUrl url1 = QUrl("ilwis://operations/stringfind");
        operation1.id = mastercatalog()->url2id(url1, itSINGLEOPERATION);
        OVertex op1Vertex = workflow->addOperation(operation1);

        NodeProperties operation2;
        QUrl url2 = QUrl("ilwis://operations/stringsub");
        operation2.id = mastercatalog()->url2id(url2, itSINGLEOPERATION);
        OVertex op2Vertex = workflow->addOperation(operation2);

        SPAssignedInputData sharedInputProperty = workflow->assignInputData(op2Vertex, 0);
        workflow->assignInputData({op1Vertex, 0}, sharedInputProperty);

        EdgeProperties properties;
        properties.outputIndexLastOperation = 0; // result of stringfind (idx)
        properties.inputIndexNextOperation = 1; // result as input on stringsub
        workflow->addOperationFlow(op1Vertex, op2Vertex, properties);

        workflow->createMetadata();
        workflow->debugPrintGraph();
        workflow->debugWorkflowMetadata();

        // wf_test( 44_pin_source,44_pin_searchtext [,44_pin_begin,45_pin_end] )
        QStringList requireds;
        QStringList optionals;
        workflow->parametersFromSyntax(requireds, optionals);
        QVERIFY2(requireds.size() == 2, "expected 2 required parameters!");
        QVERIFY2(optionals.size() == 2, "expected 2 optional parameters!");

        ExecutionContext ctx;
        SymbolTable symbolTable;

        workflow->assignInputData(op2Vertex, 2);
        QString executeString = QString("out=wf_test(%1,42,2)").arg("foo42bar");
        bool ok = commandhandler()->execute(executeString, &ctx, symbolTable);
        if ( !ok) {
            QFAIL("workflow execution failed.");
        }

        QString actual = symbolTable.getValue("out").toString();
        QVERIFY2(actual == "42", "incorrect substring.");

    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }

}

void WorkflowTest::executeCalculateNDVIWorkflow()
{
    try {
        OperationResource operation({"ilwis://operations/ndvi"}, itWORKFLOW);
        Ilwis::IWorkflow workflow(operation);

        workflow->setLongName("NDVI Workflow");
        QVERIFY2(workflow->getLongName() == "NDVI Workflow", "long name is not correct!");
        workflow->setKeywords({"keyword1, workflow, ndvi"});
        QVERIFY2(workflow->getKeywords().contains("ndvi"), "no 'ndvi' keyword found!");

        Ilwis::IRasterCoverage vis;
        vis.prepare(makeInputPath("b2.tif"));
        Ilwis::IRasterCoverage nir;
        nir.prepare(makeInputPath("b3.tif"));

        // ------------- create formal workflow description without data

        // used operation: binarymathraster(gridcoverage1,gridcoverage2|number,!add|substract|divide|times|mod|power)

        QUrl url1 = QUrl("ilwis://operations/binarymathraster");
        quint64 binaryOperationId = mastercatalog()->url2id(url1, itSINGLEOPERATION);

        // divident calculation
        NodeProperties calcNDVIDividentOperation;
        calcNDVIDividentOperation.id = binaryOperationId;
        OVertex ndviDividentVertex = workflow->addOperation(calcNDVIDividentOperation);
        SPAssignedInputData difference = workflow->assignInputData(ndviDividentVertex, 2);
        difference->value = "substract"; // constant assignment

        // divisor calculation
        NodeProperties calcNDVIDivisorOperation;
        calcNDVIDivisorOperation.id = binaryOperationId;
        OVertex ndviDivisorVertex = workflow->addOperation(calcNDVIDivisorOperation);
        SPAssignedInputData sum = workflow->assignInputData(ndviDivisorVertex, 2);
        sum->value = "add"; // constant assignment

        // ndvi ratio
        NodeProperties calcNDVIOperation;
        calcNDVIOperation.id = binaryOperationId;
        OVertex ndviVertex = workflow->addOperation(calcNDVIOperation);
        SPAssignedInputData ratio = workflow->assignInputData(ndviVertex, 2);
        ratio->value = "divide"; // constant assignment

        // ------------- declare input data before execution

        // input data
        SPAssignedInputData nirInput = workflow->assignInputData(ndviDividentVertex, 0);
        nirInput->inputName = "NIR";
        nirInput->value = nir->name(); // constant assignment
        SPAssignedInputData visInput = workflow->assignInputData(ndviDividentVertex, 1);
        visInput->inputName = "VIS";

        // using shared data input
        workflow->assignInputData({ndviDivisorVertex, 0}, nirInput);
        workflow->assignInputData({ndviDivisorVertex, 1}, visInput);

        // link divident and divisor outputs to ratio operation
        EdgeProperties divisorInputProperties;
        divisorInputProperties.outputIndexLastOperation = 0;
        divisorInputProperties.inputIndexNextOperation = 0;
        workflow->addOperationFlow(ndviDividentVertex, ndviVertex, divisorInputProperties);

        EdgeProperties dividentInputProperties;
        dividentInputProperties.outputIndexLastOperation = 0;
        dividentInputProperties.inputIndexNextOperation = 1;
        workflow->addOperationFlow(ndviDivisorVertex, ndviVertex, dividentInputProperties);

        workflow->createMetadata();
        workflow->debugPrintGraph();
        workflow->debugWorkflowMetadata();

        ExecutionContext ctx;
        SymbolTable symbolTable;
        QString executeString = QString("ndvi_out=ndvi(%1)").arg(vis->name()); // NIR as constant
        //QString executeString = QString("ndvi_out=ndvi(%1,%2)").arg(nir->name()).arg(vis->name());
        bool ok = commandhandler()->execute(executeString, &ctx, symbolTable);
        if ( !ok) {
            QFAIL("workflow execution failed.");
        }
        Symbol actual = symbolTable.getSymbol("ndvi_out");
        QVERIFY2(actual.isValid(), "ndvi result is not valid.");
        QVERIFY2(actual._type & itCOVERAGE, "ndvi result is not a raster.");

        Ilwis::IRasterCoverage raster("ilwis://internalcatalog/ndvi_out");
        QString outFile = makeOutputPath("ndvi_out.tiff");
        qDebug() << "write ndvi result to " << outFile;
        raster->connectTo(outFile, "GTiff","gdal",Ilwis::IlwisObject::cmOUTPUT);
        raster->createTime(Ilwis::Time::now());
        raster->store();

    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

