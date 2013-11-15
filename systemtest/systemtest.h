#ifndef LOADERTESTS_H
#define LOADERTESTS_H

#include <QObject>
#include "kernel.h"
namespace Ilwis {
    struct ExecutionContext;
    class SymbolTable;
}
class LoaderTests : public QObject
{
    Q_OBJECT
public:
    explicit LoaderTests(QObject *parent = 0);
    
private:
    void dump(const Ilwis::ExecutionContext& ctx, const Ilwis::SymbolTable &symtbl, quint64 tp);
    QSharedPointer<Ilwis::Kernel> _kernel;
private slots:
    void simpleLoaders();
    void gridCoverageDataAccess();
    void gdalConnector();
    void coordTransformations();
    void featureData();
    void domainandtableAccess();
    void accessCatalog();
    void scriptExecution();
    void indexDomains();
    void thematicDomains();
    void masterCatalogAdmin();
    void tabcalc();

};

#endif // LOADERTESTS_H
