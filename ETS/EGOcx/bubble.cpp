// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "bubble.h"


/////////////////////////////////////////////////////////////////////////////
// CBubble properties

long CBubble::GetEncodingMethod()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void CBubble::SetEncodingMethod(long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

double CBubble::GetMinimumSize()
{
	double result;
	GetProperty(0x2, VT_R8, (void*)&result);
	return result;
}

void CBubble::SetMinimumSize(double propVal)
{
	SetProperty(0x2, VT_R8, propVal);
}

double CBubble::GetMaximumSize()
{
	double result;
	GetProperty(0x3, VT_R8, (void*)&result);
	return result;
}

void CBubble::SetMaximumSize(double propVal)
{
	SetProperty(0x3, VT_R8, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CBubble operations
