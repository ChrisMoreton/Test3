//================== SysCAD - Copyright Kenwalt (Pty) Ltd ===================
// $Nokeywords: $
//===========================================================================

#ifndef  __EXAMPLESURGE_H
#define  __EXAMPLESURGE_H

#ifndef __MD_HEADERS_H
#include "md_headers.h"
#endif

#ifdef __EXAMPLESURGE_CPP
  #define DllImportExport __declspec(dllexport)
#elif !defined(SMDKDemoU)
  #define DllImportExport __declspec(dllimport)
#else
  #define DllImportExport
#endif

//---------------------------------------------------------------------------

class Tank : public MBaseMethod
  {
  public:
    Tank(MUnitDefBase * pUnitDef, TaggedObject * pNd);
    virtual void    Init();
    virtual void    BuildDataFields();
    virtual void    EvalProducts();

    //example of model "actions"
    virtual bool    GetModelAction(CMdlActionArray & Acts);
    virtual bool    SetModelAction(CMdlAction & Act);
    //example of model "graphics view"
    virtual bool    GetModelGraphic(CMdlGraphicArray & Grfs);
    virtual bool    OperateModelGraphic(CMdlGraphicWnd & Wnd, CMdlGraphic & Grf);

  protected:
    bool          bDoPhaseSplit;
    double        dRqdFracSplit;
    double        dRqdSolSplit;
    double        dRqdLiqSplit;
    double        dRqdVapSplit;
    double        dFeedQm;
    double        dProdQm0;
    double        dProdQm1;

    bool          m_LBtnDn;
    bool          m_RBtnDn;
    CPoint        m_MousePt;
  };

#endif