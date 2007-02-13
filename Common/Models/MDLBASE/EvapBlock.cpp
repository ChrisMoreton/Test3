#include "stdafx.h"

#define __EVAPBLOCK_CPP
#include "EvapBlock.h"

//=========================================================================
//
//
//
//=========================================================================

XID xidEvapEnable = EvapXID(1);
XID xidEvapEqnNm  = EvapXID(2);
XID xidCompCount  = EvapXID(3);

//============================================================================
//
//
//
//============================================================================

const pchar CEvapBlock::GroupName="EvapBlock";

IMPLEMENT_EVAP(CEvapBlock, "EvapNone", "", TOC_ALL|TOC_GRP_GENERAL|TOC_STD_KENWALT, "None",  " ");


CEvapBlock::CEvapBlock(pTagObjClass pClass_, pchar Tag_, TaggedObject* pAttach, TagObjAttachment eAttach) :
TaggedObject(pClass_, Tag_, pAttach, eAttach)
  {
  m_pEvapBase = NULL;
  }

//--------------------------------------------------------------------------

CEvapBlock::~CEvapBlock()
  {
  };

//--------------------------------------------------------------------------

void CEvapBlock::BuildDataDefn(DataDefnBlk& DDB)
  {
  if (DDB.BeginStruct(this, NULL/*"Evap"*/, NULL, DDB_NoPage))
    {
    }
  DDB.EndStruct();
  };

//--------------------------------------------------------------------------

void CEvapBlock::EvalProducts(SpConduit &Qf, double Po, double FinalTEst)
  {
  };

void CEvapBlock::EvalProductsInline(SpConduit & Qf, double Len, double Diam, double Po, double FinalTEst)
  {
  };

//============================================================================
//
//
//
//============================================================================

#define VER1 01

const byte Dest_Mix     = -2;
const byte Dest_Discard = -1;
const byte Dest_IO1     = 0; //????????????????

#if WithSimpleEvap
IMPLEMENT_EVAP(CEvBlk_Percentage, "EvapPerc", "", TOC_ALL|TOC_GRP_GENERAL|TOC_STD_KENWALT, "Percentage",  " ");
#endif

CEvBlk_Percentage::CEvBlk_Percentage(pTagObjClass pClass_, pchar Tag_, TaggedObject* pAttach, TagObjAttachment eAttach) :
CEvapBlock(pClass_, Tag_, pAttach, eAttach)
  {
#if VER1
  m_Components.SetSize(gs_CDB.DDBCompListVapLiq.Length());
  for (int i=0; i<m_Components.GetSize(); i++)
    {
    m_Components[i].m_CIndex   = gs_CDB.DDBCompListVapLiq[i].m_lVal;
    m_Components[i].m_Dest     = 0;
    m_Components[i].m_Fraction = 0.0;
    }
  m_dEvapFrac   = 0.0;
  m_dQmEvap     = 0.0;
  m_dQmFeed     = 0.0;
  m_dQmBleed    = 0.0;
  m_dQmProd     = 0.0;
  m_dHeatFlow   = 0.0;
  m_dTempKFeed  = C2K(0.0);
  m_dTempKProd  = C2K(0.0);
#endif
  }

//--------------------------------------------------------------------------

CEvBlk_Percentage::~CEvBlk_Percentage()
  {
  }

//--------------------------------------------------------------------------

static DDBValueLst DDBDestinations[] =
  {
    { Dest_Mix      , "Mixture"},
    { Dest_Discard  , "Discard"},
    { 0 }
  };

void CEvBlk_Percentage::BuildDataDefn(DataDefnBlk& DDB)
  {
  if (DDB.BeginStruct(this, "EvapPerc", NULL, DDB_NoPage))
    {
    DDB.Text("Requirements");
#if VER1
    if (DDB.BeginArray(this, "Comp", "EVB_Comps", m_Components.GetSize()))
      {
      for (int i=0; i<m_Components.GetSize(); i++)
        {
        LPTSTR Tg=gs_CDB[m_Components[i].m_CIndex].SymOrTag();
        if (DDB.BeginElement(this, Tg, NULL, i))
          {
          DDB.Byte  ("", "Destination", DC_,     "",  &m_Components[i].m_Dest,      this, isParmStopped, DDBDestinations);
          DDB.Double("", "Fraction",    DC_Frac, "%", &m_Components[i].m_Fraction,  this, isParm);
          }
        }
      }
    DDB.EndArray();

    DDB.Text("");
    DDB.Text("Results");
    DDB.Double ("Evap.Qm",            "", DC_Qm,   "kg/s",    &m_dQmEvap,     this, isResult);
    DDB.Double ("Evap.Frac",          "", DC_Frac, "%",       &m_dEvapFrac,   this, isResult);
    DDB.Text(" ");
    DDB.Text("Total mass flow:");
    DDB.Double ("Qm.Feed",            "", DC_Qm,   "kg/s",    &m_dQmFeed,     this, isResult);
    DDB.Double ("Qm.Bleed",           "", DC_Qm,   "kg/s",    &m_dQmBleed,    this, isResult);
    DDB.Double ("Qm.Prod",            "", DC_Qm,   "kg/s",    &m_dQmProd,     this, isResult);
    if (!HeatSkipMethod())
      {
      DDB.Text("Total heat flow:");
      DDB.Double ("Temp.Feed",          "", DC_T,    "C",       &m_dTempKFeed,  this, isResult);//|noFileAtAll);
      DDB.Double ("HeatFlow",           "", DC_Pwr,  "kW",      &m_dHeatFlow,   this, isResult);
      DDB.Double ("Temp.Prod",          "", DC_T,    "C",       &m_dTempKProd,  this, isResult);//|noFileAtAll);
      }
#else
    DDB.Int("CompCount",     "",   DC_, "", xidCompCount,    this, isParm);
    if (DDB.BeginArray(this, "Comp", "EVB_Comps", m_Components.GetSize()))
      {
      for (int i=0; i<m_Components.GetSize(); i++)
        {
        if (DDB.BeginElement(this, i, NULL, i))
          {
          DDB.Long  ("", "Component", DC_,     "",  &m_Components[i].m_CIndex,    this, isParmStopped, &gs_CDB.DDBCompListDashVapLiq);
          DDB.Double("", "Fraction",  DC_Frac, "%", &m_Components[i].m_Fraction,  this, isParm);
          }
        }
      }
    DDB.EndArray();
#endif
    }
  DDB.EndStruct();
  }

//--------------------------------------------------------------------------

flag CEvBlk_Percentage::DataXchg(DataChangeBlk & DCB)
  {
#if VER1
#else
  switch (DCB.lHandle)
    {
    case xidCompCount:
      if (DCB.rL)
        {
        int Old=m_Components.GetSize();
        m_Components.SetSize(*DCB.rL);
        for (int i=Old; i<m_Components.GetSize(); i++)
          {
          m_Components[i].m_CIndex=-1;
          m_Components[i].m_Fraction=0.0;
          }
        }
      DCB.L=m_Components.GetSize();
      return 1;
    }
#endif
  return 0;
  }

//--------------------------------------------------------------------------

flag CEvBlk_Percentage::ValidateData(ValidateDataBlk & VDB)
  {
#if VER1
#else
  for (int i=0; i<m_Components.GetSize(); i++)
    {
    int iComp=m_Components[i].m_CIndex;
    if (iComp>=0)
      {
      for (int j=i+1; j<m_Components.GetSize(); j++)
        {
        if (iComp==m_Components[j].m_CIndex)
          {
          m_Components.RemoveAt(j);
          j--;
          }
        }
      }
    }
#endif

  for (int i=0; i<m_Components.GetSize(); i++)
    m_Components[i].m_Fraction=Range(0.0, m_Components[i].m_Fraction, 1.0);

  return CEvapBlock::ValidateData(VDB); 
  }

//--------------------------------------------------------------------------

void CEvBlk_Percentage::EvalProducts(SpConduit &Qf, double Po, double FinalTEst)
  {
  m_dQmFeed = Qf.QMass();
  m_dTempKFeed = Qf.Temp();
  const double HzIn = Qf.totHz();

  SpConduit & Discard = m_pEvapBase->DiscardCd();
  Discard.QZero();
  SpMArray OldVap;
  double TtlLiq = 0.0;
  double TtlEvap = 0.0;

  Qf.SetPress(Po);
  const double H=Qf.totHf();
  for (int i=0; i<m_Components.GetSize(); i++)
    {
    CEvapComp  & EC = m_Components[i];
    CComponent & C  = gs_CDB[EC.m_CIndex];
    const int iLiq=C.LiqPhInx();
    const int iVap=C.VapPhInx();
    const double Liq=Qf.VMass[iLiq];
    const double Vap=Qf.VMass[iVap];
    const double D=Liq*EC.m_Fraction;
    TtlLiq += Liq;
    TtlEvap += D;

    Qf.SetVValue(iLiq, Liq-D);
    Qf.SetVValue(iVap, Vap+D);

    Discard.SetVValue(iVap, D);
    OldVap.SetVValue(iVap, Vap);
    }
  Qf.Set_totHf(H);

  const double T=Qf.Temp();
  const double P=Qf.Press();
  for (int i=0; i<m_Components.GetSize(); i++)
    {
    CEvapComp  & EC = m_Components[i];
    const int iVap = gs_CDB[EC.m_CIndex].VapPhInx();
    switch (EC.m_Dest)
      {
      case Dest_Mix:
        // Qf is at correct conditions
        Discard.SetVValue(iVap, 0.0);
        break;
      case Dest_Discard:
        Qf.SetVValue(iVap, OldVap[iVap]); // reset to original vapour mass
        break;
      }
    }
  Qf.SetTempPress(T, P);
  Discard.SetTempPress(T, P);

  m_dQmEvap     = TtlEvap;
  m_dEvapFrac   = (TtlLiq>SmallPosFlow ? TtlEvap/TtlLiq : 0.0);
  m_dQmProd     = Qf.QMass();
  m_dQmBleed    = m_dQmFeed-m_dQmProd;
  m_dTempKProd  = Qf.Temp();
  m_dHeatFlow   = Qf.totHz() - HzIn;
  }

//--------------------------------------------------------------------------

void CEvBlk_Percentage::EvalProductsInline(SpConduit & Qf, double Len, double Diam, double Po, double FinalTEst)
  {
  EvalProducts(Qf, Po, FinalTEst);
  }

//============================================================================
//
//
//
//============================================================================

#if WithSimpleEvap
IMPLEMENT_EVAP(CEvBlk_FixedFlow, "EvapFlow", "", TOC_ALL|TOC_GRP_GENERAL|TOC_STD_KENWALT, "FixedFlow",  " ");
#endif

CEvBlk_FixedFlow::CEvBlk_FixedFlow(pTagObjClass pClass_, pchar Tag_, TaggedObject* pAttach, TagObjAttachment eAttach) :
CEvapBlock(pClass_, Tag_, pAttach, eAttach)
  {
  m_Components.SetSize(gs_CDB.DDBCompListVapLiq.Length());
  for (int i=0; i<m_Components.GetSize(); i++)
    {
    m_Components[i].m_CIndex   = gs_CDB.DDBCompListVapLiq[i].m_lVal;
    m_Components[i].m_Dest     = 0;
    m_Components[i].m_QmRqd    = 0.0;
    }
  m_dEvapFrac   = 0.0;
  m_dQmEvap     = 0.0;
  m_dQmFeed     = 0.0;
  m_dQmBleed    = 0.0;
  m_dQmProd     = 0.0;
  m_dHeatFlow   = 0.0;
  m_dTempKFeed  = C2K(0.0);
  m_dTempKProd  = C2K(0.0);
  }

//--------------------------------------------------------------------------

CEvBlk_FixedFlow::~CEvBlk_FixedFlow()
  {
  }

//--------------------------------------------------------------------------

void CEvBlk_FixedFlow::BuildDataDefn(DataDefnBlk& DDB)
  {
  if (DDB.BeginStruct(this, "EvapPerc", NULL, DDB_NoPage))
    {
    DDB.Text("Requirements");
    if (DDB.BeginArray(this, "Comp", "EVB_Comps", m_Components.GetSize()))
      {
      for (int i=0; i<m_Components.GetSize(); i++)
        {
        LPTSTR Tg=gs_CDB[m_Components[i].m_CIndex].SymOrTag();
        if (DDB.BeginElement(this, Tg, NULL, i))
          {
          DDB.Byte  ("", "Destination", DC_,     "",  &m_Components[i].m_Dest,      this, isParmStopped, DDBDestinations);
          DDB.Double("", "Qm",          DC_Qm,   "kg/s", &m_Components[i].m_QmRqd,  this, isParm);
          }
        }
      }
    DDB.EndArray();

    DDB.Text("");
    DDB.Text("Results");
    DDB.Double ("Evap.Qm",            "", DC_Qm,   "kg/s",    &m_dQmEvap,     this, isResult);
    DDB.Double ("Evap.Frac",          "", DC_Frac, "%",       &m_dEvapFrac,   this, isResult);
    DDB.Text(" ");
    DDB.Text("Total mass flow:");
    DDB.Double ("Qm.Feed",            "", DC_Qm,   "kg/s",    &m_dQmFeed,     this, isResult);
    DDB.Double ("Qm.Bleed",           "", DC_Qm,   "kg/s",    &m_dQmBleed,    this, isResult);
    DDB.Double ("Qm.Prod",            "", DC_Qm,   "kg/s",    &m_dQmProd,     this, isResult);
    if (!HeatSkipMethod())
      {
      DDB.Text("Total heat flow:");
      DDB.Double ("Temp.Feed",          "", DC_T,    "C",       &m_dTempKFeed,  this, isResult);//|noFileAtAll);
      DDB.Double ("HeatFlow",           "", DC_Pwr,  "kW",      &m_dHeatFlow,   this, isResult);
      DDB.Double ("Temp.Prod",          "", DC_T,    "C",       &m_dTempKProd,  this, isResult);//|noFileAtAll);
      }
    }
  DDB.EndStruct();
  }

//--------------------------------------------------------------------------

flag CEvBlk_FixedFlow::DataXchg(DataChangeBlk & DCB)
  {
  return 0;
  }

//--------------------------------------------------------------------------

flag CEvBlk_FixedFlow::ValidateData(ValidateDataBlk & VDB)
  {
  for (int i=0; i<m_Components.GetSize(); i++)
    m_Components[i].m_QmRqd=Max(0.0, m_Components[i].m_QmRqd);

  return CEvapBlock::ValidateData(VDB); 
  }

//--------------------------------------------------------------------------

void CEvBlk_FixedFlow::EvalProducts(SpConduit &Qf, double Po, double FinalTEst)
  {
  m_dQmFeed = Qf.QMass();
  m_dTempKFeed = Qf.Temp();
  const double HzIn = Qf.totHz();

  SpConduit & Discard = m_pEvapBase->DiscardCd();
  Discard.QZero();
  SpMArray OldVap;
  double TtlLiq = 0.0;
  double TtlEvap = 0.0;

  Qf.SetPress(Po);
  const double H=Qf.totHf();
  for (int i=0; i<m_Components.GetSize(); i++)
    {
    CEvapComp  & EC = m_Components[i];
    CComponent & C  = gs_CDB[EC.m_CIndex];
    const int iLiq=C.LiqPhInx();
    const int iVap=C.VapPhInx();
    const double Liq=Qf.VMass[iLiq];
    const double Vap=Qf.VMass[iVap];
    const double D=Min(EC.m_QmRqd, Liq);
    TtlLiq += Liq;
    TtlEvap += D;

    Qf.SetVValue(iLiq, Liq-D);
    Qf.SetVValue(iVap, Vap+D);

    Discard.SetVValue(iVap, D);
    OldVap.SetVValue(iVap, Vap);
    }
  Qf.Set_totHf(H);

  const double T=Qf.Temp();
  const double P=Qf.Press();
  for (int i=0; i<m_Components.GetSize(); i++)
    {
    CEvapComp  & EC = m_Components[i];
    const int iVap = gs_CDB[EC.m_CIndex].VapPhInx();
    switch (EC.m_Dest)
      {
      case Dest_Mix:
        // Qf is at correct conditions
        Discard.SetVValue(iVap, 0.0);
        break;
      case Dest_Discard:
        Qf.SetVValue(iVap, OldVap[iVap]); // reset to original vapour mass
        break;
      }
    }
  Qf.SetTempPress(T, P);
  Discard.SetTempPress(T, P);

  m_dQmEvap     = TtlEvap;
  m_dEvapFrac   = (TtlLiq>SmallPosFlow ? TtlEvap/TtlLiq : 0.0);
  m_dQmProd     = Qf.QMass();
  m_dQmBleed    = m_dQmFeed-m_dQmProd;
  m_dTempKProd  = Qf.Temp();
  m_dHeatFlow   = Qf.totHz() - HzIn;
  }

//--------------------------------------------------------------------------

void CEvBlk_FixedFlow::EvalProductsInline(SpConduit & Qf, double Len, double Diam, double Po, double FinalTEst)
  {
  EvalProducts(Qf, Po, FinalTEst);
  }

//============================================================================
//
//
//
//============================================================================

flag CEvapBase::Open(TagObjClass * pEvapClass, flag Fixed)
  {
  m_fEnabled=True;

  if (m_pEvapB && (pEvapClass==NULL || m_pEvapB->Class()==pEvapClass))
    return True;

  delete m_pEvapB;
  m_fFixed=Fixed;

  if (pEvapClass)
    m_pEvapB=(CEvapBlock*)pEvapClass->Construct(NULL, "Evap", m_pNd, TOA_Embedded);//pNd);
  else
    m_pEvapB=(CEvapBlock*)CEvapBlockClass.Construct(NULL, "Evap", m_pNd, TOA_Embedded);//pNd);
  m_pNd->StructureChanged(NULL);
  m_pEvapB->m_pEvapBase=this;

  m_fEnabled=m_pEvapB!=NULL;
  return m_fEnabled;
  };

//--------------------------------------------------------------------------

void CEvapBase::Close()
  {
  if (m_fFixed)
    return;
  m_fEnabled=False;
  //if (pEvapClass==NULL)
  //  return;
  ////pGSM->StructureChanged(NULL);
  ////pGSM->Gammas.SetSize(0);
  ////pGSM->IOAlpha.SetSize(0);
  //delete pEvapClass;
  //pEvapClass=NULL;
  };
//--------------------------------------------------------------------------

void CEvapBase::Add_OnOff(DataDefnBlk &DDB, dword Flags)
  {
  DDB.Byte("",     "Evaporator",  DC_,    "",     xidEvapEnable,  m_pNd, Flags, GetOnOffValLst());
  }

//--------------------------------------------------------------------------

void CEvapBase::BuildDataDefn(DataDefnBlk &DDB, char* pTag, char* pTagComment, DDBPages PageIs, dword UserInfo)
  {
  if (pTag==NULL)
    pTag="Eval";
  DDEF_Flags Old=DDB.GetVisibility();
  DDB.Visibility(NSHM_All, m_fEnabled);

  if (Enabled())//pHL)
    {
    if (DDB.BeginStruct(m_pNd, pTag, pTagComment, PageIs))
      {
      DDBValueLstMem DDB0;
      TagObjClass::GetSDescValueLst(CEvapBlock::GroupName, DDB0);
      DDB.String  ("Model",      "",       DC_    , "",      xidEvapEqnNm  , m_pNd,m_fFixed ? 0 : isParmStopped|SetOnChange, DDB0());

      if (m_pEvapB)
        {
        DDB.SuppressNextBlock();
        m_pEvapB->BuildDataDefn(DDB);
        }
      }
    DDB.EndStruct();
    }
  DDB.SetVisibility(Old);
  };

//--------------------------------------------------------------------------

flag CEvapBase::DataXchg(DataChangeBlk & DCB)
  {
  switch (DCB.lHandle)
    {
    case xidEvapEnable:
      if (DCB.rB)
        {
        if (*DCB.rB)
          Open(*DCB.rB);
        else
          Close();
        }
      DCB.B=OpenStatus();// (Enabled());
      return 1;
    case xidEvapEqnNm:
      if (DCB.rpC && !m_fFixed)
        {
        int WasEnabled=m_fEnabled;
        TagObjClass * pC=CEvapBlockClass.FindGrpShortDesc(DCB.rpC);
        if (pC)
          Open(pC);
        else
          Close();
        }
      DCB.pC = m_pEvapB ? m_pEvapB->ShortDesc() : "";
      return 1;
    }
  return 0;
  }

//=========================================================================
//
//
//
//=========================================================================
