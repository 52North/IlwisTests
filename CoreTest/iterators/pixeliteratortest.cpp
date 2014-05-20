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

void PixelIteratorTest::initTestCase()
{
    _baseDataPath = TestSuite::instance()->inputDataPath();
    if ( !_baseDataPath.exists())
        throw SkipTest("no data path defined");
    _baseDataOutputPath = TestSuite::instance()->outputDataPath();
    if ( !_baseDataOutputPath.exists())
        throw SkipTest("no data output path defined");
}

void PixelIteratorTest::ziterator() {
     QString res = QString("file:///%1/small.mpl").arg(_baseDataPath.absolutePath());
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
     Ilwis::IRasterCoverage map1(QString("file:///%1/n000302.mpr").arg(_baseDataPath.absolutePath()));

      QString pol("Polygon((495209 80832,927209 -999367, 1887209 -1282307,2184809 311232,495209 80832))");
      geos::geom::Geometry *geom = Ilwis::GeometryHelper::fromWKT(pol, map1->coordinateSystem());
      Ilwis::PixelIterator iterIn(map1,geom);

      Ilwis::IRasterCoverage map2;
      map2.prepare();

      map2->coordinateSystem(map1->coordinateSystem());
      map2->georeference(map1->georeference());
      map2->datadef() = map1->datadef();

      Ilwis::PixelIterator iterOut(map2, geom);

      Ilwis::PixelIterator iterEnd = end(map1);
      while( iterIn != iterEnd){
          *iterOut = *iterIn;
          ++iterOut;
          ++iterIn;
      }
      QString output = QString("file:///%1/aa12.mpr").arg(_baseDataOutputPath.absolutePath());
      map2->connectTo(output,"map","ilwis3", Ilwis::IlwisObject::cmOUTPUT);
      map2->store();

      delete geom;


}



