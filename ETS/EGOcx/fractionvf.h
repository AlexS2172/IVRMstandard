#if !defined(AFX_FRACTIONVF_H__2BDD7F44_3202_43F9_A844_79E01A3C8EAE__INCLUDED_)
#define AFX_FRACTIONVF_H__2BDD7F44_3202_43F9_A844_79E01A3C8EAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CFractionVF wrapper class

class AFX_EXT_CLASS CFractionVF : public COleDispatchDriver
{
public:
	CFractionVF() {}		// Calls COleDispatchDriver default constructor
	CFractionVF(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFractionVF(const CFractionVF& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetDenominator();
	void SetDenominator(long);
	long GetDenominatorDigits();
	void SetDenominatorDigits(long);
	LPDISPATCH GetParent();

// Operations
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRACTIONVF_H__2BDD7F44_3202_43F9_A844_79E01A3C8EAE__INCLUDED_)
