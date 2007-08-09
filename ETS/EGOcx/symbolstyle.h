#if !defined(AFX_SYMBOLSTYLE_H__6E72F230_7837_47E3_874D_E4FF9723EEA1__INCLUDED_)
#define AFX_SYMBOLSTYLE_H__6E72F230_7837_47E3_874D_E4FF9723EEA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CSymbolStyle wrapper class

class AFX_EXT_CLASS CSymbolStyle : public COleDispatchDriver
{
public:
	CSymbolStyle() {}		// Calls COleDispatchDriver default constructor
	CSymbolStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSymbolStyle(const CSymbolStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetShape();
	void SetShape(long);
	unsigned long GetColor();
	void SetColor(unsigned long);
	long GetSize();
	void SetSize(long);
	LPDISPATCH GetParent();
	BOOL GetIsDefault();
	void SetIsDefault(BOOL);

// Operations
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYMBOLSTYLE_H__6E72F230_7837_47E3_874D_E4FF9723EEA1__INCLUDED_)
