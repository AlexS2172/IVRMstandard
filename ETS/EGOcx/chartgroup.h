#if !defined(AFX_CHARTGROUP_H__0791CC04_A494_43FB_BF7C_04867D13993E__INCLUDED_)
#define AFX_CHARTGROUP_H__0791CC04_A494_43FB_BF7C_04867D13993E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CChart2DData;
class CChartStyleCollection;
class CLabelCollection;
class CStringCollection;
class CPointStyleCollection;
class CChart2DDataCoordResult;
class CChart2DCoordResult;
class CChart2DDataIndexResult;

/////////////////////////////////////////////////////////////////////////////
// CChartGroup wrapper class

class AFX_EXT_CLASS CChartGroup : public COleDispatchDriver
{
public:
	CChartGroup() {}		// Calls COleDispatchDriver default constructor
	CChartGroup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChartGroup(const CChartGroup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetName();
	long GetChartType();
	void SetChartType(long);
	short GetDrawingOrder();
	void SetDrawingOrder(short);
	CChart2DData GetData();
	void SetData(LPDISPATCH);
	CChartStyleCollection GetStyles();
	CLabelCollection GetSeriesLabels();
	CLabelCollection GetPointLabels();
	LPDISPATCH GetParent();
	CStringCollection GetSeriesFields();
	void SetSeriesFields(LPDISPATCH);
	CString GetPointLabelsField();
	void SetPointLabelsField(LPCTSTR);
	CString GetPointValuesField();
	void SetPointValuesField(LPCTSTR);
	BOOL GetAreSeriesLabelsBound();
	void SetAreSeriesLabelsBound(BOOL);
	BOOL GetIsStacked();
	void SetIsStacked(BOOL);
	CPointStyleCollection GetPointStyles();
	CChartStyleCollection GetLegendStyles();

// Operations
public:
	long CoordToDataCoord(long XPixel, long YPixel, double* X, double* Y);
	void DataCoordToCoord(double X, double Y, long* XPixel, long* YPixel);
	long CoordToDataIndex(long XPixel, long YPixel, long Focus, long* Series, long* Point, long* Distance);
	void DataIndexToCoord(long Series, long Point, long* XPixel, long* YPixel);
	CChart2DDataCoordResult CoordToDataCoordObject(long XPixel, long YPixel);
	CChart2DCoordResult DataCoordToCoordObject(double X, double Y);
	CChart2DDataIndexResult CoordToDataIndexObject(long XPixel, long YPixel, short Focus);
	CChart2DCoordResult DataIndexToCoordObject(long Series, long Point);
	void LoadAdoRecordset(LPDISPATCH Recordset, BOOL UseSeriesFields);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTGROUP_H__0791CC04_A494_43FB_BF7C_04867D13993E__INCLUDED_)
