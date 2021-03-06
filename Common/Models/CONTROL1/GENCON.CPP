//================== SysCAD - Copyright Kenwalt (Pty) Ltd ===================
// $Nokeywords: $
//===========================================================================

#include "stdafx.h"
#include "sc_defs.h"
#include "pgm_e.h"
#include "gencon.h"
#include "scd_wm.h"
//#include "optoff.h"

// To stop nagging LoaderLock assert issues, turn off Managed Debugging Assistants->LoaderLock from the Debug->Exceptions menu.

#if WithPGMTagChange
#include < fstream >
#include <regex> 
//#include <RegexWrap.h>
#pragma LIBCOMMENT("..\\..\\scd\\RegexWrap\\", "\\RegexWrap" )
#endif
//==========================================================================
//
//  General Model Controller
//
//==========================================================================
/*#D:#T:General Controller                       
#X:#h<General Description>#nThis is a general controller model. It allows
simple or complex programs (PGM's) to be written in a text editor. These 
programs are loaded and compiled, any errors are reported. The program code
(PGM) is executed once at the end of every SysCAD iteration. PGM's are commonly
used to impliment or simulate control stratergies in a flowsheet. See separate
documentation on PGM's for more details.#n#n
When a PGM file is loaded, any errors encountered are reported. The use of tags
within a PGM are not checked when a PGM file is loaded and compiled. They are 
only checked when the 'Check Tags' button is pressed or when the solver starts.
The solver will not start if the PGM contains invalid tags. Tags are not
checked if the PGM is off.
#n#n
#n#h<Inputs and Outputs>#nThere are NO inputs or outputs that can be connected
to this unit.
#n#n
#h<Variables to be supplied by the user>#n
#i<PGM_Name> : The name of the program file that contains the PGM code. The file
can be entered in any text editor, and must have the file extension 'pgm'.
The file path does not need to be specified if the program file is in the
project directory or the data_lib directory for the current model configuration.
See documentation on PGM codeing for more details.#n
#i<On> : On or off. If on, the PGM code is executed each iteration, otherwise it is ignored.#n
#i<PGM variable list> : Any number of PGM variables that have been made accessable
from the PGM code.#n
#n#n
#h<Associated variables>#n
#i<State> : The state of the PGM file once a load has been attempted.#n
#i<Msg_1..Msg_4> : These message lines are used to report PGM compile errors, or
errors while PGM code is executing.#n
#n#n
#h<Buttons>#n
#i<Edit PGM> : This allows you to edit the specified PGM file.#n
#i<Reload PGM> : This reloads and recompiles the PGM code. Use this after changes to
the PGM code have been made and saved.#n
#i<Check Tags> : This can only be used while SysCAD is not solving or running. It is used
to check all the tags used by the pgm and their engineering units. This is done
automatically when the solver starts, so you do not need to use this button.#n
#i<Debug PGM> : This is an advanced feature that must be used with caution. It is used
to step through PGM code as it is being executed.#n
#n
#n#h<Other>#n
Default model prefix:GC#n
Short name:GControl#n
Model type:Unit#n
#G:Units
*/

static double Drw_GControl[] =
{
	DD_Poly, -3.2,-3.2, -3.2,3.2, 3.2,3.2, 3.2,-3.2, -3.2,-3.2,
	DD_Poly, -3.2,0, 3.2,0,
	DD_Poly, 0,-3.2, 0,3.2,
	DD_TagPos, 0, -6.7,
	DD_End
};

IMPLEMENT_MODELUNIT(GControl, "GControl", "", Drw_GControl, "Control", "GC", TOC_ALL|TOC_DYNAMICFLOW|TOC_GRP_GENERAL|TOC_STD_KENWALT, 
										"Control:General",
										"General Controller (PLC Style) model.")

										GControl::GControl(pTagObjClass pClass_, pchar TagIn, pTaggedObject pAttach, TagObjAttachment eAttach) :
FlwNode(pClass_, TagIn, pAttach, eAttach),
PgmMngr(/*this,*/ "PGM")                             
{
	fHasFiles=1;
	m_bMustInit = 0;
	m_bIterOne = 0;
	m_bMustTerm = 0;
	iIterCnt = 0;
	bJustLoaded = 0;
	bEmpty = 0;
	bPreset = 0;
	bAutoReload = True;
	bReloadReqd = False;
	bWithDBG = False;
	AttachClassInfo(nc_Control, NULL, &NullFlwGroup);
	SetActiveOptions(true, true);
	sPGMName = "";
	bOn = 1;
	bEncrypt = 0;
	m_VarData = NULL;
	m_nMaxVarData = 0;
	SetMaxVarData(32L);

	for (int incs=0; incs<TP_MaxTtlIncludeFiles; incs++)
	{
		m_hProcess[incs] = NULL;
		m_dwProcessId[incs] = 0;
		m_EditTime[incs].dwLowDateTime=0;
		m_EditTime[incs].dwHighDateTime=0; 
	}

#if WithPGMWatches
	bWatchesOn = (PrjFileVerNo()<22);
	for (int i=0; i<MaxPGMWatch; i++)
	{
		Watch[i].S="";
		Watch[i].pV=NULL;
	}
#endif
}

//--------------------------------------------------------------------------

GControl::~GControl()
{
	SetMaxVarData(0);
}

//--------------------------------------------------------------------------

void GControl::SetMaxVarData(long NewSize)
{
	CSingleLock Lock(&m_VarDataSect, true);
	if (NewSize!=m_nMaxVarData)
	{
		GCVar** NewVarData = NULL;
		if (NewSize>0)
		{
			NewVarData = new pGCVar[NewSize];
			for (int i=0; (i<NewSize && i<m_nMaxVarData); i++)
				NewVarData[i] = m_VarData[i];
		}
		if (m_VarData)
			delete []m_VarData;
		m_VarData = NewVarData;
		m_nMaxVarData = NewSize;
	}
}

//--------------------------------------------------------------------------

void GControl::ResetData(flag Complete)
{
}

//--------------------------------------------------------------------------

const int MaxPGMArrayWatch     = 512;

const word idmPGMName          = ModelXID(1000);
const word idmPGMPath          = ModelXID(1001);
const word idmEditPGMBtn       = ModelXID(1002);
const word idmReloadPGMBtn     = ModelXID(1003);
const word idmBrowsePGMBtn     = ModelXID(1004);
const word idmDebugPGMBtn      = ModelXID(1005);
const word idmTagCheckBtn      = ModelXID(1006);
const word idmWatchesOn        = ModelXID(1007);
const word idmEditFileBtn      = ModelXID(1010);
const word idmEditFileBtnLast  = ModelXID(1090);
const word idmEditFileNameNew  = ModelXID(1091);
const word idmEditFileBtnNew   = ModelXID(1092);

const word idmPGMWatch         = ModelXID(1100);                    // Keep MaxPGMWatch free after this
const word idmPGMArrayWatch    = idmPGMWatch+MaxPGMWatch; // Keep MaxPGMArrayWatch free after this
const word idmPGMData          = idmPGMArrayWatch+MaxPGMArrayWatch; // Keep everything free after this

//--------------------------------------------------------------------------

void GControl::CountWatchedVars(pGCVar VarList, int & TagCount, int & LineCount, int & PageCount)
{
	pGCVar pVar = VarList;
	while (pVar)
	{
		if (pVar->Watched())
		{
			if (pVar->WhatAmI()==VarLabel)
			{
				if (pVar->m_flags & VarPageLabel)
					PageCount++;
				else
					LineCount++;
			}
			else
			{
				TagCount++;
				LineCount++;
			}
		}
		if (pVar->WhatAmI()==VarClass && !(pVar->m_flags & VarClassDefn))
			CountWatchedVars(((pGCClassVar)pVar)->m_pVarList, TagCount, LineCount, PageCount);
		pVar = pVar->Next();
	}
}

//--------------------------------------------------------------------------

void GControl::DDBAddWatchedVars(DataDefnBlk & DDB, pchar pHdTag, pGCVar VarList, int Lvl, int &nPg, int &nOnPg, flag ForceNewPage, int MaxPerPage, bool UserPages, int &SubPg, char PgPrefix)
{
	Strng Tag;
	char HdTag[512];
	strcpy(HdTag, pHdTag); 
	if (strlen(pHdTag)>0) 
		strcat(HdTag, ".");

	pGCVar pVar = VarList;
	while (pVar)
	{
		//dbgpln("WV:%s", pVar->Name() ? pVar->Name() :"??") ;   
		if (pVar->Watched())
		{
			CSingleLock Lock(&m_VarDataSect, true);
			int nUseData = -1;
			if (pVar->WhatAmI()!=VarLabel)
			{
				nUseData = m_nVarData;
				m_nVarData++;
				if (m_nVarData>=m_nMaxVarData)
					SetMaxVarData(m_nMaxVarData+16);
				m_VarData[nUseData] = pVar;
			}
			char S[256];
			if (ForceNewPage || (Lvl==0 && nOnPg>MaxPerPage && pVar->WhatAmI()!=VarLabel))
			{
				if (UserPages)
				{
					SubPg++;
					sprintf(S, "%c%i", PgPrefix, SubPg);
				}
				else
				{
					sprintf(S, "Data:%i", nPg+1);
				}
				ForceNewPage = 0;
				DDB.Page(S, DDB_RqdPage);
				nOnPg = 0;
				nPg++;
			}
			nOnPg++;

			if (pVar->WhatAmI()==VarLabel)
			{
				char LabelBuff[512];
				if (pVar->m_flags & VarPageLabel)
				{
					DDB.Page(pVar->GetStrVal(LabelBuff), DDB_RqdPage);
					SubPg = 1;
					PgPrefix = LabelBuff[0];
					nOnPg = 0;
					nPg++;
				}
				else
				{
					DDB.Text(pVar->GetStrVal(LabelBuff)); 
				}
			}
			else
			{
				Tag.Set("%s%s", HdTag, pVar->Name());
				//const DDEF_Flags flgs = ((!pVar->ReadOnly() ? 0 : isParm) | noFile);
				const DDEF_Flags flgs = ((pVar->ReadOnly() ? 0 : isParm) | noFile);
				if (pVar->m_pWatchInfo)
				{
					switch (pVar->WhatAmI())
					{
					case VarTag   :
					case VarDouble: 
						DDB.Double(Tag(), "", pVar->CnvIndex(), pVar->CnvTxt(), idmPGMData+nUseData, this, flgs|NAN_OK);
						DDB.Range(pVar->m_pWatchInfo->dMin, pVar->m_pWatchInfo->dMax);
						DDB.Description(pVar->m_pWatchInfo->sDesc()); 
						break;
					case VarLong  :
					case VarByte  : 
						DDB.Long  (Tag(), "", pVar->CnvIndex(), pVar->CnvTxt(), idmPGMData+nUseData, this, flgs);
						DDB.Range((long)pVar->m_pWatchInfo->dMin, (long)pVar->m_pWatchInfo->dMax);
						DDB.Description(pVar->m_pWatchInfo->sDesc()); 
						break;
					case VarBit   : 
						DDB.Bool  (Tag(), "", pVar->CnvIndex(), pVar->CnvTxt(), idmPGMData+nUseData, this, flgs);
						DDB.Range((byte)pVar->m_pWatchInfo->dMin, (byte)pVar->m_pWatchInfo->dMax);
						DDB.Description(pVar->m_pWatchInfo->sDesc()); 
						break;
					case VarStr   : 
						DDB.String(Tag(), "", DC_, "", idmPGMData+nUseData, this, flgs); 
						break;
					}
				}
				else
				{
					switch(pVar->WhatAmI())
					{
					case VarTag   :
					case VarDouble: 
						DDB.Double(Tag(), "", pVar->CnvIndex(), pVar->CnvTxt(), idmPGMData+nUseData, this, flgs|NAN_OK);
						break;
					case VarLong  :
					case VarByte  : 
						DDB.Long  (Tag(), "", pVar->CnvIndex(), pVar->CnvTxt(), idmPGMData+nUseData, this, flgs);
						break;
					case VarBit   : 
						DDB.Bool  (Tag(), "", pVar->CnvIndex(), pVar->CnvTxt(), idmPGMData+nUseData, this, flgs);
						break;
					case VarStr   : 
						DDB.String(Tag(), "", DC_, "", idmPGMData+nUseData, this, flgs); 
						break;
					}
				}
			}
		}

		if (pVar->WhatAmI()==VarClass && !(pVar->m_flags & VarClassDefn))
		{
			Tag.Set("%s%s", HdTag, pVar->Name());
			flag ForcePg = (Lvl==0 && nOnPg>MaxPerPage);
			DDBAddWatchedVars(DDB, Tag(), ((pGCClassVar)pVar)->m_pVarList, Lvl+1, nPg, nOnPg, ForcePg, MaxPerPage, UserPages, SubPg, PgPrefix);
		}
		pVar = pVar->Next();
	}
}

//--------------------------------------------------------------------------

void GControl::DDBAddArrayWatchedVars(DataDefnBlk & DDB, int &nPg, int MaxPerPage)
{
	Strng Tag;
	int nOnPg = 0;
	for (int i=0; i<PgmMngr.m_ExtraWatchArray.GetSize() && i<MaxPGMArrayWatch; i++)
	{
		if (nOnPg>MaxPerPage)
		{
			char S[8];
			sprintf(S, "D%i", nPg+1);
			DDB.Page(S, DDB_RqdPage);
			nOnPg = 0;
			nPg++;
		}
		nOnPg++;
		GCArrayWatch* pAW = PgmMngr.m_ExtraWatchArray[i];
		DDB.Double(pAW->m_sTg(), "", DC_, "", idmPGMArrayWatch+i, this, (pAW->m_bReadOnly ? 0 : isParm)|NAN_OK|noFile);
	}
}

//--------------------------------------------------------------------------

void GControl::BuildDataDefn(DataDefnBlk & DDB)
{
	DDB.BeginStruct(this, "GControl", NULL, DDB_NoPage);
	DDB.Text(" ");
	DDB.String("PGM_Name",     "", DC_,    "",    idmPGMName,               this, isParm|SetOnChange);
	DDB.String("PGM_Path",     "", DC_,    "",    idmPGMPath,               this, noFileAtAll);
	DDB.CheckBoxBtn("On",      "", DC_,    "",    &bOn,                     this, isParmStopped, DDBYesNo);
	//DDB.CheckBoxBtn("Encrypt", "", DC_,    "",    &bEncrypt,                this, isParmStopped, DDBYesNo);
	DDB.CheckBoxBtn("AutoReload", "", DC_, "",    &bAutoReload,             this, isParm, DDBOnOff);
	DDB.String("State",        "", DC_,    "",    &PgmMngr.m_StateLine[0],  this, noSnap|noFile);
	DDB.Text("Error:");
	DDB.String("Msg_1",        "", DC_,    "",    &PgmMngr.m_StateLine[1],  this, noSnap|noFile);
	DDB.String("Msg_2",        "", DC_,    "",    &PgmMngr.m_StateLine[2],  this, noSnap|noFile);
	DDB.String("Msg_3",        "", DC_,    "",    &PgmMngr.m_StateLine[3],  this, noSnap|noFile);
	DDB.String("Msg_4",        "", DC_,    "",    &PgmMngr.m_StateLine[4],  this, noSnap|noFile);
	DDB.Text(" ");
	// These buttons should follow the PGMName
	if (!bEncrypt)
		DDB.Button("Edit_PGM",     "", DC_,    "",    idmEditPGMBtn,            this, isParm);
	DDB.Button("Reload_PGM",   "", DC_,    "",    idmReloadPGMBtn,          this, isParm);
	if (!bEncrypt)
		DDB.Button("Browse_PGM",   "", DC_,    "",    idmBrowsePGMBtn,          this, isParm);
	DDB.Button("Check_tags",   "", DC_,    "",    idmTagCheckBtn,           this, isParmStopped);

	// #744 Allow editting of Includes
	if (DDB.ForView())
	{
		DDB.Text("");
		for (int i=0; i<PgmMngr.m_FilesUsed.GetLen(); i++)
		{
			Strng Fn, Tg;
			Fn.FnName(PgmMngr.m_FilesUsed[i]());
			Strng Sym("Edit_");
			Sym += Fn;
			if (i==0)
				Tg = "Edit Main pgm";
			else
				Tg.Set("Edit include %d", i);
			DDB.Button(Tg(),         Sym(),   DC_,    "",    idmEditFileBtn+i,            this, isParm);
		}
		DDB.String("NewInclude",   "",       DC_,      "",    idmEditFileNameNew,            this, isParm|SetOnChange|noFileAtAll);
		if (m_sEditFileNameNew.GetLength()>0)
			DDB.Button(m_sEditFileNameNew(),  "Create", DC_,    "",    idmEditFileBtnNew,            this, isParm);
	}

#if WithPGMWatches
	DDB.Text(" ");
	DDB.CheckBoxBtn("WatchesOn", "", DC_,   "",    idmWatchesOn,            this, isParm, DDBYesNo);
#endif
	DDB.Text(" ");
	//DDB.Button("Debug_PGM",    "", DC_,    "",    idmDebugPGMBtn,           this, isParm);
	//DDB.Text(" ");

	//look ahead to see how many tags need to be display & how many tab pages..
	//TODO: These calcs need improving for user defined pages, etc
	m_nVarData = 0;
	int nPg = 0;
	int nOnPg = 20;
	int nSubPg = 0;
	int nTtlCnt = 0;
	int nLineCnt = 0;
	int nPgCnt = 0;
	CountWatchedVars(PgmMngr.m_pVarList, nTtlCnt, nLineCnt, nPgCnt);
	SetMaxVarData(Max(32, nTtlCnt));
	int MaxPerPage = 30;
	if (nPgCnt>0)
	{//user defined pages, increase max tags per page
		nOnPg = 30;
		MaxPerPage = Max(50, (int)(nTtlCnt/(MaxAccWndTabPages-1)));
	}
	else
	{//old style, no user pages
		MaxPerPage = Max(30, (int)(nTtlCnt/(MaxAccWndTabPages-1)));
	}
	//now add the watched variables..
	DDBAddWatchedVars(DDB, "", PgmMngr.m_pVarList, 0, nPg, nOnPg, 0, MaxPerPage, (nPgCnt>0), nSubPg, 'D');

	//now add 'special' watched array variables..
	if (PgmMngr.m_ExtraWatchArray.GetSize()>0)
	{
		nPg = 0;
		DDB.Page("D0", DDB_RqdPage);
		DDBAddArrayWatchedVars(DDB, nPg, MaxPerPage);
	}

#if WithPGMWatches
	if (bWatchesOn)
	{
		if (DDB.BeginArray(this, "W", "GCWatch", MaxPGMWatch))
		{
			for (int i=0; i<MaxPGMWatch; i++)
				if (DDB.BeginElement(this, i))
				{
					char S[256];
					if (i%30==0)
					{
						sprintf(S, "W%i..%i",i+1,i+30);
						DDB.Page(S, DDB_RqdPage);
					}
					DDB.String("W",     "",     DC_,    "",   idmPGMWatch+i, this, isParm);
				}
		}
		DDB.EndArray();
	}
#endif
	POSITION Pos=m_BuildResults.m_BadTags.GetHeadPosition();
	if (Pos)
	{
		DDB.Text(" ");
		while (Pos)
		{
			CXRefBuildResult & R=m_BuildResults.m_BadTags.GetNext(Pos);
			CString S(R.m_sTag);
			if (R.m_dwReason & FXR_Found           ) S+= " ";
			if (R.m_dwReason & FXR_NotFound        ) S+= " Not Found";
			if (R.m_dwReason & FXR_NotParam        ) S+= " Not Parameter";
			if (R.m_dwReason & FXR_BadValue        ) S+= " Not Number or String";
			if (R.m_dwReason & FXR_ParamStopped    ) S+= " Parameter Stopped";
			if (R.m_dwReason & FXR_BadCnv          ) S+= " Bad Cnv";
			if (R.m_dwReason & FXR_DynTag          ) S+= " DynTag";
			if (R.m_dwReason & FXR_DynTagMissing   ) S+= " DynTag Missing";
			if (R.m_dwReason & FXR_DynTagNeverFound) S+= " DynTag Never Found";
			DDB.Text((LPTSTR)(LPCTSTR)S);
		}
	}
	DDB.EndStruct();
}

//--------------------------------------------------------------------------

flag GControl::LoadPGM(char * pPGMName, flag WithDebug)
{
	CWaitCursor Wait;
	bJustLoaded = 1;
	bWithDBG = WithDebug;
	bReloadReqd = false;
	sPGMName = pPGMName;
	sPGMName.LRTrim();

	Strng ss;
	if (sPGMName())
	{
		ss.FnDrivePathName(sPGMName());
		ss.FnCheckExtension("pgm");
		ss.FnSearchExpand(NULL, AF_All|AF_BackupFiles);

		if (!FileExists(ss()))
		{
			//let's see if the pgm file has been moved to the "Controls" sub folder...
			Strng Tmp(ss);
			Tmp.FnNameExt();
			Strng Tmp2 = FnDefaultControlsFolder();
			Tmp2 += Tmp;
			if (FileExists(Tmp2()))
			{
				ss = Tmp2();
				LogNote(FullObjTag(), 0, "PGM file (%s) folder location changed to '\\Controls'.", Tmp());
			}
		}
		sPGMName.FnContract(ss());
	}

	if (WithDebug)
		bReloadReqd=!PgmMngr.Debug(AF_All|AF_BackupFiles, ss(), this, DefGenConSet);
	else
		bReloadReqd=!PgmMngr.Load(AF_All|AF_BackupFiles, ss(), this, DefGenConSet);

	//long Ret = UpdateXRefLists(); 
	MyTagsHaveChanged();

#if WithPGMWatches
	for (int i=0; i<MaxPGMWatch; i++)
		Watch[i].pV=NULL;
#endif
	return True;
}

//--------------------------------------------------------------------------

LPCSTR DefaultPGM =
";--- SysCAD General Controller (PGM) program logic file ---\n"
";--- See http://help.syscad.net/index.php/PGMs for online documentation ---\n"
"\n"
";--- variable declarations ---\n"
"\n"
"\n"
"if (OnInitialise)\n"
"  ;--- place logic here for execution before first iteration --- (use SetDynTag in OnInitialise)\n"
"  \n"
"else\n"
"  ;--- place logic here for execution each iteration ---\n"
"  \n"
"endif\n"
"\n"
"$ ; --- end of file ---\n"
"\n";
const int DefaultPGMLen = strlen(DefaultPGM);

LPCSTR DefaultPGMInc =
";--- SysCAD General Controller (PGM) include file ---\n"
";--- referenced in main pgm file with '>>'\n"
"\n"
";--- place functions or classes here ---\n"
"\n"
"\n"
"\n"
"; --- end of include file (Note: $ must NOT be used) ---\n"
"\n";
const int DefaultPGMIncLen = strlen(DefaultPGMInc);

void CreateDefault(LPCSTR Tag, LPCSTR Name, LPCSTR DefaultPGM, int DefaultPGMLen, Strng &FullFileName)
{
	Strng PgmCfg(CfgFiles(),      Name);
	Strng PgmBase(BaseCfgFiles(), Name);
	if (FileExists(PgmCfg()))
	{
		if (!CopyFile(PgmCfg(), FullFileName(), true))
			LogError(Tag, 0, "FileCopy failed '%s' to %s'", PgmCfg(), FullFileName());
	}
	else if (FileExists(PgmBase()))
	{
		if (!CopyFile(PgmBase(), FullFileName(), true))
			LogError(Tag, 0, "FileCopy failed '%s' to %s'", PgmBase(), FullFileName());
	}
	else
	{
		FILE* f = fopen(FullFileName(), "wt");
		if (f)
		{
			fwrite(DefaultPGM, sizeof(char), DefaultPGMLen, f);
			fclose(f);
		}
	}
}

//--------------------------------------------------------------------------

flag GControl::DataXchg(DataChangeBlk & DCB)
{
	if (FlwNode::DataXchg(DCB))
		return 1;
	switch (DCB.lHandle)
	{
	case idmBrowsePGMBtn:
		if (DCB.rB && (*DCB.rB!=0))
		{
			Strng Ext("*.pgm");
			Strng Dir = FnDefaultControlsFolder();
			CSCDFileDialog Dlg(true, NULL, Ext(), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_SHAREAWARE, "PGM Files (*.PGM)|*.PGM||");
			Dlg.m_ofn.lpstrInitialDir = Dir();
			Dlg.m_ofn.lpstrTitle = "Program File";
			HWND H=::GetActiveWindow();
			if (Dlg.DoModal()==IDOK)
				sPGMName=Dlg.GetPathName();
			::SetActiveWindow(H);
			DCB.B=0;
			sPGMName.FnContract();
			bReloadReqd=true;
			if (bAutoReload)
				LoadPGM(sPGMName(), bWithDBG);
			//        ValidateData(ValidateDataBlk & VDB);
		}
		DCB.B=0;
		return 1;
	case idmReloadPGMBtn:
		if (DCB.rB && (*DCB.rB!=0))
			LoadPGM(sPGMName(), False);
		DCB.B=0;
		return 1;
	case idmEditPGMBtn:
		if (DCB.rB && (*DCB.rB!=0))
		{
			m_EditTime[0].dwLowDateTime=0;
			m_EditTime[0].dwHighDateTime=0; 
			if (sPGMName.Length()==0)
			{
				sPGMName=FnDefaultControlsFolder();
				sPGMName+=Tag();
				sPGMName+=".pgm";
				if (FileExists(sPGMName()))
				{
					LoadPGM(sPGMName(), bWithDBG);
				}
			}
			Strng FileName(sPGMName());
			Strng FullFilename;
			int RetCode = DCB.DoEditBtn(m_hProcess[0], m_dwProcessId[0], "", FileName(), "pgm", &FullFilename, true, FnDefaultControlsFolder()());
			if (RetCode==-1)
			{
				CreateDefault(Tag(), "Template.pgm", DefaultPGM, DefaultPGMLen, FullFilename);

				sPGMName = FullFilename();
				sPGMName.FnContract();
				FileName = sPGMName();
				RetCode = DCB.DoEditBtn(m_hProcess[0], m_dwProcessId[0], "", FileName(), "pgm");
			}
			if (RetCode==0)
			{
				SYSTEMTIME ST;
				GetSystemTime(&ST);
				SystemTimeToFileTime(&ST, &m_EditTime[0]);
			}
		}
		DCB.B=0;
		return 1;
	case idmEditFileNameNew:
		if (DCB.rpC)
		{
			m_sEditFileNameNew=DCB.rpC;
			m_sEditFileNameNew.FnName();
			//m_sEditFileNameNew.FnName();
		}
		DCB.pC=m_sEditFileNameNew();
		return 1;
	case idmEditFileBtnNew:
		if (DCB.rB && (*DCB.rB!=0))
		{
			Strng FileName=FnDefaultControlsFolder();

			HANDLE   hNewProcess=NULL;
			DWORD    dwNewProcessId;

			FileName+=m_sEditFileNameNew;
			FileName+=".pgm";
			Strng FullFilename;
			int RetCode = DCB.DoEditBtn(hNewProcess, dwNewProcessId, "", FileName(), "pgm", &FullFilename, true);
			if (RetCode==-1)
			{
				CreateDefault(Tag(), "Template.Inc.pgm", DefaultPGMInc, DefaultPGMIncLen, FullFilename);
				RetCode = DCB.DoEditBtn(hNewProcess, dwNewProcessId, "", FileName(), "pgm");
			}
			m_sEditFileNameNew="";
		}
		DCB.B=0;
		return 1;
	case idmDebugPGMBtn:
		if (DCB.rB && (*DCB.rB!=0))
			LoadPGM(sPGMName(), True);
		DCB.B=0;
		return 1;
	case idmTagCheckBtn:
		if (DCB.rB && (*DCB.rB!=0))
		{
			if (PreStartCheck())
				LogNote(Tag(), 0, "No bad external tag references");
			m_bIterOne = 0;
		}
		DCB.B=0;
		return 1;

	case idmPGMName:
		if (DCB.rpC!=NULL)
		{
			// Dont Set if coming from snapshot
			Strng File0, Path0;
			File0.FnNameExt(DCB.rpC);
			Path0.FnDrivePath(DCB.rpC);

			Strng File1, Path1;
			File1.FnNameExt(sPGMName());
			Path1.FnDrivePath(sPGMName());

			Strng S;
			S=Path0.Length()>0 ? Path0() : Path1();
			S+=File0.Length()>0 ? File0() : File1();

			LoadPGM(S(), False);
		}
		if (DCB.ForView())
		{
			sPGMFile.FnNameExt(sPGMName());
			DCB.pC= sPGMFile();
		}
		else
			DCB.pC= sPGMName();
		return 1;

	case idmPGMPath:
		sPGMPath.FnDrivePath(sPGMName());
		if (SymbolicPaths())
			sPGMPath.FnContract();
		else
			sPGMPath.FnExpand();
		DCB.pC= sPGMPath();
		return 1;

#if WithPGMWatches
	case idmWatchesOn:
		if (DCB.rB)
			bWatchesOn=*DCB.rB;
		DCB.B=bWatchesOn;
		return 1;
#endif
	default:
		if (DCB.lHandle>=idmEditFileBtn && DCB.lHandle<=idmEditFileBtnLast)
		{
			if (DCB.rB && (*DCB.rB!=0))
			{
				const int inc=DCB.lHandle-idmEditFileBtn;
				Strng FileName=(inc==0 ? sPGMName() : PgmMngr.m_FilesUsed[inc]);
				Strng FullFilename;
				int RetCode = DCB.DoEditBtn(m_hProcess[inc], m_dwProcessId[inc], "", FileName(), "pgm", &FullFilename, true);
				if (RetCode==-1)
				{
					bool IsMain = (DCB.lHandle==idmEditFileBtn);

					if (IsMain)
						CreateDefault(Tag(), "Template.pgm", DefaultPGM, DefaultPGMLen, FullFilename);
					else
						CreateDefault(Tag(), "Template.Inc.pgm", DefaultPGMInc, DefaultPGMIncLen, FullFilename);

					RetCode = DCB.DoEditBtn(m_hProcess[inc], m_dwProcessId[inc], "", FileName(), "pgm");
				}
				//if (RetCode==0)
				//  {
				//  SYSTEMTIME ST;
				//  GetSystemTime(&ST);
				//  SystemTimeToFileTime(&ST, &EditTime);
				//  }
			}
			DCB.B=0;
			return 1;
		}
#if WithPGMWatches
		if (DCB.lHandle>=idmPGMWatch && DCB.lHandle<idmPGMWatch+MaxPGMWatch)
		{         
			int i=DCB.lHandle-idmPGMWatch;
			rStrng W=Watch[i].S;
			if (DCB.rpC)
			{
				pGCVar pV=Watch[i].pV;
				W=DCB.rpC;
				pchar pEq=W.XStrChr('=');
				if (pEq)
					W.SetLength(pEq-W());
				W.Trim();
				if (W.Length()>0)
				{
					pV=PgmMngr.m_pVarList->Find(W());
					W+="=";
					if (!pV)
						W+=" Not Found";
				}
				else
					pV=NULL;
				//Watch[i].S=W;
				if (pV!=Watch[i].pV)
				{
					//if (Watch[i].pV)
					//  Watch[i].pV->m_flags=Watch[i].pV->m_flags & ~VarManWatch;
					StructureChanged(this);
					Watch[i].pV=pV;
					//if (Watch[i].pV)
					//  Watch[i].pV->m_flags=Watch[i].pV->m_flags | VarManWatch;
				}
			}

			if (Watch[i].pV)
			{
				//W=Watch[i].S;
				pchar pEq=W.XStrChr('=');
				if (pEq)
				{
					W.SetLength(pEq-W()+1);
					switch(Watch[i].pV->WhatAmI())
					{
					case VarDouble: W+=ftoa(Watch[i].pV->getD()); break;
					case VarLong  : W+=ltoa(Watch[i].pV->getL()); break;
					case VarByte  : W+=ltoa(Watch[i].pV->getL()); break;
					case VarBit   : W+=ltoa(Watch[i].pV->getL()); break;
					case VarTag   : W+=ftoa(Watch[i].pV->getD()); break;
					case VarStr   : W+=((pGCStrVar)(Watch[i].pV))->getS(); break;
					default : W+= "?";  break;
					}
				}
			}
			DCB.pC=W();
			return True;
		}
		else 
#endif
			if (DCB.lHandle>=idmPGMData && DCB.lHandle<idmPGMData+m_nVarData)
			{
				GCVar* pV = m_VarData[DCB.lHandle-idmPGMData];
				if (pV)
				{
					if (pV->m_pCnvInfo)
					{
						switch(pV->WhatAmI())
						{
						case VarDouble: if (DCB.rD) pV->set(Cnvs[pV->m_pCnvInfo->Index()]->Human(*DCB.rD, pV->m_pCnvInfo->Text())); 
							DCB.D=Cnvs[pV->m_pCnvInfo->Index()]->Normal(pV->getD(), pV->m_pCnvInfo->Text()); return True;
						case VarLong  : if (DCB.rL) pV->set(Cnvs[pV->m_pCnvInfo->Index()]->Human(*DCB.rL, pV->m_pCnvInfo->Text()));
							DCB.L=(long)Cnvs[pV->m_pCnvInfo->Index()]->Normal(pV->getL(), pV->m_pCnvInfo->Text()); return True;
						case VarByte  : if (DCB.rL) pV->set(*DCB.rL); DCB.L=pV->getL(); return True;
						case VarBit   : if (DCB.rB) pV->set(*DCB.rB); DCB.B=pV->getB(); return True;
						case VarTag   : if (DCB.rD) pV->set(*DCB.rD); DCB.D=pV->getD(); return True;
						case VarStr   : if (DCB.rpC) ((pGCStrVar)pV)->set(DCB.rpC); DCB.pC=((pGCStrVar)pV)->getS(); return True;
						}
					}
					else
					{
						switch(pV->WhatAmI())
						{
						case VarDouble: if (DCB.rD) pV->set(*DCB.rD); DCB.D=pV->getD(); return True;
						case VarLong  : if (DCB.rL) pV->set(*DCB.rL); DCB.L=pV->getL(); return True;
						case VarByte  : if (DCB.rL) pV->set(*DCB.rL); DCB.L=pV->getL(); return True;
						case VarBit   : if (DCB.rB) pV->set(*DCB.rB); DCB.B=pV->getB(); return True;
						case VarTag   : if (DCB.rD) pV->set(*DCB.rD); DCB.D=pV->getD(); return True;
						case VarStr   : if (DCB.rpC) ((pGCStrVar)pV)->set(DCB.rpC); DCB.pC=((pGCStrVar)pV)->getS(); return True;
						}
					}
					return True;
				}
			}
			else if (DCB.lHandle>=idmPGMArrayWatch && DCB.lHandle<idmPGMArrayWatch+PgmMngr.m_ExtraWatchArray.GetSize())
			{
				GCArrayWatch* pAW = PgmMngr.m_ExtraWatchArray[DCB.lHandle-idmPGMArrayWatch];
				if (pAW)
				{
					if (DCB.rD && !DCB.ForFileSnpScn()) 
						pAW->set(*DCB.rD);
					DCB.D=pAW->getD();
					return True;
				}
			}
	}
	return False;
}

//--------------------------------------------------------------------------

flag GControl::ValidateData(ValidateDataBlk & VDB)
{
	flag OK=FlwNode::ValidateData(VDB);
	SetCI(1, bReloadReqd && GetActive());
	return OK;
}

//--------------------------------------------------------------------------

flag GControl::PreStartCheck()
{
	m_bMustInit = 1;
	m_bIterOne = 0;
	m_bMustTerm = 0;
	if (bOn)
	{
	}
	return FlwNode::PreStartCheck();
}

//--------------------------------------------------------------------------

bool GControl::TestXRefListActive() { return SetXRefListActive(!GetActiveHold() && bOn!=0); }

//--------------------------------------------------------------------------

int GControl::UpdateXRefLists(CXRefBuildResults & Results) 
{
	if (1)//bOn)
		PgmMngr.UpdateXRefLists(Results);
	return Results.m_nMissing;
}

//--------------------------------------------------------------------------

void GControl::UnlinkAllXRefs()
{
	PgmMngr.UnlinkAllXRefs();
	//CNodeXRefMngr::UnlinkAllXRefs();
	FlwNode::UnlinkAllXRefs();
};

//--------------------------------------------------------------------------

void GControl::EvalCtrlInitialise(eScdCtrlTasks Tasks)
{
	if (XRefListActive())
	{
		iIterCnt = -1;
		DoEvalCtrl(); 
		m_bIterOne = 1;
	}
};

//--------------------------------------------------------------------------

void GControl::EvalCtrlStrategy(eScdCtrlTasks Tasks)
{
	if (XRefListActive())
	{
		iIterCnt++;
		DoEvalCtrl();
		m_bIterOne = 0;
		m_bMustTerm = 1;
	}
}

//--------------------------------------------------------------------------

void GControl::EvalCtrlTerminate(eScdCtrlTasks Tasks)
{
	if (XRefListActive())
	{
		DoEvalCtrl(); 
	}
}

//--------------------------------------------------------------------------

void GControl::DoEvalCtrl()
{
	//dbgpln("!@@@@@@@@@@@@@@@@@@@@@@@@ %i %i %i %s", bOn, GetActiveHold(), ICGetTimeInc() > 0.0, Tag());

	if (bOn && !GetActiveHold() && ICGetTimeInc() > 0.0)
	{
		SetCI(1, bReloadReqd);
		//    if (bIterationOne && NetProbalMethod())
		//      PgmMngr.InitPBConvergence();
		CGExecContext ECtx(this);
		ECtx.dIC_Time = ICGetTime();
		ECtx.dIC_dTime = XRunning() ? ICGetTimeInc() : 0.0;
		//flag Initialise = (m_bMustInit && !XRunning() && XStarting());
		flag Initialise = (m_bMustInit && !XRunning());
		ECtx.SetFlags(Initialise, m_bIterOne, m_bMustTerm && !XRunning(), bJustLoaded, bEmpty, bPreset);
		PgmMngr.Execute(ECtx);
		ClrCI(4);
		if (PgmMngr.m_iRunTimeErr==1)
			SetCI(4, "E\tRun time error during iteration %d", iIterCnt);
		else if (PgmMngr.m_iRunTimeErr>1)
			SetCI(4, "E\t%d run time errors during iteration %d", PgmMngr.m_iRunTimeErr, iIterCnt);
		ClrCI(5);
		if (PgmMngr.m_iMathRunTimeErr==1)
			SetCI(5, "E\tMath run time error during iteration %d", iIterCnt);
		else if (PgmMngr.m_iMathRunTimeErr>1)
			SetCI(5, "E\t%d math run time errors during iteration %d", PgmMngr.m_iMathRunTimeErr, iIterCnt);
		for (int i=0; i<MaxCondMsgs; i++)
		{
			if (PgmMngr.m_CINOn[i])
				SetCI(6+i, "N\t%s", PgmMngr.m_CINMsgs[i]());
			else
				ClrCI(6+i);
			if (PgmMngr.m_CIEOn[i])
				SetCI(6+MaxCondMsgs+i, "E\t%s", PgmMngr.m_CIEMsgs[i]());
			else
				ClrCI(6+MaxCondMsgs+i);
		}
		bJustLoaded = 0;
		bEmpty = 0;
		bPreset = 0;
		if (ECtx.DoXStop)
		{
			LogError(Tag(), 0, "SysCAD stopped by PGM");
			ExecObj()->XStop();
		}
		if (ECtx.DoXIdle)
		{
			LogError(Tag(), 0, "SysCAD paused by PGM");
			ExecObj()->XIdle();
		}
		m_bMustInit = 0;
	}
	else
	{
		ClrCI(4);
		ClrCI(5);
		for (int i=0; i<MaxCondMsgs*2; i++)
			ClrCI(6+i);
	}
}

//--------------------------------------------------------------------------

flag GControl::GetOtherData(FilingControlBlock &FCB)
{
	if (FCB.SaveAs() && m_hProcess[0])
	{//during a save-as we must reset the link to the "old" edit files...
		//LogNote(Tag(), 0, "Remove link to currently open pgm file. (File should be closed)");
		//this is probably not needed for "far-away" files where location does not change
		for (int incs=0; incs<TP_MaxTtlIncludeFiles; incs++)
		{
			m_hProcess[incs] = NULL;
			m_dwProcessId[incs] = 0;
			m_EditTime[incs].dwLowDateTime=0;
			m_EditTime[incs].dwHighDateTime=0; 
		}
	}

	flag OK = PgmMngr.SaveScenario(FCB);

	if (FCB.SaveAs())
	{//need to correct the files used list after a save-as or save-version!
		for (int i=0; i<PgmMngr.m_FilesUsed.GetSize(); i++)
		{
			int pos = PgmMngr.m_FilesUsed[i].Find(FCB.OldPrjFiles());
			if (pos>=0)
			{
				Strng s;
				if (pos>0)
					s = PgmMngr.m_FilesUsed[i].Left(pos);
				s += FCB.Root();
				s += PgmMngr.m_FilesUsed[i].Mid(pos + strlen(FCB.OldPrjFiles()), 1024);
				PgmMngr.m_FilesUsed[i] = s;
			}
		}
	}
	return OK;
}

//--------------------------------------------------------------------------

flag GControl::PutOtherData(FilingControlBlock &FCB)
{
	return PgmMngr.LoadScenario(FCB);
}

//---------------------------------------------------------------------------

void GControl::OnAppActivate(BOOL bActive) 
{ 
	if (bOn && bActive)
	{//perhaps auto-reload PGM if date/time changed...
		Strng sFn;
		flag Reload=false;
		if (sPGMName() && (m_EditTime[0].dwLowDateTime || m_EditTime[0].dwHighDateTime))
		{
			if (sFn.FnExpandQueryReload(sPGMName(), m_EditTime[0]))
			{
				Reload=true;
				m_EditTime[0].dwLowDateTime=0;
				m_EditTime[0].dwHighDateTime=0; 
			}
		}
		for (int i=0; i<PgmMngr.m_FilesUsed.GetSize(); i++)
			if (sFn.FnExpandQueryReload(PgmMngr.m_FilesUsed[i](), PgmMngr.m_FilesTime[i]))
				Reload=true;

		if (Reload)
		{
			bReloadReqd=true;
			if (bAutoReload)
			{
				LoadPGM(sPGMName(), bWithDBG);
				if (1)
				{
					char* pTag = new char[strlen(Tag())+1];
					strcpy(pTag, Tag());
					ScdMainWnd()->PostMessage(WMU_TAGACTION, SUB_TAG_ACCREFRESHSAVE, (LPARAM)pTag);
				}
			}
			ValidateDataBlk VDB;
			ValidateData(VDB);
		}
		FlwNode::OnAppActivate(bActive);
	}
}

//--------------------------------------------------------------------------

int GControl::FilesUsed(CFilesUsedArray & Files)
{
	if (sPGMName.Len()>0)
	{
		Strng ss;
		Files.AddFile(FnExpand(ss, sPGMName()), FU_CopyFile|FU_EditTxt);
		const int RefFilesUsed = PgmMngr.m_FilesUsed.GetSize();
		for (int i=1; i<RefFilesUsed; i++)
			Files.AddFile(FnExpand(ss, PgmMngr.m_FilesUsed[i]()), FU_CopyFile|FU_EditTxt);
		//return RefFilesUsed;
	}
	FlwNode::FilesUsed(Files);
	return Files.GetCount();
	//return 0;
}

//--------------------------------------------------------------------------

void GControl::SetState(eScdMdlStateActs RqdState)
{
	FlwNode::SetState(RqdState);
	switch (RqdState)
	{
	case MSA_PBInit: break;
	case MSA_Empty: bEmpty = 1; break;
	case MSA_PreSet: bPreset = 1; break;
	case MSA_SteadyState: break;
	}
}

// -------------------------------------------------------------------------
#if WithPGMTagChange
std::string IntToString(int num)
{
	std::ostringstream myStream; //creates an ostringstream object
	myStream << num << std::flush;
	/*
	* outputs the number into the string stream and then flushes
	* the buffer (makes sure the output is put into the stream)
	*/
	return(myStream.str()); //returns the string form of the stringstream object
}
#endif

// Replaces pOldTag for pNewTag.  Renames the original file as fn.bck
void GControl::DoTextFileChangeTag(Strng fn, pchar pOldTag, pchar pNewTag, int& TagChangeCount, bool lookInComments, bool listChanges)
{
	TagChangeCount = 0;
#if WithPGMTagChange
	std::string lineList = "";
	const int BUFSIZE = 10000;
	char buf[BUFSIZE];

	std::string out;
	std::string regexStart = "(?<=[\\(\\[\\'\\\"\\.])";
	std::string regexTag   = pOldTag;
	std::string regexEnd   = "(?=[\\)\\]\\'\\\"\\.])";

	std::string commentRegex = "^[ \t]*;";

	std::string regexStr = regexStart + regexTag + regexEnd;

	CString fnIn = fn();
	CString fnTmp = fnIn + ".tmp";
	CString fnBck = fnIn + ".bck";

	std::ifstream pgmIn(fnIn);
	std::ofstream pgmOut(fnTmp);

	if (pgmIn.eof())
	{
		// complain...
	}
	else
	{
		std::tr1::regex regex(regexStr, std::tr1::regex::ECMAScript);
		std::tr1::smatch matches;
		std::string fmt("A");

		int lineNo = 0;

		while (!pgmIn.eof())
		{
			lineNo++;

			pgmIn.getline(buf, BUFSIZE-1);

			if ((lookInComments)||(!std::tr1::regex_match(commentRegex, matches, regex)))
			{
				out = std::tr1::regex_replace(regexStr, regex, fmt);


				if (matches.length() > 0)
				{
					lineList += IntToString(lineNo) + ", ";
					TagChangeCount += matches.length();
				}
			}

			pgmOut << out;
			if (!pgmIn.eof())
				pgmOut << std::endl;
		}
	}

	if (listChanges)
	{
		pgmOut << std::endl;
		pgmOut << ";" + std::string(CTime::GetCurrentTime().Format("%x %X")) + ":  '" + std::string(pOldTag) + "' changed to '" + std::string(pNewTag) + "'.  " + IntToString(TagChangeCount)
			+ " occurances on lines " + lineList.substr(0, lineList.length()-2) + ".";
		// %x %X -- uses currently defined time/date format for current locale...
	}

	pgmIn.close();
	pgmOut.close();

	remove(fnBck);
	rename(fnIn, fnBck);
	rename(fnTmp, fnIn);
#endif
}

//--------------------------------------------------------------------------

int GControl::ChangeTag(pchar pOldTag, pchar pNewTag)
{
	if (sPGMName.Len()>0)
	{
		Strng fn;
		int TagChangeCount;

		FnExpand(fn, sPGMName());
		DoTextFileChangeTag(fn(), pOldTag, pNewTag, TagChangeCount, true, true);
		if (TagChangeCount>0)
		{
			LogNote(Tag(), 0, "%d occurances of %s changed in %s", TagChangeCount, pOldTag, sPGMName());
		}

		const int RefFilesUsed = PgmMngr.m_FilesUsed.GetSize();
		for (int i=1; i<RefFilesUsed; i++)
		{
			FnExpand(fn, PgmMngr.m_FilesUsed[i]());
			//pkh todo 
			//DoTextFileChangeTag(fn(), pOldTag, pNewTag, ResultData);
			//if (ResultData.iTagChangeCount>0)
			//  {
			//  LogNote(Tag(), 0, "%d occurances of %s changed in %s", ResultData.iTagChangeCount, pOldTag, PgmMngr.m_FilesUsed[i]());
			//  }
		}
	}
	return FlwNode::ChangeTag(pOldTag, pNewTag);
}

//--------------------------------------------------------------------------

int GControl::DeleteTag(pchar pDelTag)
{
	return FlwNode::DeleteTag(pDelTag);
}

//--------------------------------------------------------------------------

flag GControl::CIStrng(int No, pchar & pS)
{
	// NB check CBCount is large enough.
	switch (No-CBContext())
	{
	case  1: pS="W\tPGM reload required";       return 1;
		//case  2: pS="E\tBad external tag references"; return 1;
		//case  3: pS="W\tEngineering units invalid"; return 1;
	case  4: pS="E\tRun time error"; return 1;
	case  5: pS="E\tMath run time error"; return 1;
	default:                                               
		return FlwNode::CIStrng(No, pS);
	}
}

//--------------------------------------------------------------------------

dword GControl::ModelStatus()
{
	dword Status=FlwNode::ModelStatus();
	Status|=bOn ? FNS_On : FNS_Off;
	return Status;
};

//==========================================================================
