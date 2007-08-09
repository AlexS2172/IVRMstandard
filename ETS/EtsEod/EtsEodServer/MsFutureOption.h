#ifndef __MSFUTUREOPTION_H__
#define __MSFUTUREOPTION_H__

#include "MsContract.h"

namespace EODMS
{

	/////////////////////////////////////////////////////////////////////////////
	//
	class  CMsFutureOption : public CMsContract
	{
	public:
		CMsFutureOption(void) : m_bIsCall(true), m_dStrike(0.), m_dtExpiration(BAD_DOUBLE_VALUE), 
			m_dPriceTheo(BAD_DOUBLE_VALUE), m_dRate(BAD_DOUBLE_VALUE), m_bUsed(false)
		{
		}

		~CMsFutureOption(void)
		{
		}

		SYMBOL_TYPE Type() const
		{
			return enStFutureOption;
		}

	public:
		bool			m_bIsCall;
		double			m_dStrike;
		DATE			m_dtExpiration;
		double			m_dRate;
		double			m_dPriceTheo;
		bool			m_bUsed;
	};

	typedef boost::shared_ptr<CMsFutureOption> CMsFutureOptionPtr;
	typedef std::map<CString, CMsFutureOptionPtr>	CMsFutureOptionColl;
	typedef std::pair<CString, CMsFutureOptionPtr>	CMsFutureOptionPair;
	typedef boost::shared_ptr<CMsFutureOptionColl>	CMsFutureOptionCollPtr;

};

#endif //__MSFUTUREOPTION_H__