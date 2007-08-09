#include "StdAfx.h"
#include "EodLoadMktStrUpdates.h"

namespace EOD
{

void CEodLoadMarketStructureUpdates::CheckMktStrUpdates(bool bOnlyActive)
{
	Report(StepMask(),enRpMtMessage,_T("Check updates of underlyings market structure on IVolatility"));
	m_bOnlyActive = bOnlyActive;

	EODSM::CSmSettingsMgrPtr spSettingsMgr = CEodServer::s_pEodServer->SettingsMgr();

	EOD::CEodMktStructureMgrPtr spMktStrMgr = CEodServer::s_pEodServer->MktStructureMgr();

	EODMS::CMsUndCollPtr spAllUndColl = spMktStrMgr->UndColl();

	DATE dtUpdate = 0.;
	EODMS::CMsUndCollPtr spRequestUndColl = _PrepareDataForRequest(spAllUndColl,dtUpdate);

	if(spRequestUndColl->size())
	{
		COleDateTime odtUpdate(dtUpdate);

		Report(StepMask(),enRpMtMessage, _T("Request changes of underlyings market structures from '%s'"), odtUpdate.Format(VAR_DATEVALUEONLY));
		m_Request.Init(spSettingsMgr, spRequestUndColl, dtUpdate);

		RequestIvData(&m_Request);
	}

	Report(StepMask(),enRpMtMessage, _T("Finished checking of market structure updates. %d underlying will be updated"), _GetUndCountNeedUpdate(spAllUndColl));
}

EODMS::CMsUndCollPtr CEodLoadMarketStructureUpdates::_PrepareDataForRequest(EODMS::CMsUndCollPtr pUndColl, DATE& dtUpdate)
{
	EODMS::CMsUndCollPtr spUndColl(new EODMS::CMsUndColl);
	for(EODMS::CMsUndColl::iterator iterUnd = pUndColl->begin(); iterUnd != pUndColl->end(); iterUnd++)
	{
		EODMS::CMsUndPtr spUnd(iterUnd->second);
		if( (!m_bOnlyActive || spUnd->m_bIsActive) && spUnd->m_dtLastMsUpdate > 0.)
		{
			if(EODCO::DoubleEQZero(dtUpdate) || dtUpdate > spUnd->m_dtLastMsUpdate)
				dtUpdate = spUnd->m_dtLastMsUpdate;

			spUndColl->insert(EODMS::CMsUndColl::value_type(spUnd->m_sSymbol, spUnd));

			spUnd->m_bNeedMsUpdate = false;
		}
	}
	return spUndColl;
}

long CEodLoadMarketStructureUpdates::_GetUndCountNeedUpdate(EODMS::CMsUndCollPtr pUndColl)
{
	long nCount = 0L;
	for(EODMS::CMsUndColl::iterator iterUnd = pUndColl->begin(); iterUnd != pUndColl->end(); iterUnd++)
	{
		EODMS::CMsUndPtr spUnd(iterUnd->second);
		if((!m_bOnlyActive || spUnd->m_bIsActive) && spUnd->m_bNeedMsUpdate)
			nCount++;
	}
	return nCount;
}

void CEodLoadMarketStructureUpdates::OnIvData(EODIV::CIvMarketStructureUpdatesResultPtr pResult)
{	
	if(_IsCancel() || IsStopping())
		throw EODCO::CEodStopException();
	
	Trace(EODCO::enTrLogDebug,__FUNCTION__,_T("Start"));

	EODMS::CMsUndCollPtr spUndColl = m_Request.Und();
	
	ATLASSERT(spUndColl);

	EODMS::CMsUndPtr spUnd(GetCollectionItem<EODMS::CMsUndPtr>(spUndColl, pResult->m_strUndSymbol));

	ATLASSERT(spUnd);
	
	if(spUnd)
	{

		spUnd->m_dtIvMsUpdate = pResult->m_dtLastUpdate;
	
		if(EODCO::DoubleEQZero(pResult->m_dtLastUpdate) || pResult->m_dtLastUpdate < 0. || spUnd->m_dtLastMsUpdate < spUnd->m_dtIvMsUpdate)
		{
			spUnd->m_bNeedMsUpdate = true;
		}

		_IncrementCheckMsProgress();
	}

	Trace(EODCO::enTrLogDebug,__FUNCTION__,_T("Completed"));
}
void CEodLoadMarketStructureUpdates::_IncrementCheckMsProgress()
{
	EODMS::CMsUndCollPtr spUndColl = m_Request.Und();

	ATLASSERT(spUndColl);

	size_t nAllUnd = spUndColl->size(); 
	size_t nProgress = 10 * m_Request.UndSend() / nAllUnd;

	if(m_nProgress != nProgress)
	{
		m_nProgress = nProgress;
		Report(StepMask(),enRpMtProgress, _T("%d"), m_nProgress);
		CEodServer::s_pEodServer->StepsMgr()->IncProgress();
	}
}
}