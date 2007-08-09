//=============================================================================
// Copyright 2002
//
// Author	: Eugene Karnygin
// File		: Rates.cpp
// Created	: 31 july 2002
// 
// 
//=============================================================================
#include "Common.h"

namespace OPM
{

double RateDiscToCont(double dDiscRate, unsigned int nDays) 
{
	double dYears360 = nDays / cdDaysPerYear360;
	double dYears365 = nDays / cdDaysPerYear365;
	
	double dDF;

	if (dYears360 <= 1.)
	{
		dDF = 1. + dDiscRate * dYears360;		
	}
	else
	{
		dDF = pow(1. + dDiscRate, dYears360);		
	}
	
	return log(dDF) / dYears365;
}

};