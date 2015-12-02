#ifndef FeatureOperations_H
#define FeatureOperations_H

#include <QTest>
#include "ilwistestclass.h"
#include "testmacros.h"

#include "commandhandler.h"
#include "symboltable.h"

class FeatureOperations : public IlwisTestCase
{
    Q_OBJECT

public:
    FeatureOperations();
    FeatureOperations(QString* testDataLocation);

private:
    NEW_TEST(FeatureOperations);



private Q_SLOTS:


    void pointrastercross();
    void transform();


    // Spatial relation specific tests
    void SpatialRelationContainsPolygon_False_Test();
    void SpatialRelationContainsPolygon_True_Test();
    void SpatialRelationContainsLine_False_Test();
    void SpatialRelationContainsLine_True_Test();
    void SpatialRelationContainsPoint_False_Test();
    void SpatialRelationContainsPoint_True_Test();


    void SpatialRelationCoversPolygon_True_Test();
    void SpatialRelationCoversPolygon_False_Test();
    void SpatialRelationCoversLine_True_Test();
    void SpatialRelationCoversLine_False_Test();
    void SpatialRelationCoversPoint_True_Test();
    void SpatialRelationCoversPoint_False_Test();


    void SpatialRelationCoveredByPolygon_True_Test();
    void SpatialRelationCoveredByPolygon_False_Test();
    void SpatialRelationCoveredByLine_False_Test();
    void SpatialRelationCoveredByPoint_False_Test();

    void SpatialRelationTouchesPolygon_True_Test();
    void SpatialRelationTouchesPolygon_False_Test();
    void SpatialRelationTouchesLine_True_Test();
    void SpatialRelationTouchesLine_False_Test();
    void SpatialRelationTouchesPoint_True_Test();
    void SpatialRelationTouchesPoint_False_Test();


    void SpatialRelationIntersectsPolygon_True_Test();
    void SpatialRelationIntersectsPolygon_False_Test();
    void SpatialRelationIntersectsLine_True_Test();
    void SpatialRelationIntersectsLine_False_Test();
    void SpatialRelationIntersectsPoint_True_Test();
    void SpatialRelationIntersectsPoint_False_Test();


    void SpatialRelationDisjointPolygon_True_Test();
    void SpatialRelationDisjointPolygon_False_Test();
    void SpatialRelationDisjointLine_True_Test();
    void SpatialRelationDisjointLine_False_Test();
    void SpatialRelationDisjointPoint_True_Test();
    void SpatialRelationDisjointPoint_False_Test();


    void SpatialRelationWithinPolygon_True_Test();
    void SpatialRelationWithinPolygon_False_Test();
    void SpatialRelationWithinLine_True_Test();
    void SpatialRelationWithinLine_False_Test();
    void SpatialRelationWithinPoint_True_Test();
    void SpatialRelationWithinPoint_False_Test();


    void SpatialRelationEqualsPolygon_True_Test();
    void SpatialRelationEqualsPolygon_False_Test();
    void SpatialRelationEqualsLine_False_Test();
    void SpatialRelationEqualsPoint_False_Test();

    void SpatialRelationCrossesPolygon_False_Test();
    void SpatialRelationCrossesPolygon_False_2_Test();
    void SpatialRelationCrossesLine_True_Test();
    void SpatialRelationCrossesLine_False_Test();
    void SpatialRelationCrossesPoint_True_Test();
    void SpatialRelationCrossesPoint_False_Test();

    void SpatialRelationOverlapsPolygon_True_Test();
    void SpatialRelationOverlapsPolygon_False_Test();
    void SpatialRelationOverlapsLine_False_Test();
    void SpatialRelationOverlapsPoint_False_Test();



    void Buffer_Test();

};



#endif // FeatureOperations_H
