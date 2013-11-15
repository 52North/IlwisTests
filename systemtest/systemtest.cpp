#include <QStringList>
#include <QString>
#include <QTest>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "kernel.h"
#include "raster.h"
#include "symboltable.h"
#include "ilwisoperation.h"
#include "numericrange.h"
//#include "line.h"
#include "ellipsoid.h"
#include "geodeticdatum.h"
#include "projection.h"
#include "numericdomain.h"
#include "domainitem.h"
#include "numericitem.h"
#include "itemdomain.h"
#include "itemrange.h"
#include "identifieritem.h"
#include "thematicitem.h"
#include "identifierrange.h"
#include "numericitemrange.h"
#include "conventionalcoordinatesystem.h"
#include "columndefinition.h"
#include "basetable.h"
#include "polygon.h"
#include "geometry.h"
#include "attributerecord.h"
#include "feature.h"
#include "featurecoverage.h"
#include "featureiterator.h"
#include "catalog.h"
#include "factory.h"
#include "abstractfactory.h"
#include "mastercatalog.h"
#include "commandhandler.h"
#include "ilwiscontext.h"
#include "indexslicer.h"
#include "systemtest.h"

#define ROOT_TESTDATA "D:/data/coding/ilwis/testdata"
//#define ROOT_TESTDATA "H:/projects/Ilwis4/testdata"

#define ISSUE(p) kernel()->issues()->popfirst().toLatin1()
using namespace Ilwis;

bool equals(double v1, double v2, double dig) {
    double d = abs(v1 - v2);
    return  d <= dig;

}

bool loaders1 = true;
bool loaders2 = true;
bool loaders3 = true;
bool loaders4 = true;
bool loaders5 = true;
bool loaders6 = true;
bool loaders7 = true;
bool loaders8 = true;

LoaderTests::LoaderTests(QObject *parent) :
    QObject(parent)
{
    _kernel.reset(kernel());
}

//Load test using the Ilwis3Connector (old ilwis data)
void LoaderTests::simpleLoaders()
{
    try{
        context()->addSystemLocation(QUrl("file:///h:/projects/Ilwis4/build/debug/win32/bin/resources"));

        QUrl s = QString("file:///%1").arg(ROOT_TESTDATA);
        mastercatalog()->addContainer(s);
        Catalog cat;
        cat.prepare(s);
        context()->setWorkingCatalog(cat);


        if (loaders1) {
            qDebug() << "ellipsoid: should fail, ellipsoid from internal wkt , doesnt exist";
            IEllipsoid ell2;
            QString res = QString("code=wkt:GRS 1987.6");
            QVERIFY2(ell2.prepare(res) == false,ISSUE(ell2));

            qDebug() << "ellipsoid: ellipsoid from internal wkt";
            IEllipsoid ell3;
            res = QString("code=wkt:GRS 1980");
            QVERIFY2(ell3.prepare(res) == true,ISSUE(ell3));

            qDebug() << "coordinatesystem: regular load from csy, csy=projected ";
            IConventionalCoordinateSystem csy3;
            res = QString("file:///%1/cochabam.csy").arg(ROOT_TESTDATA);
            QVERIFY2(csy3.prepare(res) == true,ISSUE(csy3));

            qDebug() << "projection: regular load from csy, csy=projected";
            IProjection proj1;
            res = QString("file:///%1/cochabam.csy").arg(ROOT_TESTDATA);
            QVERIFY2(proj1.prepare(res) == true,ISSUE(proj1));

            qDebug() << "coordinatesystem: regular load from csy, csy=latlon";
            ICoordinateSystem csy1;
            res = QString("file:///%1/ethiopia_dem.csy").arg(ROOT_TESTDATA);
            QVERIFY2(csy1.prepare(res) == true,ISSUE(csy1));

            qDebug() << "coordinatesystem: regular load from  epsg";
            ICoordinateSystem csy4;
            res = QString("code=epsg:5464");
            QVERIFY2(csy4.prepare(res) == true,ISSUE(csy4));

            qDebug() << "Georeference: regular load grf = corners ";
            IGeoReference grf1;
            res = QString("file:///%1/alm011nd.grf").arg(ROOT_TESTDATA);
            QVERIFY2(grf1.prepare(res) == true,ISSUE(grf1));

            qDebug() << "Georeference: regular load grf = ctp , afine";
            IGeoReference grf2;
            res = QString("file:///%1/tmgeo.grf").arg(ROOT_TESTDATA);
            QVERIFY2(grf2.prepare(res) == true,ISSUE(grf2));


            IRasterCoverage map1;
            res = QString("file:///%1/n000302.mpr").arg(ROOT_TESTDATA);
            QVERIFY2(map1.prepare(res) == true,ISSUE(map1));

            res = QString("file:///%1/201302051200_CH_3_2_1_band_2.mpr").arg(ROOT_TESTDATA);
            QVERIFY2(map1.prepare(res) == true,ISSUE(map1));

            qDebug() << "3D grid coverage, ilwis 3 mpl as coverage: regular";
            IRasterCoverage mapgdal;
            res = QString("file:///%1/average_monthly_temperature.mpl").arg(ROOT_TESTDATA);
            mapgdal.prepare(res);

            qDebug() << "loading raster with thematic domain";
            res = QString("file:///%1/Landuse.mpr").arg(ROOT_TESTDATA);
            QVERIFY2(map1.prepare(res) == true, ISSUE(map1));

            qDebug() << "grid: regular load from csy, csy=latlon; this time as bare ilwis-object";
            IIlwisObject obj1;
            res = QString("file:///%1/average_monthly_temperature_october_11.mpr").arg(ROOT_TESTDATA);
            QVERIFY2(obj1.prepare(res, itRASTER) == true,ISSUE(obj1));


        }
    }
    catch (ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}
void LoaderTests::coordTransformations() {
    try{
        if ( loaders2) {
            ICoordinateSystem csy1;
            Resource resource(QString("code=proj4:+proj=longlat +ellps=WGS84 +datum=WGS84"), itCOORDSYSTEM);
            csy1.prepare(resource);

            ICoordinateSystem csy2;
            QString res = QString("file:///%1/ndvi_long.csy").arg(ROOT_TESTDATA);
            csy2.prepare(res);

            qDebug() << "albers equal area to latlon : proj4";
            Coordinate c(-360932.48,312388.06);
            LatLon ll = csy2->coord2latlon(c);
            QVERIFY2(equals(ll.lon(),16.55,0.01),ISSUE(csy2));

            qDebug() << "latlon to utm zone 29 : proj4";
            csy2->prepare("code=proj4:+proj=utm +zone=29 +a=6378249.2 +b=6356515 +towgs84=-23,259,-9,0,0,0,0");
            Coordinate cc = csy2->latlon2coord(LatLon(9.535, -9.825));
            QVERIFY2(equals(cc.x(),409453,1),ISSUE(csy2));
        }

    }
    catch (ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}


void LoaderTests::gridCoverageDataAccess() {
    try{
        if (loaders3) {
            IRasterCoverage map1;
            QString res = QString("file:///%1/n000302.mpr").arg(ROOT_TESTDATA);
            map1.prepare(res);

            qDebug() << "Gridcoverage: access value at coord location. dom = image";
            QVERIFY2(map1->coord2value(Coordinate(112109.75,128832.51)) == 71.0,ISSUE(map1));

            qDebug() << "Gridcoverage: access value at Pixel location, dom=image";
            QVERIFY2(map1->pix2value(Pixel(564, 623)) == 169.0,ISSUE(map1));

            IRasterCoverage map2;
            res = QString("file:///%1/kenya_2009ndvi_cor_22.mpr").arg(ROOT_TESTDATA);
            map2.prepare(res);

            qDebug() << "Gridcoverage: access value at Pixel location, dom=value(raw values), grf = submap";
            QVERIFY2(equals(map2->pix2value(Pixel(416,501)), 0.232,0.0001),ISSUE(map2));

            res = QString("file:///%1/201302051200_CH_3_2_1_band_2.mpr").arg(ROOT_TESTDATA);
            map2.prepare(res);
            QVERIFY2(equals(map2->pix2value(Pixel(416,501)), 5.43,0.01),ISSUE(map2));

            qDebug() << "raster: regular load grf = ctp, afine ";
            res = QString("file:///%1/tmb1.mpr").arg(ROOT_TESTDATA);
            QVERIFY2(map1.prepare(res) == true,ISSUE(grf2));

            qDebug() << "Gridcoverage: access value at coord location. dom = image, georef=ctp, afine";
            QVERIFY2(map1->coord2value(Coordinate(800827.47,8083453.21)) == 40.0,ISSUE(map1));

            IRasterCoverage maplist;
            res = QString("file:///%1/average_monthly_temperature.mpl").arg(ROOT_TESTDATA);
            maplist.prepare(res);

            qDebug() << "3D Gridcoverage: access value at Voxel location, 898,277,3";
            QVERIFY2(equals(maplist->pix2value(Voxel(898,277,3)), 24.20,0.001),ISSUE(maplist));

            qDebug() << "Pixel access thematic domain";
            res = QString("file:///%1/Landuse.mpr").arg(ROOT_TESTDATA);
            map1.prepare(res);
            quint32 val = map1->coord2value(Coordinate(800348.443438,8082390.774796));
            QString item = map1->datadef().domain()->value(val);
            QVERIFY2(item == "Shrubs", ISSUE(map1));

            qDebug() << "PixelIterator ";

            qDebug() << "indexed access, for loop and std::copy";
            res = QString("file:///%1/small.mpl").arg(ROOT_TESTDATA);
            maplist.prepare(res);
            PixelIterator iter(maplist);
            double v = iter[31];
            double sum = 0;
            for(double v : maplist) {
                if ( v!= rUNDEF)
                    sum += v;
            }
            quint64 sz = maplist->size().totalSize();
            std::vector<double> vec(sz);
            std::copy(begin(maplist), end(maplist), vec.begin());
            QVERIFY2((int)sum == 12446, ISSUE(maplist));
            QVERIFY2(v == 32, ISSUE(maplist));
            QVERIFY2(vec[8] == 130, ISSUE(maplist));
        }
    }
    catch (ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void LoaderTests::gdalConnector()
{
    try{
        qDebug() << "Starting testing gdal connector";

        IRasterCoverage map1;
        qDebug() << "Gridcoverage: regular load rastercoverage through gdal connector ";
        QString res = QString("file:///%1/f41078a1.tif").arg(ROOT_TESTDATA);
        QVERIFY2(map1.prepare(res) == true,ISSUE(map1));


        qDebug() << "Gridcoverage: regular load rastercoverage(list) through gdal connector ";
        IRasterCoverage maplist;
        res = QString("file:///%1/GCL_INT.tif").arg(ROOT_TESTDATA);
        QVERIFY2(maplist.prepare(res) == true,ISSUE(maplist));

        qDebug() << "Gridcoverage: access value through GDAL";
        res = QString("file:///%1/f41078a1.tif").arg(ROOT_TESTDATA);
        IRasterCoverage map3;
        map3.prepare(res);
        QVERIFY2(map3->pix2value(Pixel(3278,2669)) == 4,ISSUE(map3));

        qDebug() << "Gridcoverage: access value through GDAL, maplist";
        res = QString("file:///%1/GCL_INT.tif").arg(ROOT_TESTDATA);
        maplist.prepare(res);
        QVERIFY2(maplist->pix2value(Voxel(239,297,23)) == 48, ISSUE(maplist));

        qDebug() << "Gridcoverage: access value through GDAL, ENVI-IDL";
        res = QString("file:///%1/a_200006_bv.img").arg(ROOT_TESTDATA);
        QVERIFY2(map1.prepare(res) == true,ISSUE(map1));

        IRasterCoverage map2;
        res = QString("file:///%1/n000302.mpr").arg(ROOT_TESTDATA);
        map2.prepare(res) == true,ISSUE(map2);

        qDebug() << "Gridcoverage: saving to geotiff";
        map2->connectTo(QUrl(), "GTiff","gdal",Ilwis::IlwisObject::cmOUTPUT);
        QVERIFY2(map2->store(IlwisObject::smBINARYDATA | IlwisObject::smMETADATA), ISSUE(map2));

        IFeatureCoverage map4;
        qDebug() << "FeatureCoverage: loadMetaData a featurecoverage ";
        QString res2 = QString("file:///%1/shape/regions.shp").arg(ROOT_TESTDATA);
        QVERIFY2(map4.prepare(res2) == true, QString("FeatureCoverage: %1").arg(map4->toString()).toLatin1());
        qDebug() << "FeatureCoverage: testing envelope (bbox)";
        QVERIFY2(map4->envelope().toString() == "POLYGON(33.006454 3.400880 0.000000,47.960530 14.963722 0.000000)",QString("FeatureCoverage: %1").arg(map4->toString()).toLatin1());

        qDebug() << "FeatureCoverage: loadBinaryData of featurecoverage (points)";
        QString res3 = QString("file:///%1/shape/rainfall.shp").arg(ROOT_TESTDATA);
        IFeatureCoverage map5;
        QVERIFY2(map5.prepare(res3) == true,QString("FeatureCoverage: %1").arg(map5->toString()).toLatin1());
        FeatureIterator iter2(map5);
        SPFeatureI f4 = *(iter2 + 1);
        QVariant output = f4->cell("RAINFALL");
        QVERIFY2(output.toString() == "taquina", QString("value: %1").arg(output.toString()).toLatin1());
        f4 = *(iter2 + 4);
        output = f4->cell("JANUARY");
        QVERIFY2(output.toInt() == 85 , QString("value: %1").arg(output.toString()).toLatin1());

        qDebug() << "FeatureCoverage: loadBinaryData of featurecoverage (lines)";
        QString res4 = QString("file:///%1/shape/drainage.shp").arg(ROOT_TESTDATA);
        IFeatureCoverage map6;
        QVERIFY2(map6.prepare(res4) == true,QString("FeatureCoverage: %1").arg(map6->toString()).toLatin1());
        FeatureIterator iter3(map6);
        SPFeatureI f5 = *(iter3 + 104);
        output = f5->cell("DRAINAGE");
        QVERIFY2(output.toString() == "lake", QString("value: %1").arg(output.toString()).toLatin1());
        f5 = *(iter3 + 21);
        output = f5->cell("C1");
        QVERIFY2(output.toInt() == 1 , QString("value: %1").arg(output.toString()).toLatin1());

        qDebug() << "FeatureCoverage: loadBinaryData of featurecoverage (polygons)";
        QString res5 = QString("file:///%1/shape/geology.shp").arg(ROOT_TESTDATA);
        IFeatureCoverage map7;
        QVERIFY2(map7.prepare(res5) == true, QString("FeatureCoverage: %1").arg(map7->toString()).toLatin1());
        FeatureIterator iter4(map7);
        SPFeatureI f6 = *(iter4 + 40);
        output = f6->cell("GEOLOGY");
        QVERIFY2(output.toString() == "Shales", QString("value: %1").arg(output.toString()).toLatin1());


    }
    catch (ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void LoaderTests::featureData()
{
    try{
        if ( loaders4) {
            qDebug() << "feature coverage, ilwis 3";
            IFeatureCoverage fcoverage;
            QString res = QString("file:///%1/Rainfall.mpp").arg(ROOT_TESTDATA);
            QVERIFY2(fcoverage.prepare(res) == true, ISSUE(fcoverage));

            qDebug() << "segment coverage, ilwis 3";
            IFeatureCoverage fcoverage2;
            res = QString("file:///%1/Contour.mps").arg(ROOT_TESTDATA);
            QVERIFY2(fcoverage2.prepare(res) == true, ISSUE(fcoverage));

            qDebug() << "point access, ilwis 3";
            IFeatureCoverage fcoverage3;
            res = QString("file:///%1/Rainfall.mpp").arg(ROOT_TESTDATA);
            fcoverage3.prepare(res);

            FeatureIterator iter(fcoverage);
            SPFeatureI f = *(iter + 4);
            QVERIFY2(f("january").toInt() == 93, ISSUE(fcoverage));

            FeatureIterator iter2(fcoverage2);
            SPFeatureI f2 = *(iter2 + 10);
            QVERIFY2(f2(FEATUREVALUECOLUMN).toInt() == 2600, ISSUE(fcoverage2));


            qDebug() << "polygon coverage, ilwis 3.7 format";
            IFeatureCoverage fcoverage4;
            res = QString("file:///%1/soils_sadc.mpa").arg(ROOT_TESTDATA);
            QVERIFY2(fcoverage4.prepare(res) == true, ISSUE(fcoverage4));

            FeatureIterator iter3(fcoverage4);
            SPFeatureI f4 = *(iter3 + 4);
            int val = f4("FAOSOIL").toInt();

            QString item = fcoverage4->value("FAOSOIL",val).toString();
            QVERIFY2(item == "Rd18-3ab", ISSUE(fcoverage4));
        }
    } catch(ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void LoaderTests::domainandtableAccess() {

    try{
        if ( loaders5) {
            IDomain dom;
            QString res = QString("file:///%1/landuse.dom").arg(ROOT_TESTDATA);
            qDebug() << "Thematic domain: regular load";
            QVERIFY2(dom.prepare(res) == true, ISSUE(dom));

            ITable tbl;
            res = QString("file:///%1/Rainfall.tbt").arg(ROOT_TESTDATA);
            qDebug() << "Table: regular load";
            QVERIFY2(tbl.prepare(res) == true, ISSUE(tbl));

            qDebug() << "Table: data access";
            std::vector<QVariant> values = tbl->column("february");
            QVERIFY2(values[2] == 165, ISSUE(tbl));

            qDebug() << "Table: adding data in new column";
            IDomain dmcount;
            dmcount.prepare("count");
            QVERIFY2(tbl->addColumn("newcol_123", dmcount) == true, ISSUE(tbl));

            std::vector<QVariant> newvalues;
            newvalues = {20, 30 , 40, 60};
            tbl->column("newcol_123", newvalues);
            values = tbl->column("newcol_123");
            QVERIFY2(values[2] == 40, ISSUE(tbl));

        }

    }
    catch (ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }

}

void LoaderTests::indexDomains()
{
    try{
        IRasterCoverage mpl;
        QString res = QString("file:///%1/small.mpl").arg(ROOT_TESTDATA);
        mpl.prepare(res);

        INumericItemDomain numdom;
        numdom.prepare();
        NumericItemRange nrange;
        nrange.interpolation("%1 + %2");
        nrange << "0 100 1" << "200" << "300" << "400" << "500" << "1000" << "1500";
        numdom->setRange(nrange);


        qDebug() << "Sub indexing numeric item domain, continuous, single band";
        mpl->datadefIndex().domain(numdom);
        mpl->setLayerIndexes(nrange);
        IndexSlicer slicer(mpl);
        IRasterCoverage raster = slicer("345");
        QVERIFY2(raster.isValid(), ISSUE(raster));

        qDebug() << "Sub indexing numeric item domain, discrete, single band";
        nrange.interpolation("");
        numdom->setRange(nrange);
        raster = slicer("556");
        QVERIFY2(raster.isValid(), ISSUE(raster));

        qDebug() << "Sub indexing numeric domain, discrete, single band";
        INumericDomain numdom2;
        numdom2.prepare();
        numdom2->range(new NumericRange(0,7,1));
        mpl->datadefIndex().domain(numdom2);
        slicer.grid(mpl);
        raster = slicer("5");
        QVERIFY2(raster.isValid(), ISSUE(raster));

        qDebug() << "Sub indexing numeric domain, continuous, single band";
        mpl->datadefIndex().range()->interpolation("%1 + %2");
        slicer.grid(mpl);
        raster = slicer("5.7");
        QVERIFY2(raster.isValid(), ISSUE(raster));


    }    catch (ErrorObject& err) {
        qDebug() << err.message();
    }
}

void LoaderTests::thematicDomains()
{
    try{
        IThematicDomain parentdom;
        parentdom.prepare();
        ThematicRange rng;
        rng << "building" << "road rd"<< "forest fr" << "mountain mo" << "lake l" << "sea s" << "hill" << "plain";
        parentdom->setRange(rng);
        parentdom->setTheme("my theme");

        qDebug() << "Testing thematic domains";
        qDebug() << "Basic testing : filling, members, containement";
        QVERIFY2(parentdom->count() == 8 , ISSUE(parentdom));
        QVERIFY2(parentdom->item("road")->raw() == 1, ISSUE(parentdom));
        QVERIFY2(parentdom->contains("mountain") == Domain::cSELF,ISSUE(parentdom));
        QVERIFY2(parentdom->contains("swamp") != Domain::cSELF,ISSUE(parentdom));

        qDebug() << "setting parent domain; raws will reflect the parent domain";
        IThematicDomain childom1;
        childom1.prepare();
        childom1->setTheme("my theme");
        ThematicRange childrng;
        childrng << "building" << "lake l" << "sea s" << "hill";
        childom1->setRange(childrng);
        childom1->setParent(parentdom);
        QVERIFY2(childom1->item("lake")->raw() == 4, ISSUE(parentdom));

        qDebug() << "removing value from parent; should block as it is also part of child";
        parentdom->removeItem("sea");
        QVERIFY2(hasType(parentdom->contains("sea"), Domain::cDECLARED),ISSUE(childom1));

        qDebug() << "adding item to child; should block as it is not part of parent";
        childom1->addItem(new ThematicItem({"swamp"}));
        QVERIFY2(childom1->contains("swamp") != Domain::cSELF,ISSUE(childom1));

        qDebug() << "asking for containement of a item from the parent in a non-strict child";
        childom1->setStrict(false);
        QVERIFY2(childom1->contains("road") == Domain::cPARENT,ISSUE(childom1));


    }catch(ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void LoaderTests::masterCatalogAdmin()
{
    try {
#ifdef QT_DEBUG
        qDebug() << "Admin mastercatalog testing";
        int nbegin = mastercatalog()->lookupSize();
        qDebug() << "start : "<< nbegin ;
        {
            SymbolTable symtbl;
            Operation op({"aad1=sin(small.mpr)"});
            ExecutionContext ctx;
            QVERIFY2(op->execute(&ctx,symtbl) == true,"operation done");

            int nend = mastercatalog()->lookupSize();;
            qDebug() << "before end : " << nend;


        }
        int nend = mastercatalog()->lookupSize();;
        qDebug() << "end : " << nend;
        QVERIFY2(nbegin == nend,"checking frees of objects");

        mastercatalog()->dumpLookup();

#endif
    } catch (ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }
}

void LoaderTests::tabcalc()
{
    SymbolTable symtbl;
    ExecutionContext ctx;
    try{
        qDebug() << "starting tabcalc";

        qDebug() << "simple copying of column";
        ctx.clear();
        QVERIFY(commandhandler()->execute("aa16=rainfall.tbt[march]",&ctx, symtbl));
        ITable tbl1 = symtbl.getValue(ctx._results[0]).value<Ilwis::ITable>();
        QVERIFY2(tbl1->cell(0,3) == 150, "finished copying column");

        ctx.clear();
        qDebug() << "adding to a column";
        QVERIFY(commandhandler()->execute("script aa17=rainfall.tbt[march] + 100",&ctx, symtbl));
        tbl1 = symtbl.getValue(ctx._results[0]).value<Ilwis::ITable>();
        QVERIFY2(tbl1->cell(0,3) == 250, "finished copying column");

        qDebug() << "adding to a column to a new table with the name b";
        QVERIFY(commandhandler()->execute("script aa18[a]=rainfall.tbt[march] + 100",&ctx, symtbl));
        tbl1 = symtbl.getValue(ctx._results[0]).value<Ilwis::ITable>();
        QVERIFY2(tbl1->cell("a",3) == 250, "finished copying column");

        qDebug() << "multiplying a column to a new table with the name b";
        QVERIFY(commandhandler()->execute("script aa18[f]=rainfall.tbt[march] * 100",&ctx, symtbl));
        tbl1 = symtbl.getValue(ctx._results[0]).value<Ilwis::ITable>();
        QVERIFY2(tbl1->cell("f",3) == 15000, "finished copying column");

        qDebug() << "adding a column to the same table";
        QVERIFY(commandhandler()->execute("script rainfall.tbt[b]=rainfall.tbt[march] + 100",&ctx, symtbl));
        tbl1 = symtbl.getValue(ctx._results[0]).value<Ilwis::ITable>();
        QVERIFY2(tbl1->cell("b",3) == 250, "finished copying column");

        qDebug() << "calculatin log10 from a column";
        QVERIFY(commandhandler()->execute("script rainfall.tbt[c]=log10(rainfall.tbt,march)",&ctx, symtbl));
        tbl1 = symtbl.getValue(ctx._results[0]).value<Ilwis::ITable>();
        QVERIFY2(equals(tbl1->cell("c",3).toDouble(), 2.176,.01), "finished copying column");

        qDebug() << "selection of records";
        QVERIFY(commandhandler()->execute("script aa19=rainfall.tbt[5 8]",&ctx, symtbl));
        tbl1 = symtbl.getValue(ctx._results[0]).value<Ilwis::ITable>();
        QVERIFY2(tbl1->cell(1,1).toDouble() == 87, "finished copying column");


    }catch (ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }

}

void LoaderTests::accessCatalog() {
    try{
        if (loaders6) {
            QUrl res = QString("file:///%1/other").arg(ROOT_TESTDATA);
            qDebug() << "Catalog : loading valid catalog";
            Catalog cat;
            QVERIFY2(cat.prepare(res,"type='RasterCoverage'") == true,"");

            QUrl res2 = QString("file:///%1/notvalid").arg(ROOT_TESTDATA);
            qDebug() << "Catalog : loading not existing catalog, must fail";
            QVERIFY2(cat.prepare(res2) == false,"");
        }
    }
    catch (ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }

}

void LoaderTests::scriptExecution() {
    try{
        if (loaders8) {
            SymbolTable symtbl;
            ExecutionContext ctx;
            qDebug() << "basic function on raster : sin";
            Operation op({"aa1=sin(small.mpr)"});
            QVERIFY2(op->execute(&ctx,symtbl) == true,"operation done");
            dump(ctx, symtbl, itRASTER);

            qDebug() << "resample : nearest neighbour";
            QString txt("aa2resnb=resample(small.mpr,aeqsmall.grf,nearestneighbour)");
            OperationExpression o(txt);
            Operation op1(o);
            ExecutionContext ctx2;
            QVERIFY2(op1->execute(&ctx2,symtbl) == true,"resample done");
            Ilwis::IRasterCoverage map1 = symtbl.getValue(ctx2._results[0]).value<Ilwis::IRasterCoverage>();
            QVERIFY2(map1->coord2value(Coordinate(-2406910.352640,211926.041674)) == 60,"value checked");

            qDebug() << "resample : bilinear";
            txt = "aa3resbil=resample(small.mpr,aeqsmall.grf,bilinear)";
            o.setExpression(txt, symtbl);
            Operation op2(o);
            ctx2.clear();
            QVERIFY2(op2->execute(&ctx2,symtbl) == true,"resample done");
            map1 = symtbl.getValue(ctx2._results[0]).value<Ilwis::IRasterCoverage>();
            QVERIFY2(equals(map1->coord2value(Coordinate(-2354223.223422,262322.428663)),51,0.01),"value checked");

            qDebug() << "resample : bicubic";
            txt = "aa4resbic=resample(small.mpr,aeqsmall.grf,bicubic)";
            o.setExpression(txt, symtbl);
            Operation op3(o);
            ctx2.clear();
            QVERIFY2(op3->execute(&ctx2,symtbl) == true,"resample done");
            map1 = symtbl.getValue(ctx2._results[0]).value<Ilwis::IRasterCoverage>();
            QVERIFY2(map1->coord2value(Coordinate(-1827351.931246,-92743.025122)) == 95,"value checked");

            qDebug() << "resample : bicubic bigger map, using blocks";
            txt = "aa5resbic=resample(average_monthly_temperature_june_7.mpr,plate102.grf,bicubic)";
            OperationExpression o2(txt);
            Operation op4(o2);
            ctx2.clear();
            QVERIFY2(op4->execute(&ctx2,symtbl) == true,"resample done");
            map1 = symtbl.getValue(ctx2._results[0]).value<Ilwis::IRasterCoverage>();
            dump(ctx2, symtbl, itRASTER);
            QVERIFY2(equals(map1->coord2value(Coordinate(4219540.709810,1183145.876613)),12.42,0.01),"value checked");

            qDebug() << "selection by attribute";
            txt = "aa6.mpr=Landuse.mpr[Landvalue]";
            o.setExpression(txt, symtbl);
            Operation op5(o);
            ctx.clear();
            QVERIFY2(op5->execute(&ctx,symtbl) == true,"map selection done ");
            dump(ctx, symtbl, itRASTER);

            qDebug() << "selection by box";
            txt = "aa7.mpr=Landuse.mpr[225 331,542 660]";
            o.setExpression(txt, symtbl);
            Operation op7(o);
            ctx.clear();
            QVERIFY2(op7->execute(&ctx,symtbl) == true,"map selection done ");
            dump(ctx, symtbl, itRASTER);

            qDebug() << "script as text line";
            txt = "script aa9=pixel2coord(aa6.mpr,Pixel(100,100))";
            o.setExpression(txt, symtbl);
            Operation op8(o);
            ctx.clear();
            QVERIFY2(op8->execute(&ctx,symtbl) == true,"map selection done ");


            qDebug() << "script ading two maps from different connectors";
            txt = "script aa15=average_monthly_temperature_august_2.tif + average_monthly_temperature_december_3.mpr";
            o.setExpression(txt, symtbl);
            Operation op14(o);
            ctx.clear();
            QVERIFY2(op14->execute(&ctx,symtbl) == true,"map calc done ");

            qDebug() << "assignment feature coverage";
            txt = "aa10=rainfall.mpp";
            o.setExpression(txt, symtbl);
            Operation op9(o);
            ctx.clear();
            QVERIFY2(op9->execute(&ctx,symtbl) == true,"assignment of polygonmaps");

            qDebug() << "double selection by box";
            txt = "script aa11.mpr=small_thema.mpr[2 0,4 3][Landvalue]";
            o.setExpression(txt, symtbl);
            Operation op10(o);
            ctx.clear();
            QVERIFY2(op10->execute(&ctx,symtbl) == true,"map selection done ");

            qDebug() << "aggregate rastermap 1";
            txt = "aa12=aggregateraster(small.mpl,Avg,{2 2 2},true)";
            o.setExpression(txt, symtbl);
            Operation op13(o);
            ctx.clear();
            QVERIFY2(op13->execute(&ctx,symtbl) == true,"aggregation rastermaps");
            dump(ctx, symtbl, itRASTER);

            qDebug() << "aggregate rastermap 2";
            txt = "aa12=aggregateraster(kenya_2009ndvi_cor_22.mpr,Avg,4,true)";
            o.setExpression(txt, symtbl);
            Operation op12(o);
            ctx.clear();
            QVERIFY2(op12->execute(&ctx,symtbl) == true,"aggregation rastermaps");
            dump(ctx, symtbl, itRASTER);

            qDebug() << "executing area numbering";
            ctx.clear();
            QVERIFY(commandhandler()->execute("aa13=areaNumbering(smallareanum.mpr,4)",&ctx, symtbl));
            dump(ctx, symtbl, itRASTER);

            qDebug() << "setting value range";
            ctx.clear();
            QVERIFY(commandhandler()->execute("setvaluerange(small2.mpr,20,40,2)",&ctx, symtbl));

            qDebug() << "executing adding two feature maps";
            ctx.clear();
            QVERIFY(commandhandler()->execute("aa14=binarymathfeatures(Drainage.mps,Rainfall.mpp,add)",&ctx, symtbl));

            qDebug() << "cross";
            ctx.clear();
            QVERIFY(commandhandler()->execute("aa14,aa15=cross(small_thema2.mpr, small_thema3.mpr, dontcare)",&ctx, symtbl));

            //qDebug() << "gridding";
            //ctx.clear();
            //QVERIFY(commandhandler()->execute("script aa16=gridding(ethiopia_dem.csy, coordinate(34.194008,12.365958), 3,3,10,12)",&ctx, symtbl));


//            qDebug() << "executing script test.isf";
//            txt = QString("script file:///%1/test.isf").arg(ROOT_TESTDATA);
//            qDebug() << "Execute script";
//            ctx.clear();
//            QVERIFY(commandhandler()->execute(txt,&ctx));

        }
    }
    catch (ErrorObject& err) {
        qDebug() << err.message();
        QVERIFY(false);
    }

}


void LoaderTests::dump(const ExecutionContext& ctx, const SymbolTable& symtbl, quint64 tp) {
    if ( ctx._results.size() == 0)
        return;

    if ( tp == itRASTER) {
//        IRasterCoverage mp = symtbl.getValue(ctx._results[0]).value<Ilwis::IRasterCoverage>();
//        if ( mp.isValid()) {
//            mp->connectTo(QUrl(), "map","ilwis3",Ilwis::IlwisObject::cmOUTPUT);
//            mp->setCreateTime(Ilwis::Time::now());
//            mp->store(IlwisObject::smBINARYDATA | IlwisObject::smMETADATA);
//        }
    }
}
