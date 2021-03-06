// SlotCommon.h: interface for the CSlotCommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOTCOMMON_H__58831FB6_B113_43FA_B9CA_96FB84F2FCEE__INCLUDED_)
#define AFX_SLOTCOMMON_H__58831FB6_B113_43FA_B9CA_96FB84F2FCEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const long SErr_NoError             =  0; 
const long SErr_ASyncIOWrite        =  1; 
const long SErr_SyncIOWrite         =  2;  
const long SErr_AddItem             =  3; 
const long SErr_CdBlkTagMissing     =  4; 
const long SErr_CdBlkTagBadType     =  5;
const long SErr_Clamp               =  6; 
const long SErr_DBand               =  7; 
const long SErr_CmpOp               =  8; 
const long SErr_ConnectionFn        =  9; 
const long SErr_ConnectionOp        =  10;
const long SErr_FilterOp            =  11;
const long SErr_GetAbsFn            =  12;
const long SErr_GetCmpFn            =  13;
const long SErr_GetFn               =  14;
const long SErr_GetProfileFn        =  15;
const long SErr_GetRevFn            =  16;
const long SErr_GetSqrFn            =  17;
const long SErr_GetSqrtFn           =  18;
const long SErr_InvertOp            =  19;
const long SErr_MissingOPCTag       =  20;
const long SErr_Modifier            =  21;
const long SErr_NoiseOp             =  22;
const long SErr_OscillatorOp        =  23;
const long SErr_ProfileOp           =  24;
const long SErr_Range               =  25;
const long SErr_RangeOp             =  26;
const long SErr_RemoveItem          =  27;
const long SErr_ScaleOp             =  28;
const long SErr_SetClientHandles    =  29;
const long SErr_SetFn               =  30;
const long SErr_SetRevFn            =  31;
const long SErr_SetOnRiseFn         =  32;
const long SErr_SetOnFallFn         =  33;
const long SErr_SlotExcluded        =  34;
const long SErr_Span                =  35;
const long SErr_SqrOp               =  36;
const long SErr_SqrtOp              =  37;
const long SErr_TooManyConnectFns   =  38;
const long SErr_TooManyConnects     =  39;
const long SErr_Unknown             =  40;
const long SErr_NotLoaded           =  41;
const long SErr_MissingSimTag       =  42;
const long SErr_ReadSubs            =  43;
const long SErr_ProfNotDone         =  44;
const long SErr_InvalidFilename     =  45;
const long SErr_SetValue            =  46;
const long SErr_SetValueDevice      =  47;
const long SErr_ApplySpanInComing   =  48;
const long SErr_ApplyDBandInComing  =  49;
const long SErr_ApplySpanOutGoing   =  50;
const long SErr_ApplyRangeLink2Slot =  51;
const long SErr_PotentialRecursion  =  52;

extern LPCSTR SErr_String(long i);

/* IOMarshal Handle Functions */
const DWORD IOML_Link       = 0;
const DWORD IOML_Slot       = 1;
const DWORD IOML_CdBlk      = 2;
const DWORD IOML_Device     = 3;
const DWORD IOMSI_Value     = 0;
const DWORD IOMSI_HoldValue = 1;
const DWORD IOMSI_Hold      = 2;
const DWORD IOMSI_Type      = 3;
const DWORD IOMSI_Changes   = 4;
const DWORD IOMSI_Ignored   = 5;

const DWORD IOMChgFlag_Value     = 0x00000001;
const DWORD IOMChgFlag_HoldValue = 0x00000002;
const DWORD IOMChgFlag_Hold      = 0x00000004;
const DWORD IOMChgFlag_Type      = 0x00000008;
const DWORD IOMChgFlag_Changes   = 0x00000010;
const DWORD IOMChgFlag_Ignored   = 0x00000020;
const DWORD IOMChgFlag_All       = 0x0000003f;

inline DWORD MakeIOMHandle(DWORD List,DWORD DevItem,DWORD Item,DWORD SubItem) { return ((0xf0000000&((DWORD)List<<28))|(0x0f000000&((DWORD)DevItem<<24))|(0x00fffff0&((DWORD)Item<<4))|(0x0000000f&(DWORD)SubItem)); }
inline DWORD ExtractIOMList(DWORD Handle)    { return ((0xf0000000&(DWORD)Handle)>>28); }
inline DWORD ExtractIOMDevItem(DWORD Handle) { return ((0x0f000000&(DWORD)Handle)>>24); }
inline DWORD ExtractIOMItem(DWORD Handle)    { return ((0x00fffff0&(DWORD)Handle)>>04); }
inline DWORD ExtractIOMSubItem(DWORD Handle) { return ((0x0000000f&(DWORD)Handle)); }

#import "..\scdlib\vbscript.tlb" no_namespace rename("RGB","rgb")

// =======================================================================
//                                     
//                                     
//                                     
// =======================================================================
                                       
#define WMU_STOP                (WM_USER+3 )
#define WMU_START               (WM_USER+4 )
#define WMU_CFGBEGIN            (WM_USER+5 )
#define WMU_CFGEND              (WM_USER+6 )
#define WMU_SETSIMMODE          (WM_USER+7 )
#define WMU_ADDCDBLK            (WM_USER+8 )
#define WMU_ADDSLOT             (WM_USER+9 )
#define WMU_FLUSHQ              (WM_USER+10)

#define WMU_WRITEALL2DEVICES    (WM_USER+20)
#define WMU_GETSETVALUES        (WM_USER+21)

#define WMU_ADDERROR            (WM_USER+22)

#define WMU_OPENDOC             (WM_USER+30)
#define WMU_CLOSEDOC            (WM_USER+31)

#define WMU_SETSLOTCFG          (WM_USER+40)
#define WMU_SETLINKCFG          (WM_USER+41)
#define WMU_SETCDBLKCFG         (WM_USER+42)
#define WMU_SETDEVICECFG        (WM_USER+43)

#define WMU_UPDATEONESLOT       (WM_USER+50)
#define WMU_UPDATEONELINK       (WM_USER+51)
#define WMU_UPDATEONESLOTSTATE  (WM_USER+52)
#define WMU_UPDATEONELINKSTATE  (WM_USER+53)
#define WMU_UPDATESTATUS        (WM_USER+54)

#define WMU_SETVISIBLE          (WM_USER+60)
#define WMU_XFERCHANGEBLOCK     (WM_USER+61)
#define WMU_CHANGEMONITOR       (WM_USER+62)
#define WMU_SETHOLD             (WM_USER+63)
//#define WMU_SETSELECTION          (WM_USER+64)

#define WMU_EDITSTART           (WM_USER+70)
#define WMU_EDITSLOT            (WM_USER+71)
#define WMU_EDITEND             (WM_USER+72)

#define WMU_SAVESTATE           (WM_USER+73)
#define WMU_LOADSTATE           (WM_USER+74)

//#define WMU_FINDSTR             (WM_USER+73)

// =======================================================================
//
//
//
// =======================================================================

enum eViews { ViewSlots, ViewLinks, ViewCdBlks, ViewChanges, ViewEdits, MaxViews };
const LPCTSTR pszViewNames[MaxViews] =
  {
  "Slots",
  "Links",
  "CdBlks",
  "Changes",
  "Edits",
  };

// =======================================================================
//
//
//
// =======================================================================

#define TESTING 0
#if TESTING 
const long MaxWorkSlots=5; // increment later to say 256
const long MaxHistoryListLen=50; 
const long MaxErrorsListLen=10; 
#else
const long MaxWorkSlots=1024; 
const long MaxHistoryListLen=2048; 
const long MaxErrorsListLen=1024; 
#endif

const long MaxChangesInBlock=100;
const long MaxErrorsInBlock=100;

//const DWORD gc_DisplayUpdateTimer=500;

const DWORD InfiniteDelay=0xffffffff;

extern LPCSTR   TypeToString(WORD vt);
extern LPCSTR   ActionToString(WORD A);

extern bool     gs_bAsHex;

extern void     ReportError(LPCSTR Tag, HRESULT hr, LPCSTR Fmt, ...);
extern void     ReportErrorBox(HRESULT hr, LPCSTR Fmt, ...);
extern bool     VariantsEqual(const VARIANT* pDst, const VARIANT* pSrc);
extern LPCSTR   VariantToString(VARIANT value, CString &strText, bool AsHex = false);
extern LPCSTR   TimeStampToString(FILETIME Ft, CString &strText, bool AddmSecs, FILETIME * pRef);
extern LPCSTR   VTAsString(long vt);
extern void     StringToVariant(VARTYPE VT, CString &strText, COleVariant &V, bool AsHex);

// =======================================================================
//
//
//
// =======================================================================

class CLongArray : public CArray <long, long> {};

template <class T>
class CKwikList
  {
  protected:
    T m_pHead;
    T m_pTail;
    long m_lCount;
    long m_lStats;
    CCriticalSection m_Sect;

  public:
    CKwikList()
      {
      m_pHead=NULL;
      m_pTail=NULL;
      m_lCount=0;
      m_lStats=0;
      }

    void AddHead(T p)
      {
      CSingleLock Lk(&m_Sect, true);
      p->m_pNext=m_pHead;
      m_pHead=p;
      if (!m_pTail)
        m_pTail=p;
      m_lCount++;
      m_lStats++;
      }

    void AddTail(T p)
      {
      CSingleLock Lk(&m_Sect, true);
      if (!m_pHead)
        m_pHead=p;
      if (m_pTail)
        m_pTail->m_pNext=p;
      m_pTail=p;
      m_lCount++;
      m_lStats++;
      }

    void AddAfter(T pPrev, T p)
      {
      CSingleLock Lk(&m_Sect, true);
      if (pPrev!=m_pTail)
        {// Add After
        p->m_pNext=pPrev->m_pNext;
        pPrev->m_pNext=p;
        m_lCount++;
        m_lStats++;
        }
      else
        AddTail(p);
      }
    
    T Head() 
      { 
      CSingleLock Lk(&m_Sect, true);
      return m_pHead; 
      };
    T RemoveHead()
      {
      CSingleLock Lk(&m_Sect, true);
      T p=m_pHead;
      if (m_pHead)
        {
        m_pHead=m_pHead->m_pNext;
        if (m_pTail==p)
          m_pTail=NULL;
        p->m_pNext=NULL;
        m_lCount--;
        }
      return p;
      };
    long Count() { return m_lCount; };
    long Stats() { return m_lStats; };
    long Clear()
      {
      CSingleLock Lk(&m_Sect, true);
      long n=m_lCount;
      T p;
      while ((p=RemoveHead())!=0)
        {
        delete p;
        };
      return n;
      }
    void Lock() { m_Sect.Lock(); };
    void UnLock() { m_Sect.Unlock(); };

  };

// =======================================================================
//
//
//
// =======================================================================

class CDelayBlockItem
  {
  public:
    DWORD       m_dwTime;
    COleVariant m_Value;
  };

class CDelayBlock
  {
  public:
    CDelayBlock();
    bool         Configured() { return m_OnRise.GetSize()>0 || m_OnFall.GetSize()>0; }
  
  public:
    bool         m_UseValues;
    CArray<CDelayBlockItem, CDelayBlockItem&> m_OnRise, m_OnFall;
  };

// =======================================================================
//
//
//
// =======================================================================

class CFullValue
  {
  public:
    COleVariant m_vValue;
    WORD        m_wQuality;
    FILETIME    m_ftTimeStamp;
    
    CFullValue(VARIANT &Value, WORD Quality, FILETIME TimeStamp):
      m_vValue(Value),
      m_wQuality(Quality),
      m_ftTimeStamp(TimeStamp)
      {
      };
    CFullValue(VARIANT &Value, WORD Quality):
      m_vValue(Value)
      {
      m_wQuality=Quality;
      CoFileTimeNow(&m_ftTimeStamp);
      };
    CFullValue(WORD Quality=OPC_QUALITY_BAD)
      {
      m_wQuality=Quality;
      CoFileTimeNow(&m_ftTimeStamp);
      };
    CFullValue & operator =(const CFullValue & V)
      {
      m_vValue=V.m_vValue;
      m_wQuality=V.m_wQuality;
      m_ftTimeStamp=V.m_ftTimeStamp;
      return *this;
      }
    operator COleVariant &() { return m_vValue; };
    operator FILETIME &() { return m_ftTimeStamp; };
    operator double &() { return m_vValue.dblVal; };
    operator long &() { return m_vValue.lVal; };
    VARTYPE Type() { return m_vValue.vt; };
    HRESULT ChangeType(VARTYPE T, VARIANT *pSrc=NULL) 
      {
      HRESULT H=VariantChangeType(&m_vValue, pSrc?pSrc:&m_vValue, 0, T); 
      return H;
      };

    int ChangeDirection(CFullValue & V)
      {
      switch (Type())
        {
        case VT_R4  : { double X=(V.m_vValue.fltVal     - m_vValue.fltVal); return X>0?1:X<0?-1:0 ;}
        case VT_R8  : { double X=(V.m_vValue.dblVal     - m_vValue.dblVal ); return X>0?1:X<0?-1:0 ;}
        case VT_I1  : { long X=((long)V.m_vValue.cVal   - m_vValue.cVal   ); return X>0?1:X<0?-1:0 ;};
        case VT_I2  : { long X=((long)V.m_vValue.iVal   - m_vValue.iVal   ); return X>0?1:X<0?-1:0 ;};
        case VT_I4  : { long X=((long)V.m_vValue.lVal   - m_vValue.lVal   ); return X>0?1:X<0?-1:0 ;};
        case VT_UI1 : { long X=((long)V.m_vValue.bVal   - m_vValue.bVal   ); return X>0?1:X<0?-1:0 ;};
        case VT_UI2 : { long X=((long)V.m_vValue.uiVal  - m_vValue.uiVal  ); return X>0?1:X<0?-1:0 ;};
        case VT_UI4 : { long X=((long)V.m_vValue.ulVal  - m_vValue.ulVal  ); return X>0?1:X<0?-1:0 ;};
        case VT_BOOL: { return V.m_vValue.boolVal==m_vValue.boolVal?0: m_vValue.boolVal?1:-1; };
        }
      return 0;
      }
    int ChangeDirectionInit()
      {
      switch (Type())
        {
        case VT_R4  : { double X=(m_vValue.fltVal     - 0); return X>0?1:-1 ;}
        case VT_R8  : { double X=(m_vValue.dblVal     - 0); return X>0?1:-1 ;}
        case VT_I1  : { long X=((long)m_vValue.cVal   - 0); return X>0?1:-1 ;};
        case VT_I2  : { long X=((long)m_vValue.iVal   - 0); return X>0?1:-1 ;};
        case VT_I4  : { long X=((long)m_vValue.lVal   - 0); return X>0?1:-1 ;};
        case VT_UI1 : { long X=((long)m_vValue.bVal   - 0); return X>0?1:-1 ;};
        case VT_UI2 : { long X=((long)m_vValue.uiVal  - 0); return X>0?1:-1 ;};
        case VT_UI4 : { long X=((long)m_vValue.ulVal  - 0); return X>0?1:-1 ;};
        case VT_BOOL: { return m_vValue.boolVal!=0?1:-1; };
        }
      return 0;
      }

  };

inline bool IsNumDataVT(VARTYPE VT) { return VT==VT_R4 || VT==VT_R8 || VT==VT_I1 || VT==VT_I2 || VT==VT_I4 || VT==VT_UI1 || VT==VT_UI2 || VT==VT_UI4; }
inline bool IsBooleanDataVT(VARTYPE VT) { return VT==VT_BOOL; }
inline bool IsFloatDataVT(VARTYPE VT) { return VT==VT_R4 || VT==VT_R8; }
inline bool IsSignedDataVT(VARTYPE VT) { return VT==VT_I1 || VT==VT_I2 || VT==VT_I4; }
inline bool IsUnsignedDataVT(VARTYPE VT) { return VT==VT_UI1 || VT==VT_UI2 || VT==VT_UI4; }

// =======================================================================
//
//
//
// =======================================================================

enum eConnSrcDst 
  {
    eCSD_Null, 
    eCSD_Slot, 
    eCSD_Device, 
    eCSD_Link, 
    eCSD_Simulator, 
    //eCSD_Connect, 
    eCSD_CdBlk, 
    eCSD_SlotConn, 
    eCSD_Manual,
    eCSD_File,
    eCSD_Default,
  };

extern LPCSTR SrcDstString(eConnSrcDst e);

inline long MakeSlotConnIndex(long SlotIndex, long ConnIndex) { return (SlotIndex & 0x00ffffff) | (ConnIndex << 24) & 0x7f000000; }
inline long GetSlotIndex(long Index) { return (Index & 0x00ffffff); }
inline long GetConnIndex(long Index) { return (Index & 0x7f000000) >> 24; }

class CChangeItem : public CFullValue
  {
  public:
	  CChangeItem();
    CChangeItem(eConnSrcDst Src, long SrcInx, eConnSrcDst Dst, long DstLink, OPCHANDLE hServer, DWORD TransID, CFullValue &Value, bool OverrideHold/*=false*/, bool Refresh=false);

    eConnSrcDst   m_eSrc;
    eConnSrcDst   m_eDst;
    DWORD         m_dwTransactionID; 
    bool          m_bRefresh;

    long          m_lSrcInx;
    long          m_lDstInx;
    OPCHANDLE     m_hServer;

    DWORD         m_dwDelayTimer;

    CChangeItem * m_pNext; // Simple List to not play with the heap - using spares for allocation

    static DWORD  sm_dwNumber; 
    DWORD         m_dwNumber; 

    bool          m_bOverrideHold;

    bool          PeriperalIO() 
      { 
      return (m_eSrc==eCSD_Simulator || m_eSrc==eCSD_Device || m_eSrc==eCSD_Manual  || m_eSrc==eCSD_File|| 
              m_eDst==eCSD_Simulator || m_eDst==eCSD_Device || m_eDst==eCSD_Manual); 
      };
    
    void          Advance(DWORD DT);

  DEFINE_SPARES(CChangeItem);
  };

class CChangeBlock 
  {
  public:
    long     m_nChanges;
    CChangeItem* m_Changes[MaxChangesInBlock];
    CChangeBlock ()
      {
      m_nChanges=0;
      }

    bool HasSpace() { return m_nChanges<MaxChangesInBlock; };
    void Add (CChangeItem * p) { p->m_pNext=NULL; m_Changes[m_nChanges++]=p; };
  DEFINE_SPARES(CChangeBlock);
  };

// =======================================================================
//
//
//
// =======================================================================

class CErrorItem
  {
public:
    CErrorItem();
    CErrorItem(LPCSTR Tag, long No, FILETIME TimeStamp, LPCSTR Str);

    CString       m_sError;
    CString       m_sTag;
    FILETIME      m_ftTimeStamp;
    long          m_lNo;

    CErrorItem * m_pNext; // Simple List to not play with the heap - using spares for allocation

  DEFINE_SPARES(CErrorItem);
  };

// =======================================================================
//
//
//
// =======================================================================

class CStatusInfoBlock 
  {
  public:
    DWORD   m_dwSlots;
    DWORD   m_dwLinks;
    DWORD   m_dwChanges;
    DWORD   m_dwDelays;
    DWORD   m_dwTotChgs;
    DWORD   m_dwHolds;

    DWORD   m_nScdSlotChgsIn;
    DWORD   m_nScdSlotChgsOut;
    DWORD   m_nScdLinkChgsIn;
    DWORD   m_nScdLinkChgsOut;
    DWORD   m_nDeviceChgsIn;
    DWORD   m_nDeviceChgsOutInt;
    DWORD   m_nDeviceChgsOutFlt;
    int     m_nIntWritesBusy;
    int     m_nFltWritesBusy;
    int     m_nFltWritesSkip;
  };

class CSlotValueSet
  {
  public:
    CSlotValueSet() {};
    CSlotValueSet(LPCTSTR Values) 
      {
      SetValueSet(Values);
      };
    CSlotValueSet(const CSlotValueSet & V)
      {
      m_Values.SetSize(V.m_Values.GetSize());
      for (int i=0; i<V.m_Values.GetSize(); i++)
        m_Values[i]=V.m_Values[i];
      };
    CSlotValueSet & operator=(const CSlotValueSet & V)
      {
      m_Values.SetSize(V.m_Values.GetSize());
      for (int i=0; i<V.m_Values.GetSize(); i++)
        m_Values[i]=V.m_Values[i];
      return *this;
      };
  
  void SetValueSet(LPCTSTR Values);
  void SetValueID(LPCTSTR ValueID, COleVariant & FullValue, eConnSrcDst Dst, int Index);

  private:
    CStringArray m_Values;
  
  };

// =======================================================================
//
//
//
// =======================================================================

enum  eFilterWhat { eFilterTheTag, eFilterSimTag, eFilterOPCTag, eFilterType, eMaxSelectStrings };
enum  eFilterHow  { eFilterContains, eFilterWild, eFilterRegExp, eFilterRuleCount };
const LPCTSTR eFilterHowNames[eFilterRuleCount] = { "Contains","Wildcards","Regular Expressions"};

class CSelection
  {
  public:
    
    CSelection();
    CSelection(const CSelection & Other);
    ~CSelection();

    CSelection & operator=(const CSelection & Other);
    void          SetHow(eFilterHow How);
    bool          InFilter(LPCTSTR Tag, LPCTSTR SimTag, LPCTSTR OPCTag, LPCTSTR Type, bool HasError, bool HasHold);

  //protected:
    bool          m_bOn;
    bool          m_bCaseSens;
    bool          m_bAndClause;
    bool          m_bErrorsOnly;
    bool          m_bHoldsOnly;
    eFilterHow    m_eHow;
    CString       m_sStr[eMaxSelectStrings];
    CString       m_sStrL[eMaxSelectStrings];
    IRegExpPtr *  m_pRE[eMaxSelectStrings];
  };

// =======================================================================
//
//
//
// =======================================================================

#endif // !defined(AFX_SLOTCOMMON_H__58831FB6_B113_43FA_B9CA_96FB84F2FCEE__INCLUDED_)
