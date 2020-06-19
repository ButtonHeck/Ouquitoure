#pragma once

#include <QtCore/qglobal.h>

#if defined(APPCOLLECTION_LIBRARY)
#  define APPCOLLECTION_EXPORT Q_DECL_EXPORT
#else
#  define APPCOLLECTION_EXPORT Q_DECL_IMPORT
#endif
