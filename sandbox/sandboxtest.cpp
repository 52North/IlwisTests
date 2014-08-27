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
#include "raster.h"
#include "pixeliterator.h"

#include "testsuite.h"
#include "testutils.h"
#include "sandboxtest.h"

REGISTER_TEST(SandBox);

SandBox::SandBox(): IlwisTestCase("SandBox", "SandBoxTest")
{
}

void SandBox::sometest() {
    Ilwis::IRasterCoverage raster("small.mpr");
    Ilwis::PixelIterator iter(raster,Ilwis::BoundingBox(Ilwis::Pixel(1,1), Ilwis::Pixel(2,3)));
    std::vector<quint8> data(raster->size().linearSize());
    Ilwis::PixelIterator iterEnd(iter.end());
    iter = --iterEnd;
    while(iter.position().x != 0 || iter.position().y != 0) {
        qDebug() << *iter;
        --iter;
    }
}




