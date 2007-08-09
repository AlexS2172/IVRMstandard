//=============================================================================
// Copyright 2002, Eugene Karnygin
//
// Author	: Eugene Karnygin
// File		: BlackAndScholes.cpp
// Created	: 25 june 2002
// 
// The Black and Scholes model of theoretical option price
//=============================================================================

//=============================================================================
// Standart headers including
//=============================================================================
#include "Common.h"

namespace OPM
{

double BlackAndScholes(	double	dRateDomestic,
						double	dRateForeign,
						double	dSpotPrice,
						double	dStrike,
						int		nDte,
						double	dVolatility,
						bool	bIsCall,
						double* pdDivAmnt,						   
						double* pdDivYte,						    
						int		nDivCount,
						GREEKS*	pGreeks/*out*/)
{
	if (nDte < 1) 
		return max(bIsCall ? dSpotPrice - dStrike : dStrike - dSpotPrice, 0.);

	double dContRd = RateDiscToCont(dRateDomestic , nDte);
	double dContRf = RateDiscToCont(dRateForeign, nDte);
	double dYte	= nDte / cdDaysPerYear365;
	
	double dDiscountedSpot = DiscountForDividends(dSpotPrice,
												dContRd,
												pdDivAmnt,
												pdDivYte,
												nDivCount,
												dYte);
	if(IsBadValue(dDiscountedSpot))
		return BadDoubleValue;

	const double A = dDiscountedSpot * (1. / exp( dContRf * dYte));
	const double B = dStrike * (1. / exp( dContRd * dYte));

	const double D = dVolatility * sqrt(dYte);

	const double d1	= log(dDiscountedSpot/dStrike) / D + D * (((dContRd - dContRf) / (dVolatility * dVolatility)) + .5);
	const double d2	= d1 - D;

	const double N1	= NormalC(d1);
	const double N2	= NormalC(d2);

	long cCalculatedGreeksMask = GT_NOTHING;

	double dTheoPrice = bIsCall ? A * N1 - B * N2 : A * ( N1 - 1.) - B * ( N2 - 1.);
	
	if(!IsValidTheoPrice(dTheoPrice))
	{
		dTheoPrice = BadDoubleValue;
	}
	else
	{
		cCalculatedGreeksMask |= GT_THEOPRICE;
	}

	if(pGreeks && pGreeks->nMask & ~GT_THEOPRICE && !IsBadValue(dTheoPrice))
	{
        const double	dd1dS = 1. / (D * dDiscountedSpot);
        const double	dd1dT = -d2 / (2. * dYte) + (dContRd - dContRf) / D;
        const double	dd2dT = -d1 / (2. * dYte) + (dContRd - dContRf) / D;
        const double	dd1dVol = - d2 / dVolatility;
        const double	dd2dVol = - d1 / dVolatility;
        const double	dd12dR = dYte / D;
        const double    n1 = NormalDensity(d1);
        const double    n2 = NormalDensity(d2);
		

    	// DELTA
	    if (pGreeks->nMask & GT_DELTA)
	    {
            pGreeks->dDelta = exp(-dContRf * dYte) * (N1 - (bIsCall ? 0. : 1.));
		    cCalculatedGreeksMask |= GT_DELTA;
	    }

    	// GAMMA
	    if (pGreeks->nMask & GT_GAMMA)
	    {
		    pGreeks->dGamma = exp(-dContRf * dYte) * dd1dS * n1;
		    cCalculatedGreeksMask |= GT_GAMMA;
	    }

	    // THETA
	    if (pGreeks->nMask & GT_THETA)
	    {
		    pGreeks->dTheta = ( A * (dContRf * (N1 - (bIsCall ? 0. : 1.)) - dd1dT * n1) -
                B * (dContRd * (N2 - (bIsCall ? 0. : 1.)) - dd2dT * n2) ) * cdDeltaTime;            
		    cCalculatedGreeksMask |= GT_THETA;
	    }

	    // DELTA THETA
	    if (pGreeks->nMask & GT_DELTA_THETA)
	    {
		    pGreeks->dDeltaTheta = ( dContRf * (pGreeks->dDelta - (bIsCall ? 0. : exp(-dContRf * dYte) )) - 
				pGreeks->dGamma * dd1dT / dd1dS ) * cdDeltaTime;
		    cCalculatedGreeksMask |= GT_DELTA_THETA;
	    }

	    // GAMMA THETA
	    if (pGreeks->nMask & GT_GAMMA_THETA)
	    {
		    pGreeks->dGammaTheta = ( pGreeks->dGamma * (dContRf + 1. / (2. * dYte) + d1 * dd1dT) ) * cdDeltaTime;
		    cCalculatedGreeksMask |= GT_GAMMA_THETA;
	    }

        // DELTA VEGA
        if (pGreeks->nMask & GT_DELTA_VEGA)
        {
	        pGreeks->dDeltaVega = ( pGreeks->dGamma * dd1dVol / dd1dS ) * cdDeltaVolatility;
	        cCalculatedGreeksMask |= GT_DELTA_VEGA;
        }

        // GAMMA VEGA
        if (pGreeks->nMask & GT_GAMMA_VEGA)
        {
	        pGreeks->dGammaVega = ( -pGreeks->dGamma * ( 1. / dVolatility + d1 * dd1dVol) ) * cdDeltaVolatility;
	        cCalculatedGreeksMask |= GT_GAMMA_VEGA;
        }

        // VEGA
        if (pGreeks->nMask & GT_VEGA)
        {
	        pGreeks->dVega = ( A * dd1dVol * n1 - B * dd2dVol * n2 ) * cdDeltaVolatility;
	        cCalculatedGreeksMask |= GT_VEGA;
        }

        // RHO
        if (pGreeks->nMask & GT_RHO)
   	    {
	        pGreeks->dRho = ( (A * n1 - B * n2) * dd12dR + dYte * B * (N2 - (bIsCall ? 0. : 1.)) ) * cdDeltaRate;
	        cCalculatedGreeksMask |= GT_RHO;
        }

		// Check values
		if (cCalculatedGreeksMask & GT_DELTA)
			pGreeks->dDelta = min(max(pGreeks->dDelta, -1.), 1.);
				
		if (cCalculatedGreeksMask & GT_GAMMA)
			pGreeks->dGamma = max(pGreeks->dGamma, 0.);

		if (cCalculatedGreeksMask & GT_VEGA)
			pGreeks->dVega = max(pGreeks->dVega, 0.);

		if (cCalculatedGreeksMask & GT_THETA)
			pGreeks->dTheta = min(pGreeks->dTheta, 0.);

		// ALPHA
		if ((pGreeks->nMask & GT_ALPHA) && (ValueNEQZero(pGreeks->dTheta)))
		{
			pGreeks->dAlpha = pGreeks->dGamma / pGreeks->dTheta;
			cCalculatedGreeksMask |= GT_ALPHA;
		}
	}
	// Set up greeks mask
	if(pGreeks)
		pGreeks->nMask = cCalculatedGreeksMask;

	return  dTheoPrice;
}

}
