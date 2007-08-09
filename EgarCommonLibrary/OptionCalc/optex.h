#ifndef _OPTEX_H__
#define _OPTEX_H__

#include "Models.h"

double CalculateOptionEx(	
						double	R,
						double	RF,
						double	S,
						double	K,
						double	V,
						int		Dte, 
                        bool	Call,
						bool	American,
						double* DivAmnt,
						double* DivYte,
						int		DivCount,
						long	Steps,
						GREEKS *pGreeks
						);

#endif //_OPTEX_H__

