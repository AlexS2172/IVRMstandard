#if !defined(AFX_POLAR_H__04C6B113_5EC2_41AE_B4CB_914F87A1BE44__INCLUDED_)
#define AFX_POLAR_H__04C6B113_5EC2_41AE_B4CB_914F87A1BE44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CPolar wrapper class

class AFX_EXT_CLASS CPolar : public COleDispatchDriver
{
public:
	CPolar() {}		// Calls COleDispatchDriver default constructor
	CPolar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPolar(const CPolar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetIsHalfRange();
	void SetIsHalfRange(BOOL);
	LPDISPATCH GetParent();
	BOOL GetAxisAllowNegative();
	void SetAxisAllowNegative(BOOL);

// Operations
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLAR_H__04C6B113_5EC2_41AE_B4CB_914F87A1BE44__INCLUDED_)
