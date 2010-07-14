#pragma once
#include "stdafx.h"

//class CIVRMFilter:	public POA_DDS::CustomFilter,
//					public PortableServer::RefCountServantBase
//{
//private:
//	IEtsMainPtr m_dsPtr;
//
//public:
//	CIVRMFilter();
//	virtual ~CIVRMFilter(void){}
//	void SetDataSource(IEtsMainPtr ptr);
//
//	void ProcessOptionQuote(const VS::CResponseBlock* responseBlock);
//	void ProcessEquityQuote(const VS::CResponseBlock* responseBlock);
//	void ProcessFutureQuote(const VS::CResponseBlock* responseBlock);
//	void ProcessFutureOptionQuote(const VS::CResponseBlock* responseBlock);
//	CORBA::Any* ApplyFilter(const CORBA::Any& anyData);
//
//	CLock m_filterLock;
//};