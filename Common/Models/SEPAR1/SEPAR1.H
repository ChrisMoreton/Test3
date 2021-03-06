//================== SysCAD - Copyright Kenwalt (Pty) Ltd ===================
// $Nokeywords: $
//===========================================================================
// SysCAD Copyright Kenwalt (Pty) Ltd 1992

#ifndef  __Separ1_H
#define  __Separ1_H

#ifndef  __SC_DEFS_H
  #include "sc_defs.h"
#endif

#ifdef __Separ1_CPP
  #define DllImportExport DllExport
#elif !defined(Separ1)
  #define DllImportExport DllImport
#else
  #define DllImportExport
#endif

DllImportExport void ForceLoad_Separ1();

#undef DllImportExport

#endif
