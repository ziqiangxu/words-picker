#ifndef DLLTEST_GLOBAL_H
#define DLLTEST_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLTEST_LIBRARY)
#  define DLLTESTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DLLTESTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLTEST_GLOBAL_H
