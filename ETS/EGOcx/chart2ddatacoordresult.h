#if !defined(AFX_CHART2DDATACOORDRESULT_H__683276DE_8956_4D63_9B77_8A6FD323F16D__INCLUDED_)
#define AFX_CHART2DDATACOORDRESULT_H__683276DE_8956_4D63_9B77_8A6FD323F16D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CChart2DDataCoordResult wrapper class

class AFX_EXT_CLASS CChart2DDataCoordResult : public COleDispatchDriver
{
public:
	CChart2DDataCoordResult() {}		// Calls COleDispatchDriver default constructor
	CChart2DDataCoordResult(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChart2DDataCoordResult(const CChart2DDataCoordResult& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetRegion();
	void SetRegion(long);
	double GetX();
	void SetX(double);
	double GetY();
	void SetY(double);

// Operations
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHART2DDATACOORDRESULT_H__683276DE_8956_4D63_9B77_8A6FD323F16D__INCLUDED_)
