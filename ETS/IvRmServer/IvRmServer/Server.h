#pragma once

#include "TradesCache.h"
#include "Controller.h"
#include "FilterManager.h"

class TickCounter{
public:
	long start_tick;

	void start(){
		start_tick = ::GetTickCount();
	};

	long stop(){
		return ::GetTickCount() - start_tick;
	};
};

class IniReader{
public:

	class Section{
	public:

		Section(const std::string& id);

		typedef std::pair<std::string, std::string> key_value;
		typedef std::vector<key_value> key_container;

		bool 
		get_value(const std::string& key, std::string& value, const std::string& default_value);

		bool
		get_value(const std::string& key, long& value, long default_value);

		virtual 
		void add(const std::string& key, const std::string& value);

		key_container parameters_;
		std::string id_;
	};

	typedef std::vector<std::string> key_container;

	IniReader(const std::string& file_name);

	long 
	read_section(Section& sc);

	long
	read_key(const std::string& section_id, const std::string& key, std::string& value);

	long 
	read_keys_list(const std::string& section_id, key_container& keys);

	long 
	read_sections_list(key_container& keys);

private:
	long 
	split(std::vector<char>& buffer, long size, key_container& keys);

	key_container sections;
	std::string	file_name_;
};

class DataContainer{
public:

	typedef std::pair<long, LPSAFEARRAY> my_pair;
	typedef std::vector<my_pair> container;
	typedef container::iterator my_iterator;

	void add_data(long data_type, LPSAFEARRAY& data);
	void clear();

	my_iterator get_begin();
	my_iterator get_end();

	bool is_empty();
private:
	container arrays;
};

class DataPacker{
public:
	virtual long pack(DataContainer& data, BYTE*& message) = 0;
};

class TickerWrapper{
public:
	ITicker ticker;

	TickerWrapper(){
		ticker.Symbol = 0;
		ticker.Exchange = 0;
	};

	~TickerWrapper(){
		if (ticker.Exchange){
			::SysFreeString(ticker.Exchange);
		};

		if (ticker.Symbol){
			::SysFreeString(ticker.Symbol);
		};

		ticker.Exchange = 
			ticker.Symbol = 0;
	};

	ITicker& operator()(){
		return ticker;
	};

	ITicker* operator->(){
		return &ticker;
	};
};

class QuoteWrapper{
public:
	QuoteUpdateInfo quote;

	QuoteWrapper(){
		quote.AskExchange = 0;
		quote.BidExchange = 0;
		quote.Currency = 0;
		quote.Exchange = 0;
	};

	~QuoteWrapper(){
		if (quote.AskExchange){
			::SysFreeString(quote.AskExchange);
		};
		if (quote.BidExchange){
			::SysFreeString(quote.BidExchange);
		};
		if (quote.Currency){
			::SysFreeString(quote.Currency);
		};
		if (quote.Exchange){
			::SysFreeString(quote.Exchange);
		};
		quote.AskExchange = 
			quote.BidExchange = 
				quote.Currency =
					quote.Exchange = 0;
	};

	QuoteUpdateInfo& operator()(){
		return quote;
	};

	QuoteUpdateInfo* operator->(){
		return &quote;
	};
};

inline BSTR 
get_BSTR(const std::string& value){
	//do not forget to call SysFreeString
	return _bstr_t(value.c_str()).Detach();	
};

inline BSTR
get_BSTR(const char* value){
	//do not forget to call SysFreeString
	return _bstr_t(value).Detach();
};

inline double 
get_VALUE(const double& value){
	return (_finite(value) ? value : BAD_DOUBLE_VALUE);
};

class IvRmException{
public:
	
};

typedef std::pair<TickerWrapper, QuoteWrapper> TQ_pair;
typedef std::vector<TQ_pair> TQ_container; 

class Parser{
public:
	virtual long parse(BYTE* message, long message_size, TQ_container& response) = 0;
};

class IvDataParser{
public:
	/*virtual*/
	long parse(BYTE* message, long message_size, TQ_container& response);

private:
	std::auto_ptr<VS::CResponseBlockList> deserialize(BYTE* message, long message_size);
	long parse_equity_quote(const VS::CResponseBlock* response_block, TQ_container& response);
	long parse_option_quote(const VS::CResponseBlock* response_block, TQ_container& response);
	long parse_future_quote(const VS::CResponseBlock* response_block, TQ_container& response);
	long parse_future_option_quote(const VS::CResponseBlock* response_block, TQ_container& response);
};

class IvDataPacker: public DataPacker{
public:

	IvDataPacker();
	/*virtual*/
	long pack(DataContainer& data, BYTE*& message);
	
	typedef std::map<long, VS::TableRowList> iv_tables;

private:
	long clear_tables(iv_tables& tables);
	long fill_iv_tables(DataContainer& data, iv_tables& tables);
	long assemble_message(iv_tables& tables, BYTE*& msg);
	long pack_array(long data_type, LPSAFEARRAY& arr, VS::TableRowList& table);
	long pack_analytics(LPSAFEARRAY& arr, VS::TableRowList& table);
	long pack_analytical_atom(IRisksFullInfo& anx_atom, VS::FieldDataList& fields);
	VS::FieldDataList fields;
};

class TableInitializer{
public:
	static void intialize_writers();
	static void get_analytics_table(VS::FieldIDList &fieldIDList, VS::IDList &idList);
};

class DataTransmitter{
public:
	DataPacker* packer;
	
	DataTransmitter(DataPacker* packer):packer(packer){
	};
	
	virtual long transmit(DataContainer& data) = 0;
};

class IvDataTransmitter: public DataTransmitter{
public:
	IvDataTransmitter(DataPacker* packer):DataTransmitter(packer){
	};
	
	void initialize_by(IniReader::Section& settings);

	/*virtual*/
	long transmit(DataContainer& data);

	DDS::IVDataManager_var data_manager;
	
	std::string login_;
	std::string password_;
	std::string receiver_;
	std::string session_id_;

private:
	CLock lock_;
};

class CalculationManager: public EgLib::CThread{
public:
	CalculationManager(	IEtsMainPtr sp_main,
						long sampling_priod,
						DataTransmitter* transmitter);
	virtual
	~CalculationManager();
	
	UINT Run();
	
	long calculate(LPSAFEARRAY& analytics);

private:
	long sampling_period;
	IEtsMainPtr sp_main;
	DataTransmitter* transmitter;
};

class IvRmFilter:	public POA_DDS::CustomFilter,
					public PortableServer::RefCountServantBase{
public:
	//ctor
	IvRmFilter(	IEtsMainPtr core, 
				DataPacker* packer, 
				const std::string& object_name);

	//dtor
	virtual 
	~IvRmFilter();

	void 
	get_object_name(std::string& name);

	CORBA::Any* 
	ApplyFilter(const CORBA::Any& anyData);
	
private:
	IEtsMainPtr core;
	DataPacker* packer;
	std::string object_name;
	TQ_container quotes_table;
	
	CLock filter_lock;
	CORBA::Any* 
	apply_filter_impl(const CORBA::Any& data);
};

class CorbaSettings: public IniReader::Section{
public:

	CorbaSettings(const std::string& id);
	
	/*virtual*/
	void add(const std::string& key, const std::string& value);

	void get_orb_args(char**& args, int& count);
};

class CServer:	public EgLib::CThread,
				public IDispEventSimpleImpl<0x1, CServer, &DIID__IEtsMainEvents>
{
public:
	CServer(void);
	~CServer(void);

public:
	UINT					Run();
	void					Initialiaze();

	BEGIN_SINK_MAP(CServer)
		SINK_ENTRY_INFO(0x1, DIID__IEtsMainEvents, 2/*DISPID_OnAnalytics*/, raw_OnAnalytics, &m_fiOnAnalytics)
	END_SINK_MAP()

	static _ATL_FUNC_INFO		m_fiOnAnalytics;

	STDMETHOD(raw_OnAnalytics)(SAFEARRAY* anx);

	static
	log4cplus::Logger& server_logger();
	
private:
	IEtsMainPtr				m_spMain;
	IVolatilitySourcePtr	m_spVolatilitySource;

	CTradesCachePtr			m_spTradesCache;
	CSettingsPtr			m_spSettings;	
	CControllerPtr			m_spController;
	
	CalculationManager*		manager;
	IvRmFilter*				filter;
	IvDataTransmitter*		transmitter;

	void activate_filter(IvRmFilter* filter);
	void activate_transmiter(IvDataTransmitter* transmitter);
	bool initialize_corba(CorbaSettings& settings);
	bool destroy_corba();
	
	static 
	log4cplus::Logger& corba_logger();

	static
	void corba_log_function(const char* msg);

	void initialize_logger(log4cplus::Logger& my_logger, IniReader::Section& section);

	IVolatilitySourcePtr GetVolatilitySource();
};