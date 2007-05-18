//================== SysCAD - Copyright Kenwalt (Pty) Ltd ===================
// $Nokeywords: $
//===========================================================================

#ifndef  __ALCOABAYERSPMDL_H
#define  __ALCOABAYERSPMDL_H

#ifndef __SC_DEFS_H
  #include <sc_defs.h>
#endif  
#ifndef __SP_MODEL_H
  #include <sp_model.h>
#endif  

//#define MDLBASE
//#define BASIC1
#include "models.h"

#ifndef __ALSPMDLB_H
  #include "alspmdlb.h"
#endif  
 
#ifdef __ALCOABAYERSPMDL_CPP
  #define DllImportExport DllExport
#elif !defined(AlcoaSpMdl)
  #define DllImportExport DllImport
#else
  #define DllImportExport
#endif

// ===========================================================================
//
//                          Alcoa Bayer Specie Model
//
// ===========================================================================

DEFINE_SPMODEL(AlcoaBayer)

class DllImportExport CConcentrations
  {
  public:
    static flag     NaFactorOK;
    static SpVector NaFactor;

    AlcoaBayer     *pBayerMdl;
    CArray<double, double&> Liq;

    double         Density;

    CConcentrations(AlcoaBayer *pMdl);
    void Zero();
    flag Converge(CSysVector & MA);
    double LTotalSodium(CSysVector & MA);
    double LiquorDensity(double T_, CSysVector & MA);
    static double LiquorDensEqn1(double Tc, double WTNa, double WAlumina);
    static double LiquorDensEqn2(long Fidelity, double Tc, double A, double S, double C, double toc, double SO4, double Cl);
  };

// ===========================================================================

class DllImportExport AlcoaBayer : public SMBayerBase
  {
  friend class CConcentrations;
  DEFINE_SPARES(AlcoaBayer)

  protected:

    CConcentrations LiqConcs25;
    //globals...
    static double dBPEFactor;
    static double dRhoFactor;
    static double dMinSolCp;
    static double sm_dNaOrg_to_NOOC;
    static double sm_dNaInOrg_to_TA;
    static double sm_dNaOx_to_TA;
    static byte   sm_iBPEMethod;
    static byte   sm_iDensityMethod;
    static byte   sm_iCPMethod;
    static byte   sm_iFeedCalcMethod;

  public:

    flag			 fDoCalc;
	  double		 dRqd_AtoC, dRqd_C, dRqd_CtoS;
	  double		 dRqd_Sul, dRqd_Sil, dRqd_Salt;
    double     dRqd_Ox, dRqd_TOC;
	  double		 dRqd_SolFrac;
    static		 CArray <int, int> LclParm;
    //static CToleranceBlock sm_SolTol;

    AlcoaBayer(pTagObjClass pClass_, pchar Tag_, pTaggedObject pAttach, TagObjAttachment eAttach);
    virtual ~AlcoaBayer();

    virtual bool   IsBaseClassOf(pSpModel pOther) 
      { return (dynamic_cast<AlcoaBayer*>(pOther)) != NULL; };

    virtual void   BuildDataDefn_Vars(DataDefnBlk & DDB);
    virtual flag   DataXchg(DataChangeBlk & DCB);
    virtual flag   ValidateData(ValidateDataBlk & VDB);

    double         THAMassFlow();
    double         THADens(double T_);
    double         CausticConc(double T_);
    double         AluminaConc(double T_);
    double         SodaConc(double T_);
    double         SodiumCarbonateConc(double T_);
    double         SodiumSulphateConc(double T_);
    double         SodiumOxalateConc(double T_);
    double         SolidsConc(double T_);
    double         IonicStrength();
    double         AluminaConcSat(double T_);
    double         OxalateEquilibrium(double T_);
    double         AtoCSaturation(double T_);
    double         SSNRatio(double T_);
    double         AluminaSSN(double T_);
    //double         PerformAluminaSolubility(double TRqd, double ARqd, double THARqd, double NoPerSec, double Na2OFac, double SSat, flag & ConvergeErr);
    double         TOOC(double T_);
    double         TOC(double T_);
    double         FreeCaustic(double T_);
    double         AtoC();
    double         CtoS();
    double         CltoC();
    double         TOOCtoC();
    double         Na2SO4toC();

    //Jan 2002 : new virtuals for PSD...
    //double         SodiumFlourideConc(double T_) { ASSERT_ALWAYS(true, "TODO:SodiumFlourideConc"); return 0.0; };
    //double         QuartzConc(double T_) { ASSERT_ALWAYS(true, "TODO:QuartzConc"); return 0.0; };
    //double         HeamatiteConc(double T_) { ASSERT_ALWAYS(true, "TODO:HeamatiteConc"); return 0.0; };

    double         BoundSodaFrac() { ASSERT_ALWAYS(true, "TODO:BoundSodaFrac", __FILE__, __LINE__); return 0.0; };
    double         BoundSodaOrgFrac() { ASSERT_ALWAYS(true, "TODO:BoundSodaOrgFrac", __FILE__, __LINE__); return 0.0; };

    //double         OC(double T_) { ASSERT_ALWAYS(true, "TODO:OX", __FILE__, __LINE__); return 0.0; };
    //double         OX(double T_) { ASSERT_ALWAYS(true, "TODO:OC", __FILE__, __LINE__); return 0.0; };
    //void           DumpState() { ASSERT_ALWAYS(true, "TODO:DumpState", __FILE__, __LINE__); };
    //... end for new virtuals for PSD

    double         LVolume25();
    double         SLVolume25();
    double         TotalSodiumConc();
    double         OrganateConc();
    double         TotalOrganics();
    double         ChlorineConc();
    double         SulphateConc();
    double         SodiumOxalate_Conc();
    double         Chlorine_Conc();
    double         Sulphate_Conc();
    double         CausticConc_Na2O(double T_);
    double         SodaConc_Na2O(double T_);
    double         TotalSodiumConc_Na2O();
    double         AtoC_Na2O();
    double         TotalSodium(CSysVector * pMA=NULL);
    double         BoilPtElev(double T_, CSysVector * pMA=NULL);

    virtual DDEF_Flags FixSpEditFlags(DDEF_Flags Flags, int iSpid, flag AsParms);
	  virtual double RefTemp() { return C_2_K(0.0); };
    virtual double msCp(PhMask Phase, double T_, double P_, CSysVector * pMA=NULL, double *pTotalM=NULL);
    virtual double msHm(PhMask Phase, double T_, double P_, CSysVector * pMA=NULL, double *pTotalM=NULL);
    virtual double SaturationP(double T_, CSysVector * pMA, CSaturationDefn * pSatDefn=NULL);
    virtual double SaturationT(double P_, CSysVector * pMA=NULL, CSaturationDefn * pSatDefn=NULL);
    virtual double Rho(PhMask Phase, double T_, double P_, CSysVector * pMA=NULL);
    virtual double SpecieConc(double T_, int iSpNo, PhMask PhaseM);
	  virtual double PhaseConc(double T_, PhMask Ph, PhMask PhaseM=som_ALL);
    virtual double BoilingPtElevation(double P_, CSysVector * pMA=NULL);
    virtual double DynamicViscosity(PhMask Phase, double T_, double P_, CSysVector * pMA=NULL) { return SMBayerBase::DynamicViscosity(Phase, T_, P_, pMA); };
    virtual double ThermalConductivity(PhMask Phase, double T_, double P_, CSysVector * pMA=NULL) { return SMBayerBase::ThermalConductivity(Phase, T_, P_, pMA); };

  protected:
    void           DoInputCalcs(double T_);
    double         LiqCpCalc(CSysVector & Mn, double T_);
    
  public:
    // ConditionBlk Override
    DEFINE_CI(AlcoaBayer, SMBayerBase, 6);
  };

// ==========================================================================
//
//                                  End
//
// ==========================================================================

#undef DllImportExport

#endif
