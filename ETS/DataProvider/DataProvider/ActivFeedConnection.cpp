#include "StdAfx.h"
#include "ActivFeedConnection.h"
//----------------------------------------------------------------------//
CActivFeedConnection::pointer CProviderSingleton::m_providerPtr = NULL;
CSettings::pointer CProviderSingleton::m_settingsPtr = NULL;
//----------------------------------------------------------------------//
bool	
CActivFeedConnection::Connect()
{
	if (m_Gateway.IsConnected()) return true;

	GetProcess()->SetState( IProcess::STATE_RUNNING );
	StartThread();
	return m_Gateway.Activate();
};
//----------------------------------------------------------------------//
bool	
CActivFeedConnection::Disconnect()
{
	return m_Gateway.Deactivate();
}
//----------------------------------------------------------------------//
bool	
CActivFeedConnection::Request(QuoteRequestPtr spRequest, QuoteAtomPtr& spQuote)
{
	return (STATUS_CODE_SUCCESS == m_Gateway.Request(spRequest, spQuote));
}
//----------------------------------------------------------------------//
bool	
CActivFeedConnection::Subscribe(QuoteRequestPtr spRequest)
{
	return (STATUS_CODE_SUCCESS == m_Gateway.Subscribe(spRequest));
}
//----------------------------------------------------------------------//
bool
CActivFeedConnection::GetUpdates(CQuoteVector &quotes)
{
	return m_Gateway.GetUpdates(quotes);
}
//----------------------------------------------------------------------//
bool
CActivFeedConnection::RequestMultiple(CRequestVector& request, CQuoteVector& response)
{
	return (STATUS_CODE_SUCCESS == m_Gateway.RequestMultiple(request, response));	
}
//----------------------------------------------------------------------//
bool	
CActivFeedConnection::SubscribeMultiple(CRequestVector& request)
{
	return (STATUS_CODE_SUCCESS == m_Gateway.SubscribeMultiple(request));	
}
//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
