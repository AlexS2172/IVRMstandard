#if !defined(AFX_PERCENTAGEVF_H__A4C225E1_5111_4BD1_9A46_AF317FBF2CFA__INCLUDED_)
#define AFX_PERCENTAGEVF_H__A4C225E1_5111_4BD1_9A46_AF317FBF2CFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CDerivedEnum;
class CDerivedBoolean;

/////////////////////////////////////////////////////////////////////////////
// CPercentageVF wrapper class

class AFX_EXT_CLASS CPercentageVF : public COleDispatchDriver
{
public:
	CPercentageVF() {}		// Calls COleDispatchDriver default constructor
	CPercentageVF(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPercentageVF(const CPercentageVF& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetDecimalPlaces();
	void SetDecimalPlaces(long);
	CDerivedEnum GetOrderPercentSignValue();
	void SetOrderPercentSignValue(LPDISPATCH);
	CDerivedBoolean GetSpaceSeparatingSign();
	void SetSpaceSeparatingSign(LPDISPATCH);
	CDerivedBoolean GetSpaceSeparatingPercent();
	void SetSpaceSeparatingPercent(LPDISPATCH);
	LPDISPATCH GetParent();

// Operations
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERCENTAGEVF_H__A4C225E1_5111_4BD1_9A46_AF317FBF2CFA__INCLUDED_)
