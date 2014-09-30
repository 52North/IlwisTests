#include "ilwis.h"
#include "../TestSuite/testsuite.h"
#include "kernel.h"
#include "ilwiscontext.h"
#include "ilwisdata.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "table.h"
#include "raster.h"
#include "pixeliterator.h"
#include "coverage.h"
#include "ellipsoid.h"
#include "projection.h"
#include "coordinatesystem.h"
#include "geometryhelper.h"
#include "pixeliteratortest.h"

REGISTER_TEST(PixelIteratorTest);

PixelIteratorTest::PixelIteratorTest(): IlwisTestCase("PixelIteratorTest", "CoreTest")
{
}

void PixelIteratorTest::ziterator() {
     QString res = makeInputPath("small.mpl");
     Ilwis::IRasterCoverage raster(res);

     Ilwis::PixelIterator iter(raster);
     iter.setFlow(Ilwis::PixelIterator::fZXY);

     quint32 sum = 0;
     while(iter != iter.end()){
        sum += *iter;
         ++iter;
     }
     DOTEST(sum == 5924,"correct summation of pixel values, using z direction to iterate");
}

void PixelIteratorTest::rasterSelection() {
     Ilwis::IRasterCoverage map1(makeInputPath("n000302.mpr"));

      QString pol("Polygon((495209 80832,927209 -999367, 1887209 -1282307,2184809 311232,495209 80832))");
      geos::geom::Geometry *geom = Ilwis::GeometryHelper::fromWKT(pol, map1->coordinateSystem());
      Ilwis::PixelIterator iterIn(map1,geom);

      Ilwis::IRasterCoverage map2;
      map2.prepare();

      map2->coordinateSystem(map1->coordinateSystem());
      map2->georeference(map1->georeference());
      map2->datadefRef() = map1->datadef();

      Ilwis::PixelIterator iterOut(map2, geom);

      Ilwis::PixelIterator iterEnd = end(map1);
      while( iterIn != iterEnd){
          *iterOut = *iterIn;
          ++iterOut;
          ++iterIn;
      }
      QString output = makeInputPath("aa12.mpr");
      map2->connectTo(output,"map","ilwis3", Ilwis::IlwisObject::cmOUTPUT);
      map2->store();

      Ilwis::IRasterCoverage map4("Landuse.mpr");
      QString pol2("Polygon((797083.741986 8085632.198573, 798298.074263 8076615.781740, 806555.533743 8076008.615623, \
                   805887.650991 8083901.775140, 797083.741986 8085632.198573), (799724.883355 8081624.902202, \
                   801880.323004 8077617.605832, 802912.505371 8081958.843567, 799724.883355 8081624.902202))");

//              QString pol2("Polygon((797083.741986 8085632.198573, 798298.074263 8076615.781740, 806555.533743 8076008.615623, \
//                           805887.650991 8083901.775140, 797083.741986 8085632.198573))");

      geom =  Ilwis::GeometryHelper::fromWKT(pol2, map4->coordinateSystem());

      Ilwis::IRasterCoverage map3;
      map3.prepare();

      map3->coordinateSystem(map4->coordinateSystem());
      map3->georeference(map4->georeference());
      map3->datadefRef() = map4->datadef();

      iterOut = Ilwis::PixelIterator (map3, geom);

      Ilwis::PixelIterator iterIn2(map4,geom);
      iterEnd = end(map3);
      while( iterIn2 != iterEnd){
          *iterOut = *iterIn2;
          ++iterOut;
          ++iterIn2;
      }

      output = makeInputPath("aa12b.mpr");
      map3->connectTo(output,"map","ilwis3", Ilwis::IlwisObject::cmOUTPUT);
      map3->store();


      delete geom;


}



