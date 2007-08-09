#pragma once
#ifndef __EODLOADMKTSTRUPDATES_H__
#define __EODLOADMKTSTRUPDATES_H__
#include "EodStepProcessorBase.h"

namespace EOD
{

class CEodLoadMarketStructureUpdates : 
	virtual public CEodStepProcessorBase,
	public EODIV::CIvDataLoader<EODIV::CIvMarketStructureUpdatesRequest,EODIV::CIvMarketStructureUpdatesResultPtr>
{
public:
	CEodLoadMarketStructureUpdates(void) : m_bOnlyActive(false) {};
	virtual ~CEodLoadMarketStructureUpdates(void) {};

	virtual void	CheckMktStrUpdates(bool bOnlyActive);
	virtual void	OnIvData(EODIV::CIvMarketStructureUpdatesResultPtr pResult);

protected:
	virtual const HANDLE _StopEventHandle() { return GetStopEventHandle(); }
	virtual EodStepsMaskEnum _StepMask() { return StepMask(); }
private:
	EODMS::CMsUndCollPtr _PrepareDataForRequest(EODMS::CMsUndCollPtr pUndColl, DATE& dtUpdate);
	long _GetUndCountNeedUpdate(EODMS::CMsUndCollPtr pUndColl);
	void _IncrementCheckMsProgress() throw();
private:
	EODIV::CIvMarketStructureUpdatesRequest m_Request;
	bool	m_bOnlyActive;
};

};

#endif// __EODLOADMKTSTRUPDATES_H__
