//================== SysCAD - Copyright Kenwalt (Pty) Ltd ===================
// $Nokeywords: $
//===========================================================================

#include "stdafx.h"
#define __DEMOUSR_CPP
#include "DemoUsr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "scdmacros.h" 
#include "md_headers.h" 
//#pragma comment( lib, LIBCOMMENTHD "..\\..\\Bin\\Rls\\DevLib.lib")
//#pragma comment( lib, LIBCOMMENTHD "..\\..\\Bin\\Rls\\scdlib.lib")
//#pragma comment( lib, LIBCOMMENTHD "..\\..\\Bin\\Rls\\scexec.lib")
#pragma LIBCOMMENT("..\\..\\Bin\\", "\\DevLib" )
#pragma LIBCOMMENT("..\\..\\Bin\\", "\\scdlib" )
#pragma LIBCOMMENT("..\\..\\Bin\\", "\\scexec" )

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

   		/*if (!MakeVersionOK("DemoUsr.DLL", _MAKENAME, SCD_VERINFO_V0, SCD_VERINFO_V1, SCD_VERINFO_V2, SCD_VERINFO_V3))
        return FALSE;*/

		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

//===========================================================================

extern "C" __declspec(dllexport) BOOL IsSMDKLibDLL()
  {
  return TRUE;
  }


//===========================================================================

