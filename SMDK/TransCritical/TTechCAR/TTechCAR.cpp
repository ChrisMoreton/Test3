//================== SysCAD - Copyright Kenwalt (Pty) Ltd ===================
// $Nokeywords: $
//===========================================================================

#include "stdafx.h"
#define __TTECHCAR_CPP
#include "TTechCAR.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "scdmacros.h" 
#include "md_headers.h"
#ifdef GLADDY
#pragma LIBCOMMENT("..\\smdk\\Bin\\", "\\SMDK1" )
#pragma LIBCOMMENT("..\\smdk\\Bin\\", "\\scdlib" )
#else
#pragma LIBCOMMENT("..\\..\\Bin\\", "\\SMDK1" )
#pragma LIBCOMMENT("..\\..\\Bin\\", "\\scdlib" )
#endif
//===========================================================================

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:

   		if (!MakeVersionOK("TTechCAR.DLL", _MAKENAME, 
				   SCD_VERINFO_V0, SCD_VERINFO_V1, SCD_VERINFO_V2, SCD_VERINFO_V3))
        return FALSE;

		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

//===========================================================================

void ForceLoad_TTechCAR()
  {
  // Dummy Function to allow other libraries to force load this one
  }

//===========================================================================

extern "C" __declspec(dllexport) BOOL IsSMDKLibDLL()
  {
  return TRUE;
  }


//===========================================================================
