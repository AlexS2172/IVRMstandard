#include "stdafx.h"
//#include "IVRMFilter.h"
//#include "Server.h"
//
////-------------------------------------------------------------------------------------------//
//CIVRMFilter::CIVRMFilter()
//{
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_OPTION_SYMBOL,				VS::CStreamFactory::STREAM_64BYTE_STRING_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_STOCK_SYMBOL,				VS::CStreamFactory::STREAM_STRING_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_TERM,						VS::CStreamFactory::STREAM_SHORT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_OTM,							VS::CStreamFactory::STREAM_INT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_OPTION_TYPE,					VS::CStreamFactory::STREAM_CHAR_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_BID,							VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_BID_DATE,					VS::CStreamFactory::STREAM_DATETIME_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_BID_EXCHANGE,				VS::CStreamFactory::STREAM_EXCHANGE_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_BID_SIZE,					VS::CStreamFactory::STREAM_INT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_ASK,							VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_ASK_DATE,					VS::CStreamFactory::STREAM_DATETIME_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_ASK_EXCHANGE,				VS::CStreamFactory::STREAM_EXCHANGE_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_ASK_SIZE,					VS::CStreamFactory::STREAM_INT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_LAST,						VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_LAST_DATE,					VS::CStreamFactory::STREAM_DATETIME_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_LAST_EXCHANGE,				VS::CStreamFactory::STREAM_EXCHANGE_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_LAST_SIZE,					VS::CStreamFactory::STREAM_INT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_VOLUME,						VS::CStreamFactory::STREAM_INT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_STOCK_TYPE,					VS::CStreamFactory::STREAM_CHAR_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_STOCK_DIV_DATE,				VS::CStreamFactory::STREAM_DATE_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_STOCK_DIV_FREQ,				VS::CStreamFactory::STREAM_SHORT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_STOCK_DIV_AMT_YIELD,			VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_CURRENCY,					VS::CStreamFactory::STREAM_CURRENCY_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_STOCK_REGION,				VS::CStreamFactory::STREAM_INT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_IV,							VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_DELTA,						VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_VEGA,						VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_GAMMA,						VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_THETA,						VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_RHO,							VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_VIRTUAL_STRIKE,				VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_PREIV,						VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_MONEYNESS,					VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_IVXCALL,						VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_IVXPUT,						VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_OPTION_STYLE,				VS::CStreamFactory::STREAM_CHAR_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_EXPIRATION,					VS::CStreamFactory::STREAM_DATE_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_INTEREST_RATE,				VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_IR_PERIOD,					VS::CStreamFactory::STREAM_INT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_IVXMEAN,						VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_STRIKE,						VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_SETTLEMENT_DATE,				VS::CStreamFactory::STREAM_DATETIME_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_FUTURE_ROOT_SYMBOL,			VS::CStreamFactory::STREAM_STRING_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_FUTURE_SYMBOL,				VS::CStreamFactory::STREAM_STRING_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_FUTURE_OPTION_SYMBOL,		VS::CStreamFactory::STREAM_64BYTE_STRING_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_EXCHANGE,					VS::CStreamFactory::STREAM_EXCHANGE_ID); 
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_OPTION_THEO_PRICE,			VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(DDS::FIELD_OPTION_CALC_PRICE,			VS::CStreamFactory::STREAM_FLOAT_ID);
//	VS::CStreamFactory::Instance().AddField(IVRMFields::FIELD_UPDATE_DATE,			VS::CStreamFactory::STREAM_DATETIME_ID);
//
//	TableInitializer::intialize_writers();
//}
////-------------------------------------------------------------------------------------------//
//void CIVRMFilter::SetDataSource(IEtsMainPtr ptr)
//{
//	m_dsPtr = ptr;
//	LOG4CPLUS_DEBUG(VS::Log , _T("Set Data Source"));
//}
////-------------------------------------------------------------------------------------------//
//void CIVRMFilter::ProcessFutureQuote(const VS::CResponseBlock* responseBlock)
//{
//	ITicker ticker;
//	QuoteUpdateInfo quote;
//	std::string Symbol;
//
//	VS::CResponseBlock::const_iterator it = responseBlock->Begin();
//	VS::CResponseBlock::const_iterator itEnd = responseBlock->End();
//	for (; it != itEnd; ++it)
//	{
//		const VS::CResponseRecord& record = *it;
//
//		ticker.Type = enFUT;
//
//		_bstr_t Symbol(record.GetField(DDS::FIELD_FUTURE_SYMBOL).AsString().c_str());
//		ticker.Symbol = Symbol.GetBSTR();
//
//		_bstr_t primaryExch(L"");
//		ticker.Exchange		= primaryExch.GetBSTR();
//
//		_bstr_t quoteBidExchange(record.GetField(DDS::FIELD_BID_EXCHANGE).AsString().c_str());
//		quote.BidExchange	= quoteBidExchange.GetBSTR();
//
//		_bstr_t quoteAskExchange(record.GetField(DDS::FIELD_ASK_EXCHANGE).AsString().c_str());
//		quote.AskExchange	= quoteAskExchange.GetBSTR();
//
//		_bstr_t quoteCurrency(L"USD");
//		quote.Currency		= quoteCurrency.GetBSTR();
//
//		_bstr_t quoteExchange(L"");
//		quote.Exchange		= quoteExchange.GetBSTR();
//
//		quote.BidPrice		= record.GetField(DDS::FIELD_BID).AsDouble();
//		if (_finite(quote.BidPrice) == 0) 
//			quote.BidPrice = BAD_DOUBLE_VALUE;
//
//		quote.AskPrice		= record.GetField(DDS::FIELD_ASK).AsDouble();
//		if (_finite(quote.AskPrice) == 0) 
//			quote.AskPrice = BAD_DOUBLE_VALUE;
//
//		quote.LastPrice		= record.GetField(DDS::FIELD_LAST).AsDouble();
//		if (_finite(quote.LastPrice) == 0) 
//			quote.LastPrice = BAD_DOUBLE_VALUE;
//
//		quote.Volume			= static_cast<long>(record.GetField(DDS::FIELD_VOLUME).AsLongLong());
//		quote.BidSize		= record.GetField(DDS::FIELD_BID_SIZE).AsInt();
//		quote.AskSize		= record.GetField(DDS::FIELD_ASK_SIZE).AsInt();
//		quote.UpdateDateTime = record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
//		quote.BidDateTime	= record.GetField(DDS::FIELD_BID_DATE).AsDateTime();
//		quote.AskDateTime	= record.GetField(DDS::FIELD_ASK_DATE).AsDateTime();
//		quote.LastDateTime	= record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
//
//		m_dsPtr->SetQuote(&ticker, &quote);
//	}
//}
////-------------------------------------------------------------------------------------------//
//void CIVRMFilter::ProcessFutureOptionQuote(const VS::CResponseBlock* responseBlock)
//{
//
//	ITicker ticker;
//	QuoteUpdateInfo quote;
//	std::string Symbol;
//	long updateCount = 0;
//
//	VS::CResponseBlock::const_iterator it = responseBlock->Begin();
//	VS::CResponseBlock::const_iterator itEnd = responseBlock->End();
//	for (; it != itEnd; ++it)
//	{
//		const VS::CResponseRecord& record = *it;
//
//		ticker.Type = enFOP;
//
//		_bstr_t Symbol(record.GetField(DDS::FIELD_FUTURE_OPTION_SYMBOL).AsString().c_str());
//		ticker.Symbol = Symbol.GetBSTR();
//
//		_bstr_t primaryExch(L"");
//		ticker.Exchange		= primaryExch.GetBSTR();
//
//		_bstr_t quoteBidExchange(record.GetField(DDS::FIELD_BID_EXCHANGE).AsString().c_str());
//		quote.BidExchange	= quoteBidExchange.GetBSTR();
//
//		_bstr_t quoteAskExchange(record.GetField(DDS::FIELD_ASK_EXCHANGE).AsString().c_str());
//		quote.AskExchange	= quoteAskExchange.GetBSTR();
//
//		_bstr_t quoteCurrency(L"USD");
//		quote.Currency		= quoteCurrency.GetBSTR();
//
//		_bstr_t quoteExchange(L"");
//		quote.Exchange		= quoteExchange.GetBSTR();
//
//		quote.BidPrice		= record.GetField(DDS::FIELD_BID).AsDouble();
//		if (_finite(quote.BidPrice) == 0) 
//			quote.BidPrice = BAD_DOUBLE_VALUE;
//
//		quote.AskPrice		= record.GetField(DDS::FIELD_ASK).AsDouble();
//		if (_finite(quote.AskPrice) == 0) 
//			quote.AskPrice = BAD_DOUBLE_VALUE;
//
//		quote.LastPrice		= record.GetField(DDS::FIELD_LAST).AsDouble();
//		if (_finite(quote.LastPrice) == 0) 
//			quote.LastPrice = BAD_DOUBLE_VALUE;
//
//		quote.Volume			= static_cast<long>(record.GetField(DDS::FIELD_VOLUME).AsLongLong());
//		quote.BidSize		= record.GetField(DDS::FIELD_BID_SIZE).AsInt();
//		quote.AskSize		= record.GetField(DDS::FIELD_ASK_SIZE).AsInt();
//		quote.UpdateDateTime = record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
//		quote.BidDateTime	= record.GetField(DDS::FIELD_BID_DATE).AsDateTime();
//		quote.AskDateTime	= record.GetField(DDS::FIELD_ASK_DATE).AsDateTime();
//		quote.LastDateTime	= record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
//
//		m_dsPtr->SetQuote(&ticker, &quote);
//
//		updateCount++;
//	}
//	//std::cout<<"Future option quotes: " << updateCount << std::endl;
//}
////-------------------------------------------------------------------------------------------//
//void CIVRMFilter::ProcessOptionQuote(const VS::CResponseBlock* responseBlock)
//{
//	ITicker ticker;
//	QuoteUpdateInfo quote;
//	std::string Symbol;
//
//	VS::CResponseBlock::const_iterator it = responseBlock->Begin();
//	VS::CResponseBlock::const_iterator itEnd = responseBlock->End();
//	for (; it != itEnd; ++it)
//	{
//		const VS::CResponseRecord& record = *it;
//
//		ticker.Type = enOPT;
//
//		_bstr_t Symbol(record.GetField(DDS::FIELD_OPTION_SYMBOL).AsString().c_str());
//		ticker.Symbol = Symbol.GetBSTR();
//
//		_bstr_t primaryExch(L"");
//		ticker.Exchange		= primaryExch.GetBSTR();
//
//		_bstr_t quoteBidExchange(record.GetField(DDS::FIELD_BID_EXCHANGE).AsString().c_str());
//		quote.BidExchange	= quoteBidExchange.GetBSTR();
//
//		_bstr_t quoteAskExchange(record.GetField(DDS::FIELD_ASK_EXCHANGE).AsString().c_str());
//		quote.AskExchange	= quoteAskExchange.GetBSTR();
//
//		_bstr_t quoteCurrency(L"USD");
//		quote.Currency		= quoteCurrency.GetBSTR();
//
//		_bstr_t quoteExchange(L"");
//		quote.Exchange		= quoteExchange.GetBSTR();
//
//		quote.BidPrice		= record.GetField(DDS::FIELD_BID).AsDouble();
//		if (_finite(quote.BidPrice) == 0) 
//			quote.BidPrice = BAD_DOUBLE_VALUE;
//
//		quote.AskPrice		= record.GetField(DDS::FIELD_ASK).AsDouble();
//		if (_finite(quote.AskPrice) == 0) 
//			quote.AskPrice = BAD_DOUBLE_VALUE;
//
//		quote.LastPrice		= record.GetField(DDS::FIELD_LAST).AsDouble();
//		if (_finite(quote.LastPrice) == 0) 
//			quote.LastPrice = BAD_DOUBLE_VALUE;
//
//		quote.Volume			= static_cast<long>(record.GetField(DDS::FIELD_VOLUME).AsLongLong());
//		quote.BidSize		= record.GetField(DDS::FIELD_BID_SIZE).AsInt();
//		quote.AskSize		= record.GetField(DDS::FIELD_ASK_SIZE).AsInt();
//		quote.UpdateDateTime = record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
//		quote.BidDateTime	= record.GetField(DDS::FIELD_BID_DATE).AsDateTime();
//		quote.AskDateTime	= record.GetField(DDS::FIELD_ASK_DATE).AsDateTime();
//		quote.LastDateTime	= record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
//
//		m_dsPtr->SetQuote(&ticker, &quote);
//	}
//}
////-------------------------------------------------------------------------------------------//
//void CIVRMFilter::ProcessEquityQuote(const VS::CResponseBlock* responseBlock)
//{
//	ITicker ticker;
//	QuoteUpdateInfo quote;
//
//	VS::CResponseBlock::const_iterator it = responseBlock->Begin();
//	VS::CResponseBlock::const_iterator itEnd = responseBlock->End();
//	for (; it != itEnd; ++it)
//	{
//		const VS::CResponseRecord& record = *it;
//		
//		ticker.Type = enSTK;
//
//		_bstr_t Symbol(record.GetField(DDS::FIELD_STOCK_SYMBOL).AsString().c_str());
//		ticker.Symbol = Symbol.GetBSTR();
//
//		_bstr_t primaryExch(L"");
//		ticker.Exchange		= primaryExch.GetBSTR();
//
//		_bstr_t quoteBidExchange(record.GetField(DDS::FIELD_BID_EXCHANGE).AsString().c_str());
//		quote.BidExchange	= quoteBidExchange.GetBSTR();
//
//		_bstr_t quoteAskExchange(record.GetField(DDS::FIELD_ASK_EXCHANGE).AsString().c_str());
//		quote.AskExchange	= quoteAskExchange.GetBSTR();
//
//		_bstr_t quoteCurrency(L"USD");
//		quote.Currency		= quoteCurrency.GetBSTR();
//
//		_bstr_t quoteExchange(L"");
//		quote.Exchange		= quoteExchange.GetBSTR();
//
//		quote.BidPrice		= record.GetField(DDS::FIELD_BID).AsDouble();
//		if (_finite(quote.BidPrice) == 0) 
//			quote.BidPrice = BAD_DOUBLE_VALUE;
//
//		quote.AskPrice		= record.GetField(DDS::FIELD_ASK).AsDouble();
//		if (_finite(quote.AskPrice) == 0) 
//			quote.AskPrice = BAD_DOUBLE_VALUE;
//
//		quote.LastPrice		= record.GetField(DDS::FIELD_LAST).AsDouble();
//		if (_finite(quote.LastPrice) == 0) 
//			quote.LastPrice = BAD_DOUBLE_VALUE;
//
//		quote.Volume			= static_cast<long>(record.GetField(DDS::FIELD_VOLUME).AsLongLong());
//		quote.BidSize		= record.GetField(DDS::FIELD_BID_SIZE).AsInt();
//		quote.AskSize		= record.GetField(DDS::FIELD_ASK_SIZE).AsInt();
//		quote.UpdateDateTime = record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
//		quote.BidDateTime	= record.GetField(DDS::FIELD_BID_DATE).AsDateTime();
//		quote.AskDateTime	= record.GetField(DDS::FIELD_ASK_DATE).AsDateTime();
//		quote.LastDateTime	= record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
//
//		m_dsPtr->SetQuote(&ticker, &quote);
//	}
//}
////-------------------------------------------------------------------------------------------//
//CORBA::Any* CIVRMFilter::ApplyFilter(const CORBA::Any& anyData)
//{
//	CAutoLock lock(m_filterLock);
//
//	LOG4CPLUS_INFO(VS::Log , _T("Start [ApplyFilter]"));
//	//printf("ApplyFilter [call]\n");
//
//	_set_se_translator( SeTranslator );
//	
//	CORBA::Any* result = NULL; 
//	DDS::IVData* ivData = NULL;
//	//processing IVData (parsing, updating IVRM structures)
//	try
//	{
//		result = new CORBA::Any();
//		
//		if (anyData >>= ivData) //convert corba::any to IVData.
//		{
//			TQ_container quotes_table;
//			quotes_table.reserve(30000);
//
//			IvDataParser parser;
//			parser.parse(ivData->get_buffer(), ivData->length(), quotes_table);
//
//			//VS::CVSMessageParser	msgParser;
//			//LOG4CPLUS_INFO(VS::Log , _T("Start [DeserializeMessage]"));
//
//			//std::auto_ptr<VS::CResponseBlockList> responseBlockList = 
//			//	msgParser.DeserializeMessage(ivData->get_buffer(), ivData->length());
//
//			//if (responseBlockList->IsEmpty())
//			//{
//			//	LOG4CPLUS_INFO(VS::Log , _T("Complete [DeserializeMessage] - ResponseBlock is empty."));
//			//	return result;
//			//}			
//			//else
//			//{ 
//			//	LOG4CPLUS_INFO(VS::Log , _T("Complete [DeserializeMessage]"));
//			//	LOG4CPLUS_INFO(VS::Log , _T("Start [Process incoming data]"));
//
//			//	const VS::CResponseBlock* responseBlock = responseBlockList->Front();
//			//	VS::CResponseBlockList::const_iterator responseBlockListIter = responseBlockList->Begin();
//
//			//	for (; responseBlockListIter != responseBlockList->End(); ++responseBlockListIter)
//			//	{
//			//		const VS::CResponseBlock* responseBlock = *responseBlockListIter;
//			//		long messageType = static_cast<long>(responseBlock->GetMessageType());
//			//		LOG4CPLUS_INFO(VS::Log , _T("Process [Table#: ") << static_cast<unsigned>(messageType) << _T(" ] data."));
//
//			//		switch(messageType)
//			//		{
//			//		case DDS::T_OPTION_QUOTE:
//			//			{
//			//				ProcessOptionQuote(responseBlock);
//			//				break;
//			//			}
//			//		case DDS::T_EQUITY_QUOTE:
//			//			{
//			//				ProcessEquityQuote(responseBlock);
//			//				break;
//			//			}
//			//		case DDS::T_FUTURE_QUOTE:
//			//			{
//			//				ProcessFutureQuote(responseBlock);
//			//				break;
//			//			}
//			//		case DDS::T_DIRECT_FUTURE_OPTION_QUOTE:
//			//			{
//			//				ProcessFutureOptionQuote(responseBlock);
//			//				break;
//			//			}
//			//		default:
//			//			{
//			//				LOG4CPLUS_WARN(VS::Log, _T("Unsupported [Table# ") << messageType<<_T(" ]"));
//			//				continue;
//			//				break;
//			//			}
//			//		}
//			//	}
//
//			//	LOG4CPLUS_INFO(VS::Log , _T("Complete [Process incoming data]"));
//			//} 
//		} 
//		else
//		{
//			LOG4CPLUS_INFO(VS::Log , _T("Empty data [anyData >>= ivData]"));
//			return result;
//		}
//	}
//	catch(CSeException* e)
//	{
//		CString strErrDescription;
//		e->GetErrorMessage(strErrDescription);
//		LOG4CPLUS_FATAL(VS::Log , _T("SEH exception occured while processing IVData. ") << strErrDescription);
//		e->Delete();
//		return result;
//	}
//	catch (...)
//	{
//		LOG4CPLUS_ERROR(VS::Log , _T("Unknown C++ exception occured while processing IVData."));
//		return result;
//	}
//	//---------------------------------//
//	//calculate updated contract
//	LPSAFEARRAY recalculatedData = NULL;
//	try
//	{
//		if (m_dsPtr)
//		{
//			LOG4CPLUS_INFO(VS::Log , _T("Start [Calculate contracts]"));
//
//			long stBeginCalc = GetTickCount();
//			recalculatedData = m_dsPtr->CalculateUpdatedContracts();
//			long stEndCalc = GetTickCount();
//
//			LOG4CPLUS_INFO(VS::Log , _T("Complete [Calculate contracts]"));
//
//			LOG4CPLUS_INFO(VS::Log , _T("Calculated [Contracts: ") 
//				<< (recalculatedData == NULL ? 0 : recalculatedData->rgsabound[0].cElements) 
//				<< _T(" ] in [") << stEndCalc - stBeginCalc << _T("] ticks."));			
//
//			/*printf("Calculated in: [%i] ticks\n", stEndCalc - stBeginCalc);
//			if (recalculatedData)
//				printf("Calculated: [%i]\n",recalculatedData->rgsabound[0].cElements);*/
//
//		}
//	}
//	catch(CSeException* e)
//	{
//		CString strErrDescription;
//		e->GetErrorMessage(strErrDescription);
//		LOG4CPLUS_FATAL(VS::Log , _T("SEH exception occured while calculating.") << strErrDescription);
//		e->Delete();
//		return result;
//	}
//	catch (...)
//	{
//		if (recalculatedData != NULL)	
//			::SafeArrayDestroy(recalculatedData);
//
//		LOG4CPLUS_ERROR(VS::Log, "Unknown C++ exception occured while calculating data.");
//		return result;
//	}
//	//---------------------------------//
//	//pack data and return
//	//---------------------------------//
//	DataContainer data;
//	data.add_data(35, recalculatedData);
//	IvDataPacker packer;
//
//	BYTE* message = 0;
//	long message_size = 0;
//	message_size = packer.pack(data, message);
//	data.clear();
//
//	DDS::IVData msgSequence(message_size, message_size, message, 1);
//	*result <<= msgSequence;
//
//	return result;
//	//-------------------------------------------------------------------------//
//	//Pack IVRM data to IV structure's
//	//try
//	//{
//	//	if(recalculatedData)
//	//	{
//	//		LOG4CPLUS_INFO(VS::Log , _T("Start [Packing IVRM Data]"));
//
//	//		IRisksFullInfo* pvDataOut = NULL;
//	//		long sizeOut = recalculatedData->rgsabound[0].cElements;					
//
//	//		HRESULT hr = S_OK;
//
//	//		if (SUCCEEDED(hr = ::SafeArrayAccessData( recalculatedData, (void**)&pvDataOut) ) )
//	//		{
//	//			for (int i = 0; i < sizeOut;)
//	//			{
//	//				VS::FieldDataList 	fieldDataList;
//
//	//				fieldDataList.push_back(VS::CFieldData(_bstr_t(pvDataOut[i].Ticker.Symbol))); //symbol
//	//				fieldDataList.push_back(VS::CFieldData(_bstr_t(pvDataOut[i].BaseTicker.Symbol))); //Base symbol
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<int>(pvDataOut[i].Ticker.Type))); //symbol type
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<int>(pvDataOut[i].BaseTicker.Type)));//Base symbol type
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.IVola)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.Delta)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.Vega)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.Gamma)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.Theta)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.Rho)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.TheoPrice)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.ContractPrice)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.BaseContractPrice)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.Volga)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.DeltaVega)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.DeltaTheta)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.GammaVega)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.GammaTheta)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.TheoVola)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.BidPrice)));
//	//				fieldDataList.push_back(VS::CFieldData(VS::CDateTimeType(pvDataOut[i].Risks.BidDate)));
//	//				fieldDataList.push_back(VS::CFieldData("*"));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<long>(pvDataOut[i].Risks.BidSize)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.AskPrice)));
//	//				fieldDataList.push_back(VS::CFieldData(VS::CDateTimeType(pvDataOut[i].Risks.AskDate)));
//	//				fieldDataList.push_back(VS::CFieldData("*"));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<long>(pvDataOut[i].Risks.AskSize)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.LastPrice)));
//	//				fieldDataList.push_back(VS::CFieldData(VS::CDateTimeType(pvDataOut[i].Risks.LastDate)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<long>(pvDataOut[i].Risks.Volume)));
//	//				fieldDataList.push_back(VS::CFieldData(VS::CDateTimeType(pvDataOut[i].Risks.UpdateDate)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.TheoPriceBid)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.TheoPriceAsk)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.ContractPriceBid)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.ContractPriceAsk)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.BaseContractPriceBid)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.BaseContractPriceAsk)));
//	//				fieldDataList.push_back(VS::CFieldData(static_cast<float>(pvDataOut[i].Risks.IntrinsicValue)));
//
//	//				VS::CTableRow::pointer row = new VS::CTableRow(i++, fieldDataList);
//	//				m_tableRowList.push_back(row);
//	//			}
//	//			::SafeArrayUnaccessData(recalculatedData);
//	//		}
//	//		else
//	//		{
//	//			LOG4CPLUS_ERROR(VS::Log, _T("Error occure while accessing SafeArray."));
//	//		}
//
//	//		::SafeArrayDestroy(recalculatedData);
//
//	//		LOG4CPLUS_INFO(VS::Log , _T("Complete [Packing IVRM Data]"));
//	//	}
//	//}
//	//catch(CSeException* e)
//	//{
//	//	CString strErrDescription;
//	//	e->GetErrorMessage(strErrDescription);
//	//	LOG4CPLUS_FATAL(VS::Log , _T("SEH exception occured while packing IVRM data.")<<strErrDescription);
//	//	e->Delete();
//	//	return result;
//	//}
//	//catch(...)
//	//{
//	//	LOG4CPLUS_ERROR(VS::Log, "Unknown C++ exception occured while packing IVRM data.");
//	//	return result;
//	//}
//	//-------------------------------------------------------------------------//
//	//Assemble recalculated data
//	//try 
//	//{
//	//	if (!m_tableRowList.empty())
//	//	{
//	//		LOG4CPLUS_INFO(VS::Log, _T("Start [Assemble IV message.]"));
//
//	//		long stReturningBegin = GetTickCount();
//
//	//		VS::CMessageTrails messageTrails(	IVRMFields::T_IVRM_RISKS,
//	//			VS::CMessageTrails::enRealtimeMessage,
//	//			m_calcPosFieldIDList, 
//	//			m_tableRowList, 
//	//			m_calcPosFldIdxList);
//
//	//		messageTrails.SetProtocolVersion(1);
//
//	//		VS::CMessage::pointer message = VS::CMessageFactory::Instance().CreateMessage(messageTrails);
//	//		if (message)
//	//		{
//	//			VS::CMessageGroup messageGroup(VS::enCompressionNone);
//	//			messageGroup.AddMessage(message);
//	//			CORBA::ULong msgSize = 0;
//	//			BYTE* msg = messageGroup.AssembleMessage(msgSize);
//	//			DDS::IVData msgSequence(msgSize, msgSize, msg, 1);
//	//			*result <<= msgSequence;
//	//		}
//
//	//		long stReturningEnd = GetTickCount();
//	//		//free allocated rows
//	//		for (VS::TableRowList::iterator rowIter = m_tableRowList.begin(); rowIter != m_tableRowList.end(); ++rowIter)
//	//		{
//	//			VS::CTableRow::pointer row = *rowIter;
//	//			delete row;
//	//		}
//	//		m_tableRowList.clear();
//
//	//		LOG4CPLUS_INFO(VS::Log, _T("Complete [Assemble IV message.]"));
//	//	}
//	//	else
//	//	{
//	//		LOG4CPLUS_INFO(VS::Log, _T("Empty data to return."));
//	//	}
//	//}
//	//catch(CSeException* e)
//	//{
//	//	CString strErrDescription;
//	//	e->GetErrorMessage(strErrDescription);
//	//	LOG4CPLUS_FATAL(VS::Log , _T("SEH exception occured while assembling IV message.") << strErrDescription);
//	//	e->Delete();
//	//	return result;
//	//}
//	//catch(...)
//	//{
//	//	LOG4CPLUS_ERROR(VS::Log, _TEXT("Unknown C++ exception occured while assembling IV message."));
//	//	return result;
//	//}
//
//	//LOG4CPLUS_INFO(VS::Log , _T("Complete [ApplyFilter]"));
//	//return result;
//}
////-------------------------------------------------------------------------------------------//