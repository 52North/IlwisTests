#include <thread>
#include <chrono>
#include "ilwis.h"
#include "testsuite.h"
#include "kernel.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "raster.h"
#include "pixeliterator.h"
#include "geometryhelper.h"
#include "commandhandler.h"
#include "geos/geom/Envelope.inl"
#include "postgrestest.h"

REGISTER_TEST(PostgresTest);

PostgresTest::PostgresTest() : IlwisTestCase("PostgresConnectorTest", "PostgresConnectorTest")
{
}

void PostgresTest::construction() {
    Ilwis::IRasterCoverage map1;
    DOTEST(map1.prepare( makeInputPath("EV_2003_al_warp.bsq")),"basic loading idl file");

    double v  = map1->pix2value(Ilwis::Pixel(150,150,20));
}

void PostgresTest::testBigSelection() {
    //Ilwis::IRasterCoverage map1(makeInputPath("n000302.mpr"));

     //QString pol("Polygon((495209 80832,927209 -999367, 1887209 -1282307,2184809 311232,495209 80832))");
     Ilwis::IRasterCoverage map1(makeInputPath("g100_06.mpr"));
     QString pol("POLYGON((4049300 3169500,4102100 3169500,4102100 3305300,4049300 3305300,4049300 3169500))");

     geos::geom::Geometry *geom = Ilwis::GeometryHelper::fromWKT(pol, map1->coordinateSystem());
     Ilwis::PixelIterator iterIn(map1,geom);

      const geos::geom::Envelope *env = geom->getEnvelopeInternal();
      Ilwis::Envelope envelope(Ilwis::Coordinate(env->getMinX(), env->getMinY()),Ilwis::Coordinate(env->getMaxX(), env->getMaxY()));
      Ilwis::BoundingBox box = map1->georeference()->coord2Pixel(envelope);
      QString grfcode = QString("code=georef:type=corners,csy=%1,envelope=%2,gridsize=%3,name=gorilla").arg(map1->coordinateSystem()->id()).arg(envelope.toString()).arg(box.size().toString());
      Ilwis::IGeoReference grf(grfcode);

     Ilwis::IRasterCoverage map2;
     map2.prepare();

     map2->coordinateSystem(map1->coordinateSystem());
     map2->georeference(grf);
     map2->datadefRef() = map1->datadef();

     Ilwis::PixelIterator iterOut(map2, geom);
     std::copy(iterIn, iterIn.end(), iterOut);

//     Ilwis::PixelIterator iterEnd = end(map2);
//     while( iterOut != iterEnd){
//         *iterOut = *iterIn;
//         ++iterOut;
//         ++iterIn;
//     }
     QString output = makeInputPath("aa12.mpr");
     map2->connectTo(output,"map","ilwis3", Ilwis::IlwisObject::cmOUTPUT);
     map2->store();
}
