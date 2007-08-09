#include "stdafx.h"

#include "PequoteConnector.h"
#include "Publisher.h"

DWORD __stdcall CPequoteConnector::Start(void* pParam)
{
	CTracer::TraceMessage(CTracer::enMtInformation,NULL, _T("Starting publisher..."));

	DWORD dwErr = m_Publisher.Start(pParam);
	if(dwErr)
		return TraceError(dwErr);

	CTracer::TraceMessage(CTracer::enMtInformation,NULL, _T("Publisher started."));
	return CFileConnector::Start(pParam);
};

DWORD __stdcall CPequoteConnector::Stop()
{
	DWORD dwErr = CFileConnector::Stop();
	if(dwErr)
		TraceError();

	Sleep(500);	
	CTracer::TraceMessage(CTracer::enMtInformation,NULL, _T("Stopping publisher..."));
	m_Publisher.Stop();
	CTracer::TraceMessage(CTracer::enMtInformation,NULL, _T("Publisher stopped."));

	return 0;
}
