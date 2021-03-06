#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CFindTagsDlg dialog

class CFindTagsDlg; // forward
class CFTItem; // forward
class CFTClass; // forward
class CFTPage; // forward
class CFTRepSeq; // forward

//class CFTRepSeq
//  {
//  public:
//    CFTRepSeq()
//      {
//      m_AdjustCnt=0;
//      m_ReplaceUndoCnt=0;
//      m_nDuplicateCount=0;
//      }
//    CFTRepSeq(const CFTRepSeq & Other)
//      {
//      *this=Other;
//      }
//    CFTRepSeq & operator=(const CFTRepSeq & Other)
//      {
//      m_sReplacement    = Other.m_sReplacement;
//      m_sStatus         = Other.m_sStatus;
//      m_nDuplicateCount = Other.m_nDuplicateCount;
//      m_AdjustCnt       = Other.m_AdjustCnt;
//      m_ReplaceUndoCnt      = Other.m_ReplaceUndoCnt;
//      return *this;
//      }
//
//  public:
//    CString           m_sReplacement;
//    CString           m_sStatus;
//    BOOL              m_nDuplicateCount;
//    int               m_AdjustCnt;
//    int               m_ReplaceUndoCnt;
//  };

class CFTItem //: public CFTRepSeq
  {
  friend class CFindTagsDlg;

  enum eDoItTerms {/*eSRPage,*/ eSRCheck/*, eSRClass*/, eSRMarked, eSRSelected};

  public:
    CFTItem(CFindTagsDlg * Dlg, LPCTSTR Tag, CFTClass * ClassId);
    LPCTSTR       Display();
    //void        PutString (int j, LPCTSTR Str);



    //BOOL        PageChecked();
    //BOOL        SetReqd(bool IgnoreCheck=false);
    //void        ChangeSetReqd(eDoItTerms Term, BOOL On);
    //void        SaveSetReqd();
    //void        TestSetReqd();

    //BOOL        DoIt(bool IgnoreCheck=false);
    BOOL        ShowIt();
    //void        Start();
    //void        TagChanged();
    //void        Replace(LPCTSTR New);
    //void        Undo();
    //LPCTSTR     StatusString();

  public:
    CFindTagsDlg  & m_Dlg;
    CString           m_sTag;
    CString           m_sTagLwr;
    //CString           m_sPages;
    CString           m_sDisplay;
    CFTClass        * m_pClassId;
    BOOL              m_Selected;
    BOOL              m_Marked;
    BOOL              m_Loaded;
    int               m_nRefs;
    HTREEITEM         m_hTree;

    CArray<CFTPage*, CFTPage*> m_Pages;
  };

class CFTClass
  {
  friend class CFindTagsDlg;

  public:
    CFTClass(CFindTagsDlg * Dlg, LPCTSTR ClassId) : m_Dlg(*Dlg)
      {
      m_sClassId=ClassId;
      };

  public:
    CFindTagsDlg  & m_Dlg;
    CString           m_sClassId;
    //BOOL              m_Checked; 
  };

class CFTPage
  {
  friend class CFindTagsDlg;

  public:
    CFTPage(CFindTagsDlg * Dlg, LPCTSTR PageId) : m_Dlg(*Dlg) 
      {
      m_sPageId=PageId;
      };

  public:
    CFindTagsDlg  & m_Dlg;
    CString           m_sPageId;
    //BOOL              m_Checked; 
  };

//class CFindTagsTreeCtrl : public CTreeCtrl
//  {
//  // Construction
//  public:
//    CFindTagsTreeCtrl(CFindTagsDlg *Dlg);
//    //CFindTagTreeCtrl &m_Data;
//
//    // Attributes
//  public:
//    CFindTagsDlg &m_Dlg;
//
//    // Operations
//
//  public:
//    virtual ~CFindTagsTreeCtrl();
//    void    OnButtonUp(CPoint point);
//
//    // Generated message map functions
//  protected:
//    //{{AFX_MSG(CFindTagTreeCtrl)
//    //afx_msg void OnBeginDrag(LPNMHDR pnmhdr, LRESULT *pResult);
//    //afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//    //}}AFX_MSG
////    afx_msg void OnPaint();
//
//    DECLARE_MESSAGE_MAP()
//  };

class CFindTagsDlg : public CDialog
  {
  DECLARE_DYNAMIC(CFindTagsDlg)

  public:
    CFindTagsDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CFindTagsDlg();

    // Dialog Data
    enum { IDD = IDD_FINDTAGSDLG };

  protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL  OnInitDialog();
    virtual void  OnOK();
    virtual void  OnCancel();
    virtual BOOL  XXOnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);


    void          BuildTags();
    void          ClearTags();
    void          SetFilter();
    void          LoadTagTree();
    void          LoadTagItem(CFTItem & Tg, bool UpdateTag=false);
    void          SaveProfile();

    void          PositionControls(int cx, int cy);
    void          SavePos();
    void          RestorePos();

  public:
    void          DoOnItem(HTREEITEM hItem, bool RClick);
    void          ProcessTimer(UINT_PTR idEvent);

  protected:
    DECLARE_MESSAGE_MAP()

  public:

    CPoint                m_TopLeft;            // Relative to Main Wnd Client TopLeft
    CRect                 m_ClientRctInit;
    CRect                 m_WindowRctInit;
    CArray<CRect, CRect&> m_CtrlRcts;

    CTreeCtrl             m_TagTree;
    CComboBox             m_TagFilterRule;
    CEdit                 m_TagFilter;

    BOOL                  m_Inited;
    BOOL                  m_bCaseSens;
    IRegExpPtr          * m_pFilterRE;

    BOOL                  m_GoTo;
    BOOL                  m_DoAccess;
    CString               m_TagName;
    CString               m_GraphName;
    CString               m_TrendName;
    int                   m_TrendLine;

    HTREEITEM             m_LastItem;
    UINT                  m_nTimer;

    //int                   m_RClick;
    static CFindTagsDlg * gs_pDlg;
   
    CArray <CFTItem*, CFTItem*> m_Tags;
    CMap <LPCTSTR, LPCTSTR,  CFTItem*, CFTItem*> m_TagMap;
    CMap <HTREEITEM, HTREEITEM,  CFTItem*, CFTItem*> m_TagHMap;
    CArray <CFTPage*, CFTPage*> m_Pages;
    CMap <LPCTSTR, LPCTSTR,  CFTPage*, CFTPage*> m_PageMap;
    CArray <CFTClass*, CFTClass*> m_Classes;
    CMap <LPCTSTR, LPCTSTR,  CFTClass*, CFTClass*> m_ClassMap;

    afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTvnSelchangedTagtree(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCbnSelchangeTagfilterrule();
    afx_msg void OnEnChangeTagfilter();
    afx_msg void OnBnClickedGoto();
    afx_msg void OnBnClickedGoaccess();
    afx_msg void OnNMDblclkTagtree(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickTagtree(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnTvnSelchangingTagtree(NMHDR *pNMHDR, LRESULT *pResult);
    //afx_msg void OnTimer(UINT nIDEvent); 
    afx_msg void OnNMRclickTagtree(NMHDR *pNMHDR, LRESULT *pResult);
  };
