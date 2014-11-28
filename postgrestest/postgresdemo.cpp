#include <QFileInfo>
#include <QUrl>
#include <QDir>

#include "geos/io/ParseException.h"
#include "geos/geom/GeometryFactory.h"
#include "geos/geom/LinearRing.h"
#include "geos/geom/Polygon.h"

#include "kernel.h"
#include "ilwisobject.h"
#include "ilwisdata.h"
#include "geometries.h"
#include "ilwiscontext.h"
#include "mastercatalog.h"
#include "catalog.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "attributedefinition.h"
#include "table.h"
#include "connectorinterface.h"
#include "ilwisobjectconnector.h"
#include "catalogexplorer.h"
#include "catalogconnector.h"
#include "coordinatesystem.h"
#include "coverage.h"
#include "featurecoverage.h"
#include "feature.h"
#include "featureiterator.h"
#include "geometryhelper.h"

#include "postgresdemo.h"
#include "testsuite.h"

using namespace Ilwis;

REGISTER_TEST(PostgresDemo);

PostgresDemo::PostgresDemo():
    IlwisTestCase("PostgresqlDemo", "Demo")
{
}

void PostgresDemo::storeRailsAsShapeFile()
{
    try {
        IOOptions options;
        options.addOption("pg.username", "postgres");
        options.addOption("pg.password", "postgres");
        QUrl connectionString("postgresql://localhost:5432/ilwis-pg-test/tl_2010_us_rails");
        Resource rails(connectionString, itCOVERAGE);

        IFeatureCoverage fcoverage;
        if ( !fcoverage.prepare(rails,options)) {
            QFAIL("Could not prepare coverage.");
        }

        fcoverage->connectTo(makeOutputPath("rails.shp"), "ESRI Shapefile", "gdal", IlwisObject::cmOUTPUT);
        fcoverage->store();
    } catch (std::exception& e) {
        QFAIL(QString("exception occured: %1").arg(e.what()).toLatin1().constData());
    }

}

void PostgresDemo::storeStatesAsShapeFile()
{
    try {
        IOOptions options;
        options.addOption("pg.username", "postgres");
        options.addOption("pg.password", "postgres");
        QUrl connectionString("postgresql://localhost:5432/ilwis-pg-test/tl_2010_us_state10");
        Resource rails(connectionString,itCOVERAGE);

        IFeatureCoverage fcoverage;
        if ( !fcoverage.prepare(rails, options)) {
            QFAIL("Could not prepare coverage.");
        }

        fcoverage->connectTo(makeOutputPath("states.shp"), "ESRI Shapefile", "gdal", IlwisObject::cmOUTPUT);
        fcoverage->store();
    } catch (std::exception& e) {
        QFAIL(QString("exception occured: %1").arg(e.what()).toLatin1().constData());
    }

}
