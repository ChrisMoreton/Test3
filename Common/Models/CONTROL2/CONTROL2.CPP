// Control2.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#define __Control2_CPP

#include "sc_defs.h"
#include "scdver.h"
#include "Control2.h"
#define MATHAND1
#include "Models.h"
#include "sfe_srvr.h"

//===========================================================================
//
//                    Visual C++ Stuff
//
//===========================================================================

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE Control2DLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE1("Control2.DLL Initializing %08x!\n", hInstance);

		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(Control2DLL, hInstance))
      return 0;

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(Control2DLL);

		if (!MakeVersionOK("Control2.DLL", _MAKENAME, SCD_VERINFO_V0, SCD_VERINFO_V1, SCD_VERINFO_V2, SCD_VERINFO_V3))
      return 0;

  //  ForceLoadModelLibrary();

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Control2.DLL Terminating!\n");
		AfxTermExtensionModule(Control2DLL);
	}
	return 1;   // ok
}

//---------------------------------------------------------------------------

#define DLLEXPORT __declspec( dllexport ) 

//---------------------------------------------------------------------------

extern "C" DLLEXPORT BOOL FilterDllMsg(LPMSG lpMsg)
  {
  return AfxGetApp()->PreTranslateMessage(lpMsg);
  }

//---------------------------------------------------------------------------

extern "C" DLLEXPORT void ProcessDllIdle()
  {
  // flush it all at once
  long lCount = 0;
  while (AfxGetApp()->OnIdle(lCount))
    lCount++;
  }

//---------------------------------------------------------------------------

extern "C" DLLEXPORT BOOL IsFlowLibDLL()
  {
  return TRUE;
  }

//---------------------------------------------------------------------------

extern "C" DLLEXPORT BOOL GetDLLInfo(MDLLInfo* pDLLInfo)
  {
  pDLLInfo->iPriority = 4;
  pDLLInfo->sName = "Control2";
  //pDLLInfo->AddDependentDLL("FlwLib");
  pDLLInfo->AddDependentDLL("MatHand1");
  return TRUE;
  }

//---------------------------------------------------------------------------

extern "C" DLLEXPORT CMdlCfgBase* GetCfgPropPg(int iPage, CMdlCfgSheet * pSheet)
  {
  return NULL;
  };

//===========================================================================
//
//
//
//===========================================================================

void ForceLoad_Control2()
  {
  // Dummy Function to allow other libraries to force load this one
  }

//===========================================================================
//
//
//
//===========================================================================
