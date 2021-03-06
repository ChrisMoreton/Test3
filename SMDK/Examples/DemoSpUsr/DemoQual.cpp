//================== SysCAD - Copyright Kenwalt (Pty) Ltd ===================
// $Nokeywords: $
//===========================================================================
#include "stdafx.h"
#include "DemoQual.h"
#include "math.h"
#include "md_headers.h"
#pragma comment(lib, "rpcrt4.lib")

//===========================================================================
//
//
//
//===========================================================================
 
IMPLEMENT_SPECIEQUALITY(CDemoQual, "DemoQual", "DemoQual ShortDesc", "CDemoQual Desc", DLL_GroupName)

CDemoQual::CDemoQual(TaggedObject * pNd)
  {
  MInitialise(); // this must be called to initialise the SMDK library if neccessary

  m_SpCount = 0;
  m_PSDCount = 0;
  m_DSDCount = 0;

  m_dSG=0.0;
  m_dSetProp=2.0;
  }

//---------------------------------------------------------------------------

CDemoQual::~CDemoQual()
  {
  }

//---------------------------------------------------------------------------

void CDemoQual::BuildDataFields()
  { 
  };              

//---------------------------------------------------------------------------

bool CDemoQual::ExchangeDataFields()
  {
  return false;
  };

//---------------------------------------------------------------------------

bool CDemoQual::ValidateDataFields()
  { 
  return true; 
  }; 

//===========================================================================
//
//
//
//===========================================================================

long CDemoQual::DefinedPropertyCount()
  {
  return 2; 
  }

//---------------------------------------------------------------------------

long CDemoQual::DefinedPropertyInfo(long Index, MPropertyInfo & Info)
  {
  long Inx=Index;//(Index-MSpModelBase::DefinedPropertyCount());
  switch (Inx)
    {
    case 0: Info.SetStructName("DemoQuals");
            Info.Set(ePT_Double,    "SG",        "", MC_,    "",       0,      0,  MP_Result|MP_NoFiling, "A Desc"); return Inx;
    case 1: Info.Set(ePT_Double,    "Set",       "", MC_,    "",       0,      0,  MP_HardMin|MP_Parameter, "A Desc"); return Inx;
    }
  return -1;
  };

//---------------------------------------------------------------------------

DWORD CDemoQual::GetPropertyVisibility(long Index)
  {
  return ePVis_All;
  };

//---------------------------------------------------------------------------

void CDemoQual::GetPropertyValue(long Index, ULONG Phase/*=MP_All*/, double T/*=NAN*/, double P/*=NAN*/, MPropertyValue & Value)
  {
  switch (Index)
    {
    case   0: Value=m_dSG;  return ;
    case   1: Value=m_dSetProp;  return ;
    };
  };

//---------------------------------------------------------------------------

void CDemoQual::PutPropertyValue(long Index, MPropertyValue & Value)
  {
  switch (Index)
    {
    case  1: m_dSetProp=Value; return;
    };
  };

//---------------------------------------------------------------------------

void CDemoQual::ExchangeSpecies(MSpQualityBase * Other) 
  {
  };
bool CDemoQual::EquilRqd4HEval()
  {
  return false;
  };
void CDemoQual::Equilibrate() 
  {
  MVector M1(this);
  m_dSG=M1.Density()/1000;
  };
void CDemoQual::ZeroMass() 
  {
  };
void CDemoQual::ZeroDeriv() 
  {
  };
void CDemoQual::ScaleMass(long Phase, double Mult) 
  {
  };
void CDemoQual::ScaleMass(CArray<int,int> &SpIds, double Mult)
  {
  };
void CDemoQual::SetMassF(MSpQualityBase * QualSet, MArray & MSet) 
  {
  CDemoQual * pQ2=dynamic_cast<CDemoQual*>(QualSet);
  m_dSG=pQ2->m_dSG;
  m_dSetProp=pQ2->m_dSetProp;

  m_SpCount  = pQ2->m_SpCount ;
  m_PSDCount = pQ2->m_PSDCount;
  m_DSDCount = pQ2->m_DSDCount;

  };
void CDemoQual::AddMassF(MSpQualityBase * QualAdd, MArray & MAdd) 
  {
  MVector M1(this);
  CDemoQual * pQualAdd=dynamic_cast<CDemoQual*>(QualAdd);
  
  double m1    = M1.Mass();
  double m2    = MAdd.Mass();
  double Frac1 = m1/GTZ(m1+m2);
  double Frac2 = 1.0-Frac1;
  
  m_dSG       = Frac1*m_dSG + Frac2*pQualAdd->m_dSG;
  m_dSetProp  = Frac1*m_dSetProp + Frac2*pQualAdd->m_dSetProp;

  //m_SpCount  = pQ2->m_SpCount ;
  //m_PSDCount = pQ2->m_PSDCount;
  //m_DSDCount = pQ2->m_DSDCount;
  };
void CDemoQual::SubMassF(MSpQualityBase * QualSub, MArray & M2) 
  {
  };
void CDemoQual::Copy(MVector &V2, MSpQualityBase * QualCopy) 
  {
  CDemoQual * pQ2=dynamic_cast<CDemoQual*>(QualCopy);
  m_dSG=pQ2->m_dSG;
  m_dSetProp=pQ2->m_dSetProp;
  m_SpCount  = pQ2->m_SpCount ;
  m_PSDCount = pQ2->m_PSDCount;
  m_DSDCount = pQ2->m_DSDCount;
  };

void CDemoQual::AddDeriv(MVector &V2, MSpQualityBase * pQual2, double Sgn_, double DeltaTime) 
  {
  };
void CDemoQual::AddDiscrete(MVector &V2, MSpQualityBase * pQual2, double Sgn_, double DeltaTime) 
  {
  };
