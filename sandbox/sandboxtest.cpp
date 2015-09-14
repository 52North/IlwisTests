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
        QString expr = QString("newmap=transformcoordinates(%1,%2)").arg("drainage.mps").arg("code=epsg:4326");
        Ilwis::ExecutionContext ctx;
        Ilwis::SymbolTable syms;
        DOTEST(Ilwis::commandhandler()->execute(expr,&ctx,syms), "transform done");

        Ilwis::IFeatureCoverage raster("ilwis://internalcatalog/newmap");
        QString outputFile = makeOutputPath("aatransformed.mpa");
        qDebug() << "write to: " << outputFile;

        raster->connectTo(outputFile, "vectormap","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
        raster->createTime(Ilwis::Time::now());
        raster->store();
    }
    catch(Ilwis::ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }


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



