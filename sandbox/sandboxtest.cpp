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
#include "sandboxtest.h"

REGISTER_TEST(SandBox);

using namespace Ilwis;
using namespace boost;

SandBox::SandBox(): IlwisTestCase("SandBox", "SandBoxTest")
{
}

void SandBox::sometest()
{
    try {
        // to be set from API when creating an empty workflow
        OperationResource operation({"ilwis://operations/sandbox_workflow"});
        // set as a descriptive text
        operation.setLongName("First Workflow Operation");
        // also descriptive .. TODO add keyword 'workflow' implicitly
        operation.setKeywords({"keyword1, workflow"});

        Ilwis::IWorkflow workflow(operation);

        NodeProperties resampleOperation;
        QUrl resampleUrl("ilwis://operations/resample");
        resampleOperation.ilwisId = mastercatalog()->url2id(resampleUrl, itOPERATIONMETADATA);
        OVertex op1Id = workflow->addOperation(resampleOperation);

        NodeProperties mirrorRotateOperation;
        QUrl mirrorrotateUrl("ilwis://operations/mirrorrotateraster");
        mirrorRotateOperation.ilwisId = mastercatalog()->url2id(mirrorrotateUrl, itOPERATIONMETADATA);
        OVertex op2Id = workflow->addOperation(mirrorRotateOperation);

        EdgeProperties properties;
        OEdge flow1 = workflow->addOperationFlow(op1Id, op2Id, properties);

        workflow->debugPrintGraph();

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

struct NodeProperty {
    QString FirstName;
    QString LastName;
};

void SandBox::graph_test()
{
/*
    // create a typedef for the Graph type
    typedef adjacency_list<vecS, vecS, bidirectionalS, QString> Graph;
    typedef graph_traits<Graph>::vertex_descriptor MyNode;

    Graph g;
    MyNode aNode = add_vertex(g);
    MyNode bNode = add_vertex(g);

    typedef property_map<Graph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);

    std::cout << "vertices(g) = ";
    typedef graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first)
      std::cout << index[*vp.first] <<  " ";
    std::cout << std::endl;
*/


/*
    // Make convenient labels for the vertices
    //enum { A="first", B="second", C='third', D='fourth', E='fifth'};
    const int num_vertices = 5;
    const char* name = "ABCDE";

    // writing out the edges in the graph
    typedef std::pair<QString, QString> Edge;
    Edge edge_array[] =
    //{ Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
    //  Edge(C,E), Edge(B,D), Edge(D,E) };
    {
        Edge("A", "B"), Edge("A", "D"), Edge("C", "A"),
        Edge("D", "C"), Edge("C", "E"), Edge("B", "D"), Edge("D", "E")
    };
    const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);

    // declare a graph object
    Graph g(num_vertices);

    // add the edges to the graph object
    for (int i = 0; i < num_edges; ++i)
      add_edge(edge_array[i].first, edge_array[i].second, g);
*/


/*

    // get the property map for vertex indices
    typedef property_map<Graph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);

    std::cout << "vertices(g) = ";
    typedef graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; --vp.second)
      std::cout << index[*vp.second] <<  " ";
    std::cout << std::endl;





    std::cout << "edges(g) = ";
    graph_traits<Graph>::edge_iterator ei, ei_end;
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        std::cout << "(" << index[source(*ei, g)]
                  << "," << index[target(*ei, g)] << ") ";
    std::cout << std::endl;
*/
}



