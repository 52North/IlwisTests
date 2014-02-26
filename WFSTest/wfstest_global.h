#ifndef WFSTEST_GLOBAL_H
#define WFSTEST_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WFSTEST_LIBRARY)
#  define WFSTESTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WFSTESTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WFSTEST_GLOBAL_H
