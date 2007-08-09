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
#include "OptionCalcMM2.h"

static double CalculateOptionMM(double	dDomesticRate,
								double	dForeignRate, 
								double	dSpotPrice,
								double	dStrike,
								double	dVolatility, 
								long	nDTE,
								bool	bIsCall,
								bool	bIsAmerican,
								long	nCount, 
								double*	pDivAmnts,
								double*	pDivYears,
								long	nSteps,
								double	dSkew,
								double	dKurtosis,
								long	nModel,
								GREEKS*	pGreeks = NULL)
{
	switch (nModel)
	{
	case MM_EGAR_BS			:
        return CO_BlackScholes(dDomesticRate, dForeignRate, dSpotPrice, dStrike,
			dVolatility, nDTE, bIsCall, bIsAmerican, pDivAmnts, pDivYears, nCount, pGreeks);
	case MM_EGAR_BINOMIAL	:	
        return CO_StandardBinomial(dDomesticRate, dForeignRate, dSpotPrice, dStrike,
			dVolatility, nDTE, bIsCall, bIsAmerican, pDivAmnts, pDivYears, nCount, nSteps, pGreeks);
	case MM_EGAR_OPTIMIZED	:	
        return CO_OptimizedBinomial(dDomesticRate, dForeignRate, dSpotPrice, dStrike,
			dVolatility, nDTE, bIsCall, bIsAmerican, pDivAmnts, pDivYears, nCount, pGreeks);
	case MM_EGAR_VSKLOG		:	
        return CO_VskLog(dDomesticRate, dForeignRate, dSpotPrice, dStrike,
			dVolatility, nDTE, bIsCall, bIsAmerican, pDivAmnts, pDivYears, nCount, dSkew, dKurtosis, pGreeks);

	default: return 0.;
	}
}

/***************************************************************************************************
	Calculates volatility. Returns -1 if error occured.
***************************************************************************************************/
double OPTIONCALC_API CalcVolatilityMM2(	double	dDomesticRate,	
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
											double	dSkew,
											double	dKurtosis,
											long	nModel)
{
    long nFlag = VF_OK;
    double dRet = CalcVolatilityMM3(dDomesticRate,
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
                                    dSkew,
                                    dKurtosis,
                                    nModel,
                                    &nFlag);

    return nFlag == VF_OK ? dRet : -1;
}

/***************************************************************************************************
	Calculates volatility. Returns -1 if error occured.
***************************************************************************************************/
double OPTIONCALC_API CalcVolatilityMM3(	double	dDomesticRate,	
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
											double	dSkew,
											double	dKurtosis,
											long	nModel,
                                            long*   pnFlag)
{
	// Check parameters
	if (nCount != 0)
	{
		if( ::IsBadReadPtr(pDivAmnts, sizeof(double) * nCount) || 
			::IsBadReadPtr(pDivYears, sizeof(double) * nCount))
		{
			::SetLastError(ERROR_NOACCESS);
			return -1;
		}
	}

	if (!pnFlag)
	{
		::SetLastError(ERROR_INVALID_PARAMETER);
		return -1;
	}

	double EPS = 3.0e-8;
	int ITMAX = 30;

	double tol = 1.0e-6;
	double tolF = 1.0e-4;
	double x1  = 0.01;
	double x2  = 2.5;

	double dOptValMin = 0.0;
	double dOptValMax = 0.0;

	int iter;
	double a=x1,b=x2,c=x2,d,e,min1,min2;
	double fa=(dOptValMin = CalculateOptionMM(dDomesticRate, dForeignRate, dSpotPrice, dStrike, 
		x1 , nDTE, (nIsCall != 0L), (nIsAmerican != 0L), nCount, pDivAmnts, pDivYears,
		max(nSteps, 5), dSkew, dKurtosis, nModel))-dOptionPrice;

	double fb=(dOptValMax = CalculateOptionMM(dDomesticRate, dForeignRate, dSpotPrice, dStrike, 
		x2 , nDTE, (nIsCall != 0L), (nIsAmerican != 0L), nCount, pDivAmnts, pDivYears,
		max(nSteps, 5), dSkew, dKurtosis, nModel))-dOptionPrice;

	if (dOptionPrice > dOptValMax)
	{
		*pnFlag = VF_TOOHIGH;
		return x2;
	}
	else if (dOptionPrice < (dOptValMin + .005))
	{
		*pnFlag = VF_TOOLOW;
		dOptionPrice = dOptValMin + .005;
		fa = dOptValMin - dOptionPrice;

	}
	else
	{
		*pnFlag = VF_OK;
	}

	double fc,p,q,r,s,tol1,xm;

	if ((fa > 0.0 && fb > 0.0) || (fa < 0.0 && fb < 0.0)) {
		//Root must be bracketed in zbrent
		//::SetLastError( ERROR_INVALID_PARAMETER );
		*pnFlag = VF_UNRELIABLE;
		return -1;
	}

	fc=fb;
	for (iter=1;iter<=ITMAX;iter++) {

		if ((fb > 0.0 && fc > 0.0) || (fb < 0.0 && fc < 0.0)) {
			c=a;  //Rename a, b, c and adjust bounding interval. 
			fc=fa;
			e=d=b-a;
		}

		if (fabs(fc) < fabs(fb)) {
			a=b;
			b=c;
			c=a;
			fa=fb;
			fb=fc;
			fc=fa;
		}

		tol1=2.0*EPS*fabs(b)+0.5*tol; //Convergence check.
		xm=0.5*(c-b);


		//if (abs(fb)<= 0.005*dOptionPrice) {
		if (fabs(fb) <= tolF || fabs(xm) <= tol1) {
			//*pnFlag = VF_OK;
			return b;
		}

		if (fabs(e) >= tol1 && fabs(fa) > fabs(fb)) {

			s=fb/fa; //Attempt inverse quadratic interpolation.

			if (a == c) {
				p=2.0*xm*s;
				q=1.0-s;
			} else {
				q=fa/fc;
				r=fb/fc;
				p=s*(2.0*xm*q*(q-r)-(b-a)*(r-1.0));
				q=(q-1.0)*(r-1.0)*(s-1.0);
			}

			if (p > 0.0) q = -q; //Check whether in bounds.

			p=fabs(p);
			min1=3.0*xm*q-fabs(tol1*q);
			min2=fabs(e*q);

			if (2.0*p < (min1 < min2 ? min1 : min2)) {
				e=d; //Accept interpolation.
				d=p/q;
			} else {
				d=xm; //Interpolation failed, use bisection.
				e=d;
			}
		} else { //Bounds decreasing too slowly, use bisection.
			d=xm;
			e=d;
		}

		a=b; //Move last best guess to a.
		fa=fb;

		if (fabs(d) > tol1) //Evaluate new trial root.
			b +=d;
		else
			b += xm>=0?tol1:-tol1;

		fb=CalculateOptionMM(dDomesticRate, dForeignRate, dSpotPrice, dStrike, 
			b , nDTE, (nIsCall != 0L), (nIsAmerican != 0L), nCount, pDivAmnts, pDivYears,
			max(nSteps, 5), dSkew, dKurtosis, nModel)-dOptionPrice;
	}
	//Maximum number of iterations exceeded in brent
	//::SetLastError( ERROR_INVALID_DATA );
	*pnFlag = VF_UNRELIABLE;
	return -1; //Never get here.
}

// Calculates greeks. Returns 0 if failed, or value greater than zero otherwise.
long OPTIONCALC_API CalcGreeksMM2(	double	dDomesticRate,
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
									double	dSkew,
									double	dKurtosis,
									long	nModel,
									GREEKS*	pGreeks) /*out*/
{
	if (dVolatility < 0. || dStrike <= 0.)
		return 0;				// Check valid volatility & strike

	// Check parameters
	if (nCount > 0)
	{
		if( ::IsBadReadPtr(pDivAmnts, sizeof(double) * nCount) || 
			::IsBadReadPtr(pDivYears, sizeof(double) * nCount))
		{
			::SetLastError(ERROR_NOACCESS);
			return 0;
		}
	}

	if(::IsBadWritePtr(pGreeks, sizeof(GREEKS)))
	{
		::SetLastError(ERROR_NOACCESS);
		return 0;
	}

	if( pGreeks->nMask == GT_NOTHING )
		return 1;	// Nothing to calculate

	long gt = pGreeks->nMask;

	if (dVolatility <= 0.0005){
		memset(pGreeks, 0, sizeof(GREEKS));
		pGreeks->nMask = gt;
		return 1;
	}



	gt |= (gt & GT_GAMMA_VEGA)	? GT_DELTA_VEGA | GT_GAMMA	        : GT_NOTHING;
	gt |= (gt & GT_GAMMA_THETA) ? GT_DELTA_THETA | GT_GAMMA	        : GT_NOTHING;
	gt |= (gt & GT_DELTA_VEGA)	? GT_DELTA | GT_VEGA | GT_GAMMA     : GT_NOTHING;
	gt |= (gt & GT_DELTA_THETA) ? GT_DELTA | GT_THETA | GT_GAMMA    : GT_NOTHING;
	gt |= (gt & GT_GAMMA)		? GT_DELTA					        : GT_NOTHING;
	gt |= (gt & GT_ALPHA)		? GT_GAMMA | GT_THETA		        : GT_NOTHING;

	pGreeks->nMask = gt;

	pGreeks->dTheoPrice = CalculateOptionMM(dDomesticRate, dForeignRate, dSpotPrice, dStrike, 
		dVolatility, nDTE, (nIsCall != 0L), (nIsAmerican != 0L), nCount, pDivAmnts, pDivYears,
		min(max(nSteps, OPM::cnTreeStepsMin), OPM::cnTreeStepsMax), dSkew, dKurtosis, nModel, pGreeks);

	if(OPM::IsBadValue(pGreeks->dTheoPrice))
	{
		pGreeks->dTheoPrice = 0.;
		return 0L;
	}

	return 1;
}

