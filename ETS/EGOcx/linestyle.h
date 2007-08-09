#if !defined(AFX_LINESTYLE_H__5D3B1E2A_B960_40A9_9B9E_C5EC473F5089__INCLUDED_)
#define AFX_LINESTYLE_H__5D3B1E2A_B960_40A9_9B9E_C5EC473F5089__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CLineStyle wrapper class

class AFX_EXT_CLASS CLineStyle : public COleDispatchDriver
{
public:
	CLineStyle() {}		// Calls COleDispatchDriver default constructor
	CLineStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CLineStyle(const CLineStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetPattern();
	void SetPattern(long);
	unsigned long GetColor();
	void SetColor(unsigned long);
	long GetWidth();
	void SetWidth(long);
	LPDISPATCH GetParent();
	BOOL GetIsDefault();
	void SetIsDefault(BOOL);

// Operations
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINESTYLE_H__5D3B1E2A_B960_40A9_9B9E_C5EC473F5089__INCLUDED_)
