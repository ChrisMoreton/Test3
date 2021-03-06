//================== SysCAD - Copyright Kenwalt (Pty) Ltd ===================
// $Nokeywords: $
//===========================================================================
// SysCAD Copyright Kenwalt (Pty) Ltd 1992

#ifndef  __SCDTEMPL_H
#define  __SCDTEMPL_H

#ifndef __AFXTEMPL_H__
  #include <afxtempl.h> // "xafxtempl.h"
#endif

#if !defined(SCDLIB)
  #define DllImportExport DllImport
#else
  #define DllImportExport
#endif

//===========================================================================
//
//
//
//===========================================================================

template<> UINT AFXAPI HashKey<LPTSTR> (LPTSTR Key);
template<> UINT AFXAPI HashKey<LPCTSTR> (LPCTSTR Key);
template<> BOOL AFXAPI CompareElements<LPTSTR, LPTSTR> (const LPTSTR* E1, const LPTSTR* E2);
template<> BOOL AFXAPI CompareElements<LPCTSTR, LPCTSTR> (const LPCTSTR* E1, const LPCTSTR* E2);

#undef DllImportExport

// =========================================================================

template<class TYPE, class ARG_TYPE>
class CSCDList : public CList <TYPE, ARG_TYPE>
{
public:
  VOID RemoveAllToFreeList() { while (!IsEmpty()) RemoveAt(GetHeadPosition()); };
};

// =========================================================================

template<class CLIST, class ARG_TYPE>
class CSCDListIter : public CObject
{
protected:
  CLIST &List;
  POSITION pos;
  flag bFwd;

public:
// Construction
	CSCDListIter(CLIST &Lst) : List(Lst) {pos=NULL;};

  ARG_TYPE First() { bFwd=1; pos = List.GetHeadPosition(); return (pos) ? &(List.GetNext(pos)) : NULL; };
  ARG_TYPE Next()  { return (pos) ? &(List.GetNext(pos)) : NULL; };
  ARG_TYPE Last()  { bFwd=0; pos = List.GetTailPosition(); return (pos) ? &(List.GetPrev(pos)) : NULL; };
  ARG_TYPE Prev()  { return (pos) ? &(List.GetPrev(pos)) : NULL; };
  ARG_TYPE MakeCurrent(POSITION Pos) { pos=Pos; return (bFwd ? Next() : Prev()); };
//  ARG_TYPE First() { pos = List.GetHeadPosition(); return (pos) ? List.GetNext(pos) : NULL; };
//  ARG_TYPE Next()  { return (pos) ? List.GetNext(pos) : NULL; };
//  ARG_TYPE Last()  { pos = List.GetTailPosition(); return (pos) ? List.GetPrev(pos) : NULL; };
//  ARG_TYPE Prev()  { return (pos) ? List.GetPrev(pos) : NULL; };
};

// =========================================================================

template<class CLIST, class ARG_TYPE>
class CSCDListIterWithPos : public CObject
{
protected:
  CLIST &List;
  POSITION pos, ppos;
  flag bFwd;

public:
// Construction
	CSCDListIterWithPos(CLIST &Lst) : List(Lst) {ppos=pos=NULL;};

  ARG_TYPE First() { bFwd=1; ppos = pos = List.GetHeadPosition(); return (pos) ? &(List.GetNext(pos)) : NULL; };
  ARG_TYPE Next()  { ppos = pos; return (pos) ? &(List.GetNext(pos)) : NULL; };
  ARG_TYPE Last()  { bFwd=0; ppos = pos = List.GetTailPosition(); return (pos) ? &(List.GetPrev(pos)) : NULL; };
  ARG_TYPE Prev()  { ppos = pos; return (pos) ? &(List.GetPrev(pos)) : NULL; };
  ARG_TYPE MakeCurrent(POSITION Pos) { pos=Pos; return (bFwd ? Next() : Prev()); };
//  ARG_TYPE First() { ppos = pos = List.GetHeadPosition(); return (pos) ? List.GetNext(pos) : NULL; };
//  ARG_TYPE Next()  { ppos = pos; return (pos) ? List.GetNext(pos) : NULL; };
//  ARG_TYPE Last()  { ppos = pos = List.GetTailPosition(); return (pos) ? List.GetPrev(pos) : NULL; };
//  ARG_TYPE Prev()  { ppos = pos; return (pos) ? List.GetPrev(pos) : NULL; };
  POSITION Pos()   { return ppos; };
};

// =========================================================================

template<class CLIST, class ARG_TYPE>
class CSCDPtrListIter : public CObject
{
protected:
  CLIST &List;
  POSITION pos;
  flag bFwd;

public:
// Construction
	CSCDPtrListIter(CLIST &Lst) : List(Lst) { pos=NULL; };

  ARG_TYPE First() { bFwd=1; pos = List.GetHeadPosition(); return (pos) ? (List.GetNext(pos)) : NULL; };
  ARG_TYPE Next()  { return (pos) ? (List.GetNext(pos)) : NULL; };
  ARG_TYPE Last()  { bFwd=0; pos = List.GetTailPosition(); return (pos) ? (List.GetPrev(pos)) : NULL; };
  ARG_TYPE Prev()  { return (pos) ? (List.GetPrev(pos)) : NULL; };
  ARG_TYPE MakeCurrent(POSITION Pos) { pos=Pos; return (bFwd ? Next() : Prev()); };
//  ARG_TYPE First() { pos = List.GetHeadPosition(); return (pos) ? List.GetNext(pos) : NULL; };
//  ARG_TYPE Next()  { return (pos) ? List.GetNext(pos) : NULL; };
//  ARG_TYPE Last()  { pos = List.GetTailPosition(); return (pos) ? List.GetPrev(pos) : NULL; };
//  ARG_TYPE Prev()  { return (pos) ? List.GetPrev(pos) : NULL; };
};

// =========================================================================

template<class CLIST, class ARG_TYPE>
class CSCDPtrListIterWithPos : public CObject
{
protected:
  CLIST &List;
  POSITION pos, ppos;
  flag bFwd;

public:
// Construction
	CSCDPtrListIterWithPos(CLIST &Lst) : List(Lst) {ppos=pos=NULL;};

  ARG_TYPE First() { bFwd=1; ppos = pos = List.GetHeadPosition(); return (pos) ? (List.GetNext(pos)) : NULL; };
  ARG_TYPE Next()  { ppos = pos; return (pos) ? (List.GetNext(pos)) : NULL; };
  ARG_TYPE Last()  { bFwd=0; ppos = pos = List.GetTailPosition(); return (pos) ? (List.GetPrev(pos)) : NULL; };
  ARG_TYPE Prev()  { ppos = pos; return (pos) ? (List.GetPrev(pos)) : NULL; };
  ARG_TYPE MakeCurrent(POSITION Pos) { pos=Pos; return (bFwd ? Next() : Prev()); };
//  ARG_TYPE First() { ppos = pos = List.GetHeadPosition(); return (pos) ? List.GetNext(pos) : NULL; };
//  ARG_TYPE Next()  { ppos = pos; return (pos) ? List.GetNext(pos) : NULL; };
//  ARG_TYPE Last()  { ppos = pos = List.GetTailPosition(); return (pos) ? List.GetPrev(pos) : NULL; };
//  ARG_TYPE Prev()  { ppos = pos; return (pos) ? List.GetPrev(pos) : NULL; };
  POSITION Pos()   { return ppos; };
};


/////////////////////////////////////////////////////////////////////////////
// CLockedList<TYPE, ARG_TYPE>

template<class TYPE, class ARG_TYPE>
class CLockedList : public CObject
{
protected:
	struct CNode
	{
		CNode* pNext;
		CNode* pPrev;
		TYPE data;
	};
public:
// Construction
	CLockedList(int nBlockSize = 10);

// Attributes (head and tail)
	// count of elements
	int GetCount() const;
	BOOL IsEmpty() const;

	// peek at head or tail
	TYPE& GetHead();
	TYPE GetHead() const;
	TYPE& GetTail();
	TYPE GetTail() const;

// Operations
	// get head or tail (and remove it) - don't call on empty list !
	TYPE RemoveHead();
	TYPE RemoveTail();

	// add before head or after tail
	POSITION AddHead(ARG_TYPE newElement);
	POSITION AddTail(ARG_TYPE newElement);

	// add another list of elements before head or after tail
	void AddHead(CLockedList* pNewList);
	void AddTail(CLockedList* pNewList);

	// remove all elements
	void RemoveAll();

	// iteration
	POSITION GetHeadPosition() const;
	POSITION GetTailPosition() const;
	TYPE& GetNext(POSITION& rPosition); // return *Position++
	TYPE GetNext(POSITION& rPosition) const; // return *Position++
	TYPE& GetPrev(POSITION& rPosition); // return *Position--
	TYPE GetPrev(POSITION& rPosition) const; // return *Position--

	// getting/modifying an element at a given position
	TYPE& GetAt(POSITION position);
	TYPE GetAt(POSITION position) const;
	void SetAt(POSITION pos, ARG_TYPE newElement);
	void RemoveAt(POSITION position);

	// inserting before or after a given position
	POSITION InsertBefore(POSITION position, ARG_TYPE newElement);
	POSITION InsertAfter(POSITION position, ARG_TYPE newElement);

	// helper functions (note: O(n) speed)
	POSITION Find(ARG_TYPE searchValue, POSITION startAfter = NULL) const;
		// defaults to starting at the HEAD, return NULL if not found
	POSITION FindIndex(int nIndex) const;
		// get the 'nIndex'th element (may return NULL)

// Implementation
protected:
	CNode* m_pNodeHead;
	CNode* m_pNodeTail;
	int m_nCount;
	CNode* m_pNodeFree;
	struct CPlex* m_pBlocks;
	int m_nBlockSize;
  CCriticalSection m_Sect;

	CNode* NewNode(CNode*, CNode*);
	void FreeNode(CNode*);

public:
	~CLockedList();
	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CLockedList<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
AFX_INLINE int CLockedList<TYPE, ARG_TYPE>::GetCount() const
	{ CSingleLock L((CSyncObject*)&m_Sect,TRUE);
    return m_nCount; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE BOOL CLockedList<TYPE, ARG_TYPE>::IsEmpty()  const
	{ CSingleLock L((CSyncObject*)&m_Sect,TRUE);
    return m_nCount == 0; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE& CLockedList<TYPE, ARG_TYPE>::GetHead()
	{ CSingleLock L(&m_Sect,TRUE);
    ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE CLockedList<TYPE, ARG_TYPE>::GetHead() const
	{ CSingleLock L((CSyncObject*)&m_Sect,TRUE);
    ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE& CLockedList<TYPE, ARG_TYPE>::GetTail()
	{ ASSERT(m_pNodeTail != NULL);
		CSingleLock L(&m_Sect,TRUE);
    return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE CLockedList<TYPE, ARG_TYPE>::GetTail() const
	{ ASSERT(m_pNodeTail != NULL);
		CSingleLock L((CSyncObject*)&m_Sect,TRUE);
    return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE POSITION CLockedList<TYPE, ARG_TYPE>::GetHeadPosition() const
	{ CSingleLock L((CSyncObject*)&m_Sect,TRUE);
    return (POSITION) m_pNodeHead; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE POSITION CLockedList<TYPE, ARG_TYPE>::GetTailPosition() const
	{ CSingleLock L((CSyncObject*)&m_Sect,TRUE);
    return (POSITION) m_pNodeTail; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE& CLockedList<TYPE, ARG_TYPE>::GetNext(POSITION& rPosition) // return *Position++
	{ CSingleLock L(&m_Sect,TRUE);
    CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE CLockedList<TYPE, ARG_TYPE>::GetNext(POSITION& rPosition) const // return *Position++
	{ CSingleLock L((CSyncObject*)&m_Sect,TRUE);
    CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE& CLockedList<TYPE, ARG_TYPE>::GetPrev(POSITION& rPosition) // return *Position--
	{ CSingleLock L(&m_Sect,TRUE);
    CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE CLockedList<TYPE, ARG_TYPE>::GetPrev(POSITION& rPosition) const // return *Position--
	{ CSingleLock L((CSyncObject*)&m_Sect,TRUE);
    CNode* pNode = (CNode*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE& CLockedList<TYPE, ARG_TYPE>::GetAt(POSITION position)
	{ CSingleLock L(&m_Sect,TRUE);
    CNode* pNode = (CNode*) position;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE CLockedList<TYPE, ARG_TYPE>::GetAt(POSITION position) const
	{ CSingleLock L((CSyncObject*)&m_Sect,TRUE);
    CNode* pNode = (CNode*) position;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE void CLockedList<TYPE, ARG_TYPE>::SetAt(POSITION pos, ARG_TYPE newElement)
	{ CSingleLock L(&m_Sect,TRUE);
    CNode* pNode = (CNode*) pos;
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		pNode->data = newElement; }

template<class TYPE, class ARG_TYPE>
CLockedList<TYPE, ARG_TYPE>::CLockedList(int nBlockSize)
{
  CSingleLock L(&m_Sect,TRUE);

	ASSERT(nBlockSize > 0);

	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
}

template<class TYPE, class ARG_TYPE>
void CLockedList<TYPE, ARG_TYPE>::RemoveAll()
{
	CSingleLock L(&m_Sect,TRUE);

  ASSERT_VALID(this);

	// destroy elements
	CNode* pNode;
	for (pNode = m_pNodeHead; pNode != NULL; pNode = pNode->pNext)
    (&pNode->data)->~TYPE();

	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

template<class TYPE, class ARG_TYPE>
CLockedList<TYPE, ARG_TYPE>::~CLockedList()
{
	CSingleLock L(&m_Sect,TRUE);

  RemoveAll();
	ASSERT(m_nCount == 0);
}

/////////////////////////////////////////////////////////////////////////////
// Node helpers
//
// Implementation note: CNode's are stored in CPlex blocks and
//  chained together. Free blocks are maintained in a singly linked list
//  using the 'pNext' member of CNode with 'm_pNodeFree' as the head.
//  Used blocks are maintained in a doubly linked list using both 'pNext'
//  and 'pPrev' as links and 'm_pNodeHead' and 'm_pNodeTail'
//   as the head/tail.
//
// We never free a CPlex block unless the List is destroyed or RemoveAll()
//  is used - so the total number of CPlex blocks may grow large depending
//  on the maximum past size of the list.
//

template<class TYPE, class ARG_TYPE>
typename CLockedList<TYPE, ARG_TYPE>::CNode*
CLockedList<TYPE, ARG_TYPE>::NewNode(typename CLockedList::CNode* pPrev, typename CLockedList::CNode* pNext)
{
	CSingleLock L(&m_Sect,TRUE);

  if (m_pNodeFree == NULL)
	{
		// add another block
		CPlex* pNewBlock = CPlex::Create(m_pBlocks, m_nBlockSize,
				 sizeof(CNode));

		// chain them into free list
		CNode* pNode = (CNode*) pNewBlock->data();
		// free in reverse order to make it easier to debug
		pNode += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pNode--)
		{
			pNode->pNext = m_pNodeFree;
			m_pNodeFree = pNode;
		}
	}
	ASSERT(m_pNodeFree != NULL);  // we must have something

	CLockedList::CNode* pNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNode->pPrev = pPrev;
	pNode->pNext = pNext;
	m_nCount++;
	ASSERT(m_nCount > 0);  // make sure we don't overflow

  (&pNode->data)->TYPE();
  return pNode;
}

template<class TYPE, class ARG_TYPE>
void CLockedList<TYPE, ARG_TYPE>::FreeNode(typename typename CLockedList::CNode* pNode)
{
	CSingleLock L(&m_Sect,TRUE);

  (&pNode->data)->~TYPE();
	pNode->pNext = m_pNodeFree;
	m_pNodeFree = pNode;
	m_nCount--;
	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	// if no more elements, cleanup completely
	if (m_nCount == 0)
		RemoveAll();
}

template<class TYPE, class ARG_TYPE>
POSITION CLockedList<TYPE, ARG_TYPE>::AddHead(ARG_TYPE newElement)
{
	CSingleLock L(&m_Sect,TRUE);

  ASSERT_VALID(this);

	CNode* pNewNode = NewNode(NULL, m_pNodeHead);
	pNewNode->data = newElement;
	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = pNewNode;
	else
		m_pNodeTail = pNewNode;
	m_pNodeHead = pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CLockedList<TYPE, ARG_TYPE>::AddTail(ARG_TYPE newElement)
{
	CSingleLock L(&m_Sect,TRUE);

  ASSERT_VALID(this);

	CNode* pNewNode = NewNode(m_pNodeTail, NULL);
	pNewNode->data = newElement;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;
	m_pNodeTail = pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
void CLockedList<TYPE, ARG_TYPE>::AddHead(CLockedList* pNewList)
{
	CSingleLock L(&m_Sect,TRUE);

  ASSERT_VALID(this);

	ASSERT(pNewList != NULL);
	ASSERT_VALID(pNewList);

	// add a list of same elements to head (maintain order)
	POSITION pos = pNewList->GetTailPosition();
	while (pos != NULL)
		AddHead(pNewList->GetPrev(pos));
}

template<class TYPE, class ARG_TYPE>
void CLockedList<TYPE, ARG_TYPE>::AddTail(CLockedList* pNewList)
{
	CSingleLock L(&m_Sect,TRUE);

  ASSERT_VALID(this);
	ASSERT(pNewList != NULL);
	ASSERT_VALID(pNewList);

	// add a list of same elements
	POSITION pos = pNewList->GetHeadPosition();
	while (pos != NULL)
		AddTail(pNewList->GetNext(pos));
}

template<class TYPE, class ARG_TYPE>
TYPE CLockedList<TYPE, ARG_TYPE>::RemoveHead()
{
	CSingleLock L(&m_Sect,TRUE);

  ASSERT_VALID(this);
	ASSERT(m_pNodeHead != NULL);  // don't call on empty list !!!
	ASSERT(AfxIsValidAddress(m_pNodeHead, sizeof(CNode)));

	CNode* pOldNode = m_pNodeHead;
	TYPE returnValue = pOldNode->data;

	m_pNodeHead = pOldNode->pNext;
	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = NULL;
	else
		m_pNodeTail = NULL;
	FreeNode(pOldNode);
	return returnValue;
}

template<class TYPE, class ARG_TYPE>
TYPE CLockedList<TYPE, ARG_TYPE>::RemoveTail()
{
	CSingleLock L(&m_Sect,TRUE);

  ASSERT_VALID(this);
	ASSERT(m_pNodeTail != NULL);  // don't call on empty list !!!
	ASSERT(AfxIsValidAddress(m_pNodeTail, sizeof(CNode)));

	CNode* pOldNode = m_pNodeTail;
	TYPE returnValue = pOldNode->data;

	m_pNodeTail = pOldNode->pPrev;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = NULL;
	else
		m_pNodeHead = NULL;
	FreeNode(pOldNode);
	return returnValue;
}

template<class TYPE, class ARG_TYPE>
POSITION CLockedList<TYPE, ARG_TYPE>::InsertBefore(POSITION position, ARG_TYPE newElement)
{
	CSingleLock L(&m_Sect,TRUE);

  ASSERT_VALID(this);

	if (position == NULL)
		return AddHead(newElement); // insert before nothing -> head of the list

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	CNode* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
	pNewNode->data = newElement;

	if (pOldNode->pPrev != NULL)
	{
		ASSERT(AfxIsValidAddress(pOldNode->pPrev, sizeof(CNode)));
		pOldNode->pPrev->pNext = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeHead);
		m_pNodeHead = pNewNode;
	}
	pOldNode->pPrev = pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CLockedList<TYPE, ARG_TYPE>::InsertAfter(POSITION position, ARG_TYPE newElement)
{
	CSingleLock L(&m_Sect,TRUE);

  ASSERT_VALID(this);

	if (position == NULL)
		return AddTail(newElement); // insert after nothing -> tail of the list

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	ASSERT(AfxIsValidAddress(pOldNode, sizeof(CNode)));
	CNode* pNewNode = NewNode(pOldNode, pOldNode->pNext);
	pNewNode->data = newElement;

	if (pOldNode->pNext != NULL)
	{
		ASSERT(AfxIsValidAddress(pOldNode->pNext, sizeof(CNode)));
		pOldNode->pNext->pPrev = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeTail);
		m_pNodeTail = pNewNode;
	}
	pOldNode->pNext = pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
void CLockedList<TYPE, ARG_TYPE>::RemoveAt(POSITION position)
{
	CSingleLock L(&m_Sect,TRUE);

  ASSERT_VALID(this);

	CNode* pOldNode = (CNode*) position;
	ASSERT(AfxIsValidAddress(pOldNode, sizeof(CNode)));

	// remove pOldNode from list
	if (pOldNode == m_pNodeHead)
	{
		m_pNodeHead = pOldNode->pNext;
	}
	else
	{
		ASSERT(AfxIsValidAddress(pOldNode->pPrev, sizeof(CNode)));
		pOldNode->pPrev->pNext = pOldNode->pNext;
	}
	if (pOldNode == m_pNodeTail)
	{
		m_pNodeTail = pOldNode->pPrev;
	}
	else
	{
		ASSERT(AfxIsValidAddress(pOldNode->pNext, sizeof(CNode)));
		pOldNode->pNext->pPrev = pOldNode->pPrev;
	}
	FreeNode(pOldNode);
}

template<class TYPE, class ARG_TYPE>
POSITION CLockedList<TYPE, ARG_TYPE>::FindIndex(int nIndex) const
{
	CSingleLock L((CSyncObject*)&m_Sect,TRUE);

  ASSERT_VALID(this);

	if (nIndex >= m_nCount || nIndex < 0)
		return NULL;  // went too far

	CNode* pNode = m_pNodeHead;
	while (nIndex--)
	{
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		pNode = pNode->pNext;
	}
	return (POSITION) pNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CLockedList<TYPE, ARG_TYPE>::Find(ARG_TYPE searchValue, POSITION startAfter) const
{
	CSingleLock L((CSyncObject*)&m_Sect,TRUE);

  ASSERT_VALID(this);

	CNode* pNode = (CNode*) startAfter;
	if (pNode == NULL)
	{
		pNode = m_pNodeHead;  // start at head
	}
	else
	{
		ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
		pNode = pNode->pNext;  // start after the one specified
	}

	for (; pNode != NULL; pNode = pNode->pNext)
		if (CompareElements<TYPE>(&pNode->data, &searchValue))
			return (POSITION)pNode;
	return NULL;
}

template<class TYPE, class ARG_TYPE>
void CLockedList<TYPE, ARG_TYPE>::Serialize(CArchive& ar)
{
	CSingleLock L(&m_Sect,TRUE);

  ASSERT_VALID(this);

	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar.WriteCount(m_nCount);
		for (CNode* pNode = m_pNodeHead; pNode != NULL; pNode = pNode->pNext)
		{
			ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			SerializeElements<TYPE>(ar, &pNode->data, 1);
		}
	}
	else
	{
		DWORD nNewCount = ar.ReadCount();
		while (nNewCount--)
		{
			TYPE newData;
			SerializeElements<TYPE>(ar, &newData, 1);
			AddTail(newData);
		}
	}
}

#ifdef _DEBUG
template<class TYPE, class ARG_TYPE>
void CLockedList<TYPE, ARG_TYPE>::Dump(CDumpContext& dc) const
{
	CSingleLock L((CSyncObject*)&m_Sect,TRUE);

  CObject::Dump(dc);

	dc << "with " << m_nCount << " elements";
	if (dc.GetDepth() > 0)
	{
		POSITION pos = GetHeadPosition();
		while (pos != NULL)
		{
			dc << "\n";
			DumpElements<TYPE>(dc, &((CLockedList*)this)->GetNext(pos), 1);
		}
	}

	dc << "\n";
}

template<class TYPE, class ARG_TYPE>
void CLockedList<TYPE, ARG_TYPE>::AssertValid() const
{
	CSingleLock L((CSyncObject*)&m_Sect,TRUE);

  CObject::AssertValid();

	if (m_nCount == 0)
	{
		// empty list
		ASSERT(m_pNodeHead == NULL);
		ASSERT(m_pNodeTail == NULL);
	}
	else
	{
		// non-empty list
		ASSERT(AfxIsValidAddress(m_pNodeHead, sizeof(CNode)));
		ASSERT(AfxIsValidAddress(m_pNodeTail, sizeof(CNode)));
	}
}
#endif //_DEBUG


#endif
