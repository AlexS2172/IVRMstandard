/***************************************************************************************************
*	
*	(C) EGAR technology inc. 2002
*	
*	Special functions which calulates greeks and implied volatility 
*	calculation model.
*	
*	
*	Author: Eugene Karnygin (EVK)
*
***************************************************************************************************/

#include "stdafx.h"

#include "Models.h"
#include "OptionCalcMM.h"
#include "OptionCalcMM2.h"

/***************************************************************************************************
	Calculates volatility. Returns -1 if error occured.
***************************************************************************************************/
double OPTIONCALC_API CalcVolatilityMM(	double	dDomesticRate,	
										double	dForeignRate, 
										double	dSpotPrice,
										double	dOptionPrice,
										double	dStrike,
										long	nDTE,
										long	nIsCall,
										long	nIsAmerican,
										long	nCount, 
										double*	pDivAmnts,
										double*	pDivYears,
										long	nSteps,
										long	nModel)
{
	if (nModel == MM_EGAR_VSKLOG)
	{
		::SetLastError(ERROR_INVALID_PARAMETER);
		return -1;
	}

	return CalcVolatilityMM2(	dDomesticRate,	
								dForeignRate, 
								dSpotPrice,
								dOptionPrice,
								dStrike,
								nDTE,
								nIsCall,
								nIsAmerican,
								nCount, 
								pDivAmnts,
								pDivYears,
								nSteps,
								0,		// Skew
								0,		// Kurtosis
								nModel);
}

// Calculates greeks. Returns 0 if failed, or value greater than zero otherwise.
long OPTIONCALC_API CalcGreeksMM(	double	dDomesticRate,
									double	dForeignRate, 
									double	dSpotPrice,
									double	dStrike,
									double	dVolatility, 
									long	nDTE,
									long	nIsCall,
									long	nIsAmerican,
									long	nCount, 
									double*	pDivAmnts,
									double*	pDivYears,
									long	nSteps,
									long	nModel,
									GREEKS*	pGreeks) /*out*/
{
	if (nModel == MM_EGAR_VSKLOG)
	{
		::SetLastError(ERROR_INVALID_PARAMETER);
		return -1;
	}

	
	return CalcGreeksMM2(	dDomesticRate,
							dForeignRate, 
							dSpotPrice,
							dStrike,
							dVolatility, 
							nDTE,
							nIsCall,
							nIsAmerican,
							nCount, 
							pDivAmnts,
							pDivYears,
							nSteps,
							0,		// Skew
							0,		// Kurtosis
							nModel,
							pGreeks);
}