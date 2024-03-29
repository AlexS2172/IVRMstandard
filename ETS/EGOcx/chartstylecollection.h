#if !defined(AFX_CHARTSTYLECOLLECTION_H__B54C5BAF_9E49_4917_89D5_575B130BEAE2__INCLUDED_)
#define AFX_CHARTSTYLECOLLECTION_H__B54C5BAF_9E49_4917_89D5_575B130BEAE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CChartStyle;

/////////////////////////////////////////////////////////////////////////////
// CChartStyleCollection wrapper class

class AFX_EXT_CLASS CChartStyleCollection : public COleDispatchDriver
{
public:
	CChartStyleCollection() {}		// Calls COleDispatchDriver default constructor
	CChartStyleCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChartStyleCollection(const CChartStyleCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetCount();
	LPDISPATCH GetParent();

// Operations
public:
	CChartStyle GetItem(const VARIANT& Index);
	CChartStyle Add(const VARIANT& Before);
	BOOL Remove(const VARIANT& Index);
	void RemoveAll();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTSTYLECOLLECTION_H__B54C5BAF_9E49_4917_89D5_575B130BEAE2__INCLUDED_)
