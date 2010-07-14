#include "StdAfx.h"
#include "Server.h"

_ATL_FUNC_INFO CServer::m_fiOnAnalytics = 
{CC_STDCALL, VT_EMPTY, 1, {VT_DISPATCH} };
//---------------------------------------------------------//
STDMETHODIMP 
CServer::raw_OnAnalytics(SAFEARRAY* anx) {
	LOG4CPLUS_INFO(server_logger(), 
	"Analytics updated.");

	//DataContainer data_container;

	//data_container.add_data(35, anx);
	//transmitter->transmit(data_container);
	//data_container.clear();

	return S_OK;
};
//---------------------------------------------------------//
CServer::CServer(void) {
	m_spMain = NULL;
	m_spVolatilitySource = NULL;
	m_spTradesCache = CTradesCachePtr(new CTradesCache);
	m_spSettings = CSettingsPtr(new CXmlSettings);
	m_spController = CControllerPtr(new CController);
};
//---------------------------------------------------------//
CServer::~CServer(void) {
	EgLib::CThread::Stop(true, 5000);
	
	manager->Stop(true, 5000);
	delete manager;
	delete filter;

	destroy_corba();
	
	omniORB::setLogFunction(0);
	
	m_spMain = NULL;
	m_spVolatilitySource = NULL;
};
//---------------------------------------------------------//
IVolatilitySourcePtr 
CServer::GetVolatilitySource() {
	try	{

		if (m_spVolatilitySource == NULL) {

			BSTR bsTitle, bsFileName, bsVersion, bsProgID;
			BSTR	bsDBConnectionString;
			m_spSettings->GetDBConnection(&bsDBConnectionString);

			IVADBLayoutPtr spDBLayout = NULL;
			HRESULT hr = spDBLayout.CreateInstance(__uuidof(DBLayout));
			if(FAILED(hr))
				utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to create DBLayout object.");
			spDBLayout->put_ConnectionString(bsDBConnectionString);

			IVolatilitySourcesPtr spVolaSources = NULL;
			hr = spVolaSources.CreateInstance(__uuidof(VolatilitySources));
			if(FAILED(hr))
				utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to create VolatilitySources object.");

			hr = spVolaSources->GetVolatilitySourceInfoByID(0, &bsTitle, &bsFileName, &bsVersion, &bsProgID);
			if(FAILED(hr))
				utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to GetVolatilitySourceInfoByID.");

			hr = spVolaSources->get_VolatilitySource(0, &m_spVolatilitySource);
			if(FAILED(hr))
				utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to get_VolatilitySource.");

			IVAManagementPtr spManagement = spDBLayout;
			hr = m_spVolatilitySource->put_DataSource(spManagement);
			if(FAILED(hr))
				utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to put_DataSource.");

			m_spVolatilitySource->put_EnableEditing(VARIANT_TRUE);
			m_spVolatilitySource->put_EnableEvents(VARIANT_TRUE);
		}
	}
	catch (_com_error err) {
		LOG4CPLUS_ERROR(CServer::server_logger(),
		"com_error occured while get_volatility_source. " <<
		err.Description());
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(),
		"Unknown error occured while initializing server.");
	};
	return m_spVolatilitySource;
};
//---------------------------------------------------------//
void
CServer::initialize_logger(log4cplus::Logger& my_logger, IniReader::Section& section){
	using namespace log4cplus;
	
	my_logger.removeAllAppenders();

	std::string log_pattern;
	section.get_value("LOG_PATTERN", log_pattern, "%D{%c} [%t] [%p]: %m%n");

	std::string log_file_name;
	section.get_value("LOG_FILE_NAME", log_file_name, "Server.log");

	long log_parts;
	section.get_value("LOG_PARTS", log_parts, 3);

	long log_file_size;
	section.get_value("LOG_FILE_SIZE", log_file_size, 100);

	long log_level;
	section.get_value("LOG_LEVEL", log_level, long(log4cplus::FATAL_LOG_LEVEL));

	SharedAppenderPtr appender(new RollingFileAppender(	log_file_name, 
														log_file_size * 1024 * 1024, 
														log_parts));
	appender->setName(_T("log_appender"));
	appender->setLayout(std::auto_ptr<Layout>(new PatternLayout(log_pattern)));
	my_logger.setLogLevel(LogLevel(log_level));
	my_logger.addAppender(appender);

	LOG4CPLUS_INFO(my_logger, _T("logger initialized"));
};
//---------------------------------------------------------//
/*static*/
log4cplus::Logger&
CServer::corba_logger() {
	static log4cplus::Logger logger_(log4cplus::Logger::getInstance("corba_logger"));
	return logger_;
};
//---------------------------------------------------------//
/*static*/
log4cplus::Logger&
CServer::server_logger() {
	static log4cplus::Logger logger_(log4cplus::Logger::getInstance("server_logger"));
	return logger_;
};
//---------------------------------------------------------//
/*static*/
void 
CServer::corba_log_function(const char *msg) {
	LOG4CPLUS_TRACE(CServer::corba_logger(), msg);
};
//---------------------------------------------------------//
void 
CServer::Initialiaze() {
	
	std::string file_name;
	get_configuration_file_name(file_name);
	IniReader reader(file_name);

	IniReader::Section logger_settings("SERVER_LOG");
	reader.read_section(logger_settings);

	initialize_logger(CServer::server_logger(), logger_settings);

	try	{

		if (m_spMain != NULL) return;

		HRESULT hr = m_spMain.CreateInstance(__uuidof(EtsMain));
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to create EtsMain object.");

		hr = DispEventAdvise(m_spMain);
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to DispEventAdvise.");	

		hr = m_spMain->SetWorkingMode(enWmServer);
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to SetWorkingMode.");	

		hr = m_spMain->SetLogLevel(m_spSettings->GetLogLevel());
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to read log level from configuration file.");	

		hr = m_spMain->SetLogLifetime(m_spSettings->GetLogLifetime());
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to read log lifetime from configuration file.");	

		BSTR bsDBConnectionString;
		m_spSettings->GetDBConnection(&bsDBConnectionString);
		
		hr = m_spMain->put_DatabaseString(bsDBConnectionString);
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to put_DatabaseString.");	

		hr = m_spMain->putref_VolatilitySource(GetVolatilitySource());
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to putref_VolatilitySource.");	

		hr = m_spMain->LoadStrategy();
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to LoadStrategy.");	

		hr = m_spMain->LoadBroker();
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to LoadBrokers.");

		hr = m_spMain->LoadPriceProfile();
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to LoadPriceProfile.");

		hr = m_spMain->LoadUnderlying(0);
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to LoadUnderlying.");

		hr = m_spMain->LoadTraderGroup();
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to LoadTraderGroup.");

		hr = m_spMain->LoadTrader(0);
		if(FAILED(hr))
			utils::ThrowErrorNoSetErrorInfo(hr, L"Failed to LoadTrader.");

		//---------------------//
		//trade channel routine//
		//---------------------//
		
		m_spTradesCache->SetSettingsImpl(m_spSettings);
		m_spTradesCache->SetMain(m_spMain);
		m_spTradesCache->LoadTrades();
		m_spTradesCache->SubscribeTradeUpdate();

		m_spController->SetSettingsImpl(m_spSettings);
		m_spController->SetMain(m_spMain);
		m_spController->LoadSettings();
		m_spController->LoadAssetList();
		m_spController->SubscribeSettingsUpdate();
		m_spController->SubscribeUnderlyingUpdate();


		//-------------------------//
		TableInitializer::intialize_writers();

		IniReader::Section main_settings("MAIN");
		reader.read_section(main_settings);
		
		long recalculation_period;
		main_settings.get_value("RECALCULATION_PERIOD", recalculation_period, 5000);

		std::string filter_object_name;
		main_settings.get_value("FILTER_NAME", filter_object_name, "IvRmServer");

		filter = new IvRmFilter(m_spMain, new IvDataPacker, filter_object_name);
		
		IniReader::Section transmitter_settings("TRANSMITTER");
		reader.read_section(transmitter_settings);

		transmitter = new IvDataTransmitter(new IvDataPacker);
		transmitter->initialize_by(transmitter_settings);

		manager = new CalculationManager(m_spMain, recalculation_period, transmitter);

		CorbaSettings orb_settings("ORB");
		reader.read_section(orb_settings);

		IniReader::Section corba_logger_settings("CORBA_LOG");
		reader.read_section(corba_logger_settings);

		initialize_logger(CServer::corba_logger(), corba_logger_settings);

		if(initialize_corba(orb_settings)){
			activate_filter(filter);
			activate_transmiter(transmitter);
			manager->Start();
		};
	}
	catch (_com_error e) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"_com_error occured while initialize server: " 
		<< e.Description());
		throw;
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"Unknown error occured while initialize server.");
		throw;
	};
};
//---------------------------------------------------------//
UINT	
CServer::Run() {
	try	{		
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		Initialiaze();
		
		WaitForSingleObject(CThread::GetStopEventHandle(), INFINITE);
		
		CoUninitialize();
	}
	catch (_com_error err) {
		LOG4CPLUS_ERROR(CServer::server_logger(),
		"Com error occured while server Run. " <<
		err.Description());
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(),
		"Unknown error occured while server Run.");
	};
	return 0;
};
//---------------------------------------------------------//
void
CServer::activate_filter(IvRmFilter* filter){
	try {
		int arg_count = 0;
		char** args = 0;
		CORBA::ORB_ptr orb = CORBA::ORB_init(arg_count, args);

		CORBA::Object_var poa = orb->resolve_initial_references("omniINSPOA");
		PortableServer::POA_var	ins_poa = PortableServer::POA::_narrow(poa);
		PortableServer::POAManager_var pman	= ins_poa->the_POAManager();
		pman->activate();

		std::string object_name;
		filter->get_object_name(object_name);

		PortableServer::ObjectId_var object_id = PortableServer::string_to_ObjectId(object_name.c_str());
		ins_poa->activate_object_with_id(object_id, filter);	

		CORBA::release(orb);
	}
	catch(CORBA::SystemException& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"corba::SystemException: " << ToString(err));
	}
	catch(CORBA::Exception& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"corba::Exception: " << ToString(err));
	}
	catch(omniORB::fatalException& err) {		
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"omniORB::FatalException: " << ToString(err));
	}
	catch (std::exception err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"std::exception occured while activate_filter() " <<
		err.what());
		throw;
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"Unknown exception occured while activatie_filter.");
		throw;
	};
};
//---------------------------------------------------------//
void
CServer::activate_transmiter(IvDataTransmitter* transmitter){
	try {
		int argc = 0;
		char** args = 0;
		CORBA::ORB_var orb = CORBA::ORB_init(argc, args);

		std::string remote_object_id = transmitter->receiver_;
		std::string login = transmitter->login_;
		std::string password = transmitter->password_;
		std::string session_id = transmitter->session_id_;

		CORBA::Object_var poa_obj = 
			orb->resolve_initial_references("RootPOA");

		PortableServer::POA_var poa = 
			PortableServer::POA::_narrow(poa_obj);

		PortableServer::POAManager_var pman = 
			poa->the_POAManager();

		pman->activate();

		CORBA::Object_var data_service_object = 
			orb->resolve_initial_references(remote_object_id.c_str());

		DDS::IVDataService_var data_service = 
			DDS::IVDataService::_narrow(data_service_object);

		DDS::IVSessionManager_var session_manager = 
			data_service->ResolveSessionManager(login.c_str(), password.c_str());

		transmitter->data_manager =
			session_manager->ResolveSession(session_id.c_str());
	}
	catch(CORBA::SystemException& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"corba::SystemException: " << ToString(err));
	}
	catch(CORBA::Exception& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"corba::Exception: " << ToString(err));
	}
	catch(omniORB::fatalException& err) {		
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"omniORB::FatalException: " << ToString(err));
	}
	catch (std::exception err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"std::exception occured while initialize_corba() " <<
		err.what());
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"Unknown exception occured while activating transmitter.");
		throw;
	};
};
//---------------------------------------------------------//
bool
CServer::initialize_corba(CorbaSettings& settings){
	try {
		char**	args = 0;
		int		args_count = 0;

		omniORB::setLogFunction(CServer::corba_log_function);

		settings.get_orb_args(args, args_count);
		CORBA::ORB_ptr orb = CORBA::ORB_init(args_count, args);
		
		CORBA::release(orb);
		return (orb != 0);
	}
	catch(CORBA::SystemException& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"corba::SystemException: " << ToString(err));
	}
	catch(CORBA::Exception& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"corba::Exception: " << ToString(err));
	}
	catch(omniORB::fatalException& err) {		
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"omniORB::FatalException: " << ToString(err));
	}
	catch (std::exception err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"std::exception occured while initialize_corba() " <<
		err.what());
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(),
		"Unknown exception occured while initializing CORBA.");
		throw;
	};
	return false;
};
//---------------------------------------------------------//
bool
CServer::destroy_corba(){
	try {
		int count = 0;
		char** args = 0;

		CORBA::ORB_ptr orb = CORBA::ORB_init(count, args);
		CORBA::release(orb);

		orb->shutdown(true);
		orb->destroy();
	}
	catch(CORBA::SystemException& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"corba::SystemException: " << ToString(err));
	}
	catch(CORBA::Exception& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"corba::Exception: " << ToString(err));
	}
	catch(omniORB::fatalException& err) {		
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"omniORB::FatalException: " << ToString(err));
	}
	catch (std::exception err) {
		LOG4CPLUS_ERROR(CServer::server_logger(),
		"std::exception occured while destroy_corba()" <<
		err.what());	
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(),
		"Unknown exception occured while destroying corba.");
	};
	return true;
};
//----------------------------------------------------------//
/*INI file read helper*/
IniReader::IniReader(const std::string& file_name): file_name_(file_name){
};
//----------------------------------------------------------//
long 
IniReader::read_section(Section& sc) {

	key_container section_keys;

	std::string& section_id = sc.id_;
	if (read_keys_list(section_id, section_keys) > 0) {		

		key_container::iterator it = section_keys.begin();
		key_container::iterator it_end = section_keys.end();

		std::string value;
		for ( ; it != it_end; it++) {
			std::string& key = (*it);			
			long size = read_key(section_id, key, value);
			if (size > 0) {
				sc.add(key, value);
			}
		}
	}
	return -1;		
};
//----------------------------------------------------------//
long
IniReader::read_key(const std::string& section_id, const std::string& key, std::string& value) {
	std::vector<char> buffer;
	buffer.resize(2048);

	long size = GetPrivateProfileString(section_id.c_str(), 
		key.c_str(), NULL, &buffer[0], 2048, 
		file_name_.c_str());	
	value = std::string(&buffer[0]);

	return size;
};
//----------------------------------------------------------//
long 
IniReader::read_keys_list(const std::string& section_id, key_container& keys){
	std::vector<char> buffer;
	buffer.resize(2048);
	long size = GetPrivateProfileString(section_id.c_str(), 
		NULL, NULL, &buffer[0], 2048, 
		file_name_.c_str());
	return split(buffer, size, keys);
};
//----------------------------------------------------------//
long 
IniReader::read_sections_list(key_container& keys){
	std::vector<char> buffer;
	buffer.resize(2048);	

	long size = GetPrivateProfileString(NULL, NULL, NULL, 
		&buffer[0], 2048, 
		file_name_.c_str());
	return split(buffer, size, keys);
};
//----------------------------------------------------------//
long 
IniReader::split(std::vector<char>& buffer, long size, key_container& keys){

	std::string key;
	key.clear();

	for(long i = 0; i < size; i++) {	
		if (buffer[i]  != '\0') {
			key.append(1, buffer[i]);
		}
		else{
			if (!key.empty()) {
				keys.push_back(key);
				key.clear();
			}
		}
	}

	return static_cast<long>(keys.size());
};
//---------------------------------------------------------//
IniReader::Section::Section(const std::string& id):id_(id){
};
//---------------------------------------------------------//
bool
IniReader::Section::get_value(const std::string &key, 
							  long &value,
							  long default_value){

	std::string string_value;
	if (get_value(key, string_value, "0")){
		value = atoi(string_value.c_str());
		return true;
	};
	value = default_value;
	return false;
};
//---------------------------------------------------------//
bool
IniReader::Section::get_value(const std::string& key, 
							  std::string& value,
							  const std::string& default_value){

	key_container::iterator it = parameters_.begin();
	key_container::iterator it_end = parameters_.end();

	for ( ; it != it_end; it++){
		key_value& item = (*it);
		if (item.first == key){
			value = item.second;
			return true;
		};
	};
	value = default_value;
	return false;
};
//---------------------------------------------------------//
void
IniReader::Section::add(const std::string& key, 
						const std::string& value){
	parameters_.push_back(key_value(key, value));
};
//---------------------------------------------------------//
CorbaSettings::CorbaSettings(const std::string &id):IniReader::Section(id){
};
//---------------------------------------------------------//
void
CorbaSettings::add(const std::string& key,
				   const std::string& value){
	parameters_.push_back(key_value("-" + key, value));
};
//---------------------------------------------------------//
void
CorbaSettings::get_orb_args(char**& args, int& count){

	int		argc		= __argc;
	TCHAR**	argv		= __targv;

	count = argc + static_cast<int>(2 * parameters_.size());
	args = new char*[count];
	memcpy(args, argv, sizeof(char*)*argc);

	int paramIndex = argc;

	IniReader::Section::key_container::iterator it = parameters_.begin();
	IniReader::Section::key_container::iterator it_end = parameters_.end();

	for( ;it != it_end; it++){
		IniReader::Section::key_value& pmtr = *it;
		args[paramIndex++] = const_cast<char*>(pmtr.first.c_str());
		args[paramIndex++] = const_cast<char*>(pmtr.second.c_str());
	};
};
//---------------------------------------------------------//
CalculationManager::CalculationManager(	IEtsMainPtr sp_core, 
										long sampling_rate,
										DataTransmitter* transmitter)
										:transmitter(transmitter){
	this->sampling_period = sampling_rate;
	this->sp_main = sp_core;
};
//---------------------------------------------------------//
CalculationManager::~CalculationManager(){
	EgLib::CThread::Stop(true, 5000);
	this->sp_main = NULL;
};
//---------------------------------------------------------//
long 
CalculationManager::calculate(LPSAFEARRAY& analytics){
	try {
		
		TickCounter counter;
		counter.start();
		
		_CHK(sp_main->raw_CalculateUpdatedContracts(&analytics), 
			_T("Fail to calculate updated contract."));

		LOG4CPLUS_INFO(CServer::server_logger(), 
		"Calculation complete in [" << counter.stop() << "] ticks.");
		
		if (analytics){
			return analytics->rgsabound[0].cElements;
		};
	}	
	catch (_com_error err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"ComError occured while calculate updated contracts." <<
		err.Description());
		throw;
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(),
		"Unknown error occured while calculate updated contracts.");
		throw;
	};
	return -1;
};
//---------------------------------------------------------//
UINT
CalculationManager::Run(){
	try {
		
		if (!sp_main) {
			LOG4CPLUS_ERROR(CServer::server_logger(),
			"core not initialized.");
			return 0;
		};
		
		::CoInitializeEx(NULL, COINIT_MULTITHREADED);

		LPSAFEARRAY calculation_result = 0;
		CORBA::Any* result = new CORBA::Any();
		DataContainer data_container;

		while(WAIT_TIMEOUT == ::WaitForSingleObject(GetStopEventHandle(), sampling_period)) {
							
			LOG4CPLUS_INFO(CServer::server_logger(), 
			"calculate analitycs.");
			
			try {
				long array_size = calculate(calculation_result);
			}
			catch (...) {
				continue;					
			}
			
			data_container.add_data(35, calculation_result);
			
			transmitter->transmit(data_container);
			data_container.clear();
			calculation_result = 0;
		};

		LOG4CPLUS_DEBUG(CServer::server_logger(), 
		"Calculation thread complete.");
		
		::CoUninitialize();
	}
	catch (std::exception err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"std::exception occured. " << err.what());
	}
	catch (_com_error err) {
		LOG4CPLUS_ERROR(CServer::server_logger(),
		"Com error occured in calculation thread." <<
		err.Description());
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(),
		"Unknown exception occured in calculation thread.");
	};
	return 0;
};
//---------------------------------------------------------//
void 
DataContainer::add_data(long data_type, LPSAFEARRAY& data) {
	arrays.push_back(DataContainer::my_pair(data_type, data));
};
//---------------------------------------------------------//
DataContainer::my_iterator
DataContainer::get_begin() {
	return arrays.begin();
};
//---------------------------------------------------------//
DataContainer::my_iterator
DataContainer::get_end() {
	return arrays.end();
};
//---------------------------------------------------------//
void
DataContainer::clear() {
	my_iterator it = get_begin();
	my_iterator it_end = get_end();
	for (;it != it_end; it++) {
		SafeArrayDestroy(it->second);
	};
	arrays.clear();
};
//---------------------------------------------------------//
bool
DataContainer::is_empty() {
	return arrays.empty();
};
//---------------------------------------------------------//
std::auto_ptr<VS::CResponseBlockList>
IvDataParser::deserialize(BYTE *message, long message_size) {
	try {
		VS::CVSMessageParser msgParser;
		return msgParser.DeserializeMessage(message, message_size);
	}
	catch (std::exception& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		err.what());
		throw;
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"Unknown exception occured while deserialize message.");
		throw;
	};
};
//---------------------------------------------------------//
long
IvDataParser::parse(BYTE* message, 
					long message_size, 
					TQ_container& data) {

	try {
		std::auto_ptr<VS::CResponseBlockList> responseBlockList = 
			deserialize(message, message_size);	

		long parsed_atoms = 0;
		if (!responseBlockList->IsEmpty()){
			
			VS::CResponseBlockList::const_iterator it = responseBlockList->Begin();
			VS::CResponseBlockList::const_iterator it_end = responseBlockList->End();

			for (; it != it_end; it++){
				const VS::CResponseBlock* responseBlock = *it;

				long table_id = static_cast<long>(responseBlock->GetMessageType());
				
				if (table_id == IvRmTables::IVRM_OPTION_QUOTE){
					parsed_atoms += parse_option_quote(responseBlock, data);
				}
				else if (table_id == IvRmTables::IVRM_EQUITY_QUOTE){
					parsed_atoms += parse_equity_quote(responseBlock, data);
				}
				else if (table_id == IvRmTables::IVRM_FUTURE_QUOTE){
					parsed_atoms += parse_future_quote(responseBlock, data);
				}
				else if (table_id == IvRmTables::IVRM_FUTURE_OPTION_QUOTE){
					parsed_atoms += parse_future_option_quote(responseBlock, data);
				};
			};
		};
		return parsed_atoms;
	}
	catch (std::exception& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		err.what());
		
		return -1;	
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"Unknown exception while parse ivdata.");
				
		return -2;	
	};
};
//---------------------------------------------------------//
long 
IvDataParser::parse_equity_quote(const VS::CResponseBlock* response_block, 
								 TQ_container& response) {
	
	long response_size = 0;
	TQ_container::iterator result_iterator;

	VS::CResponseBlock::const_iterator it = response_block->Begin();
	VS::CResponseBlock::const_iterator itEnd = response_block->End();

	for (; it != itEnd; ++it) {

		const VS::CResponseRecord& record = *it;
		
		response.push_back(TQ_pair());
		result_iterator = response.end() - 1; 
		
		TQ_pair& tq_pair = *result_iterator;
		TickerWrapper& ticker = tq_pair.first;
		QuoteWrapper& quote = tq_pair.second;

		ticker->Type		= enSTK;
		ticker->Symbol		= get_BSTR(record.GetField(DDS::FIELD_STOCK_SYMBOL).AsString());
		ticker->Exchange	= get_BSTR("");
		
		quote->BidExchange	= get_BSTR(record.GetField(DDS::FIELD_BID_EXCHANGE).AsString());
		quote->AskExchange	= get_BSTR(record.GetField(DDS::FIELD_ASK_EXCHANGE).AsString());
		quote->Currency		= get_BSTR("USD");
		quote->Exchange		= get_BSTR("");

		quote->BidPrice		= get_VALUE(record.GetField(DDS::FIELD_BID).AsDouble());
		quote->AskPrice		= get_VALUE(record.GetField(DDS::FIELD_ASK).AsDouble());	
		quote->LastPrice	= get_VALUE(record.GetField(DDS::FIELD_LAST).AsDouble());

		quote->Volume		= static_cast<long>(record.GetField(DDS::FIELD_VOLUME).AsLongLong());
		quote->BidSize		= record.GetField(DDS::FIELD_BID_SIZE).AsInt();
		quote->AskSize		= record.GetField(DDS::FIELD_ASK_SIZE).AsInt();
		quote->UpdateDateTime = record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
		quote->BidDateTime	= record.GetField(DDS::FIELD_BID_DATE).AsDateTime();
		quote->AskDateTime	= record.GetField(DDS::FIELD_ASK_DATE).AsDateTime();
		quote->LastDateTime	= record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();

		response_size++;
	};
	return response_size;
};
//---------------------------------------------------------//
long 
IvDataParser::parse_option_quote(const VS::CResponseBlock* response_block, 
								 TQ_container& response) {
	
	TQ_container::iterator result_iterator;
	long response_size = 0;

	VS::CResponseBlock::const_iterator it = response_block->Begin();
	VS::CResponseBlock::const_iterator itEnd = response_block->End();

	for (; it != itEnd; ++it) {
		const VS::CResponseRecord& record = *it;
		
		response.push_back(TQ_pair());
		result_iterator = response.end() - 1; 

		TQ_pair& tq_pair = *result_iterator;
		TickerWrapper& ticker = tq_pair.first;
		QuoteWrapper& quote = tq_pair.second;

		ticker->Type		= enOPT;
		ticker->Symbol		= get_BSTR(record.GetField(DDS::FIELD_OPTION_SYMBOL).AsString());
		ticker->Exchange	= get_BSTR("");
				
		quote->BidExchange	= get_BSTR(record.GetField(DDS::FIELD_BID_EXCHANGE).AsString());
		quote->AskExchange	= get_BSTR(record.GetField(DDS::FIELD_ASK_EXCHANGE).AsString());
		quote->Currency		= get_BSTR("USD");
		quote->Exchange		= get_BSTR("");

		quote->BidPrice		= get_VALUE(record.GetField(DDS::FIELD_BID).AsDouble());
		quote->AskPrice		= get_VALUE(record.GetField(DDS::FIELD_ASK).AsDouble());
		quote->LastPrice	= get_VALUE(record.GetField(DDS::FIELD_LAST).AsDouble());

		quote->Volume		= static_cast<long>(record.GetField(DDS::FIELD_VOLUME).AsLongLong());
		quote->BidSize		= record.GetField(DDS::FIELD_BID_SIZE).AsInt();
		quote->AskSize		= record.GetField(DDS::FIELD_ASK_SIZE).AsInt();
		quote->UpdateDateTime = record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
		quote->BidDateTime	= record.GetField(DDS::FIELD_BID_DATE).AsDateTime();
		quote->AskDateTime	= record.GetField(DDS::FIELD_ASK_DATE).AsDateTime();
		quote->LastDateTime	= record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
		
		response_size++;
	};
	return response_size;
};
//---------------------------------------------------------//
long 
IvDataParser::parse_future_quote(const VS::CResponseBlock* response_block, 
								 TQ_container& response) {

	long response_size = 0;
	TQ_container::iterator result_iterator;

	VS::CResponseBlock::const_iterator it = response_block->Begin();
	VS::CResponseBlock::const_iterator it_end = response_block->End();

	for (; it != it_end; ++it) {
	
		const VS::CResponseRecord& record = *it;

		response.push_back(TQ_pair());
		result_iterator = response.end() - 1; 

		TQ_pair& tq_pair = *result_iterator;
		TickerWrapper& ticker = tq_pair.first;
		QuoteWrapper& quote = tq_pair.second;

		ticker->Type		= enFUT;
		ticker->Symbol		= get_BSTR(record.GetField(DDS::FIELD_FUTURE_SYMBOL).AsString());		
		ticker->Exchange	= get_BSTR("");

		quote->BidExchange	= get_BSTR(record.GetField(DDS::FIELD_BID_EXCHANGE).AsString());
		quote->AskExchange	= get_BSTR(record.GetField(DDS::FIELD_ASK_EXCHANGE).AsString());
		quote->Currency		= get_BSTR("USD");
		quote->Exchange		= get_BSTR("");

		quote->BidPrice		= get_VALUE(record.GetField(DDS::FIELD_BID).AsDouble());
		quote->AskPrice		= get_VALUE(record.GetField(DDS::FIELD_ASK).AsDouble());
		quote->LastPrice	= get_VALUE(record.GetField(DDS::FIELD_LAST).AsDouble());

		quote->Volume		= static_cast<long>(record.GetField(DDS::FIELD_VOLUME).AsLongLong());
		quote->BidSize		= record.GetField(DDS::FIELD_BID_SIZE).AsInt();
		quote->AskSize		= record.GetField(DDS::FIELD_ASK_SIZE).AsInt();
		quote->UpdateDateTime = record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
		quote->BidDateTime	= record.GetField(DDS::FIELD_BID_DATE).AsDateTime();
		quote->AskDateTime	= record.GetField(DDS::FIELD_ASK_DATE).AsDateTime();
		quote->LastDateTime	= record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();

		response_size++;
	}
	return response_size;
};
//---------------------------------------------------------//
long 
IvDataParser::parse_future_option_quote(const VS::CResponseBlock* response_block, 
										TQ_container& response) {

	long response_size = 0;
	TQ_container::iterator result_iterator;

	VS::CResponseBlock::const_iterator it = response_block->Begin();
	VS::CResponseBlock::const_iterator it_end = response_block->End();

	for (; it != it_end; ++it) {

		const VS::CResponseRecord& record = *it;
		
		response.push_back(TQ_pair());
		result_iterator = response.end() - 1; 

		TQ_pair& tq_pair = *result_iterator;
		TickerWrapper& ticker = tq_pair.first;
		QuoteWrapper& quote = tq_pair.second;

		ticker->Type		= enFOP;
		ticker->Symbol		= get_BSTR(record.GetField(DDS::FIELD_FUTURE_OPTION_SYMBOL).AsString());
		ticker->Exchange	= get_BSTR("");

		quote->BidExchange	= get_BSTR(record.GetField(DDS::FIELD_BID_EXCHANGE).AsString());
		quote->AskExchange	= get_BSTR(record.GetField(DDS::FIELD_ASK_EXCHANGE).AsString());
		quote->Currency		= get_BSTR("USD");
		quote->Exchange		= get_BSTR("");

		quote->BidPrice		= get_VALUE(record.GetField(DDS::FIELD_BID).AsDouble());
		quote->AskPrice		= get_VALUE(record.GetField(DDS::FIELD_ASK).AsDouble());
		quote->LastPrice	= get_VALUE(record.GetField(DDS::FIELD_LAST).AsDouble());

		quote->Volume		= static_cast<long>(record.GetField(DDS::FIELD_VOLUME).AsLongLong());
		quote->BidSize		= record.GetField(DDS::FIELD_BID_SIZE).AsInt();
		quote->AskSize		= record.GetField(DDS::FIELD_ASK_SIZE).AsInt();
		quote->UpdateDateTime = record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
		quote->BidDateTime	= record.GetField(DDS::FIELD_BID_DATE).AsDateTime();
		quote->AskDateTime	= record.GetField(DDS::FIELD_ASK_DATE).AsDateTime();
		quote->LastDateTime	= record.GetField(DDS::FIELD_LAST_DATE).AsDateTime();
		
		response_size++;
	};
	return response_size;
};
//---------------------------------------------------------//
IvDataPacker::IvDataPacker() {
	this->fields.reserve(64);
};
//---------------------------------------------------------//
long
IvDataPacker::pack(DataContainer& data, BYTE*& message) {
	if (!data.is_empty()) {
		iv_tables tables;		
		fill_iv_tables(data, tables);		
		long message_size = assemble_message(tables, message);
		clear_tables(tables);
		return message_size;
	};
	return -1;
};
//---------------------------------------------------------//
long
IvDataPacker::clear_tables(IvDataPacker::iv_tables &tables) {
	iv_tables::iterator it = tables.begin();
	iv_tables::iterator it_end = tables.end();
	
	long rows_deleted = 0;
	for ( ; it != it_end; it++) {
		VS::TableRowList& table = it->second;
		
		VS::TableRowList::iterator row_it = table.begin();
		VS::TableRowList::iterator row_it_end = table.end();

		for (; row_it != row_it_end; row_it++) {
			VS::CTableRow::pointer row = *row_it;
			delete row;
			rows_deleted++;
		};

		table.clear();
	};

	return rows_deleted;
};
//---------------------------------------------------------//
long 
IvDataPacker::assemble_message(iv_tables& tables, BYTE*& msg) {
	
	VS::CMessageGroup messageGroup(VS::enCompressionNone);

	iv_tables::iterator it = tables.begin();
	iv_tables::iterator it_end = tables.end();
	
	for (;it != it_end; it++) {
	
		long current_type = it->first;
		VS::TableRowList& table = it->second;
		
		VS::FieldIDList filed_id_list;
		VS::IDList id_list;
		TableInitializer::get_analytics_table(filed_id_list, id_list);

		VS::CMessageTrails messageTrails(	current_type,
											VS::CMessageTrails::enRealtimeMessage,
											filed_id_list, 
											table, 
											id_list);

		messageTrails.SetProtocolVersion(1);

		VS::CMessage::pointer message = VS::CMessageFactory::Instance().CreateMessage(messageTrails);
		if (message)
			messageGroup.AddMessage(message);
	};
	unsigned long message_size = 0;
	msg = messageGroup.AssembleMessage(message_size);
	return message_size;
};
//---------------------------------------------------------//
long
IvDataPacker::fill_iv_tables(DataContainer& data, iv_tables& tables) {

	DataContainer::my_iterator it = data.get_begin();
	DataContainer::my_iterator it_end = data.get_end();

	DataContainer::my_pair& current_pair = DataContainer::my_pair(0,0);

	long current_table_id = 0;
	LPSAFEARRAY current_array = 0;

	for (;it != it_end; it++) {
		current_pair = *it;

		current_array = current_pair.second;
		current_table_id = current_pair.first;

		VS::TableRowList& current_table = tables[current_table_id];

		pack_array(current_table_id, current_array, current_table);
	};
	return static_cast<long>(tables.size());
};
//---------------------------------------------------------//
long
IvDataPacker::pack_array(long data_type, 
						 LPSAFEARRAY &arr, 
						 VS::TableRowList& table) {
	if (data_type == IvRmTables::IVRM_ANALYTICS) {
		return pack_analytics(arr, table);
	};
	return -1;
};
//---------------------------------------------------------//
long 
IvDataPacker::pack_analytics(LPSAFEARRAY& arr, 
							 VS::TableRowList& table) {
								 
	IRisksFullInfo* anx_array = 0;
	long array_size = arr->rgsabound[0].cElements;					

	SafeArrayAccessData(arr, (void**)&anx_array);
		
	if (anx_array) {

		long table_size = static_cast<long>(table.size());

		for (int i = 0; i < array_size; i++) {
			pack_analytical_atom(anx_array[i], fields);			
			table.push_back(new VS::CTableRow(table_size + i, fields));
			fields.clear();
		};
	};

	SafeArrayUnaccessData(arr);

	return -1;
};
//---------------------------------------------------------//
long 
IvDataPacker::pack_analytical_atom(	IRisksFullInfo& anx_atom, 
									VS::FieldDataList& fields) {

	IRisksFullInfo& analytics = anx_atom;
	IRisks& anx = analytics.Risks;

	fields.push_back(VS::CFieldData(_bstr_t(analytics.Ticker.Symbol)));
	fields.push_back(VS::CFieldData(_bstr_t(analytics.BaseTicker.Symbol)));
	fields.push_back(VS::CFieldData(static_cast<int>(analytics.Ticker.Type))); 
	fields.push_back(VS::CFieldData(static_cast<int>(analytics.BaseTicker.Type)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.IVola)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.Delta)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.Vega)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.Gamma)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.Theta)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.Rho)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.TheoPrice)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.ContractPrice)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.BaseContractPrice)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.Volga)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.DeltaVega)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.DeltaTheta)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.GammaVega)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.GammaTheta)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.TheoVola)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.BidPrice)));
	fields.push_back(VS::CFieldData(VS::CDateTimeType(anx.BidDate)));
	fields.push_back(VS::CFieldData("*"));
	fields.push_back(VS::CFieldData(static_cast<long>(anx.BidSize)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.AskPrice)));
	fields.push_back(VS::CFieldData(VS::CDateTimeType(anx.AskDate)));
	fields.push_back(VS::CFieldData("*"));
	fields.push_back(VS::CFieldData(static_cast<long>(anx.AskSize)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.LastPrice)));
	fields.push_back(VS::CFieldData(VS::CDateTimeType(anx.LastDate)));
	fields.push_back(VS::CFieldData(static_cast<long>(anx.Volume)));
	fields.push_back(VS::CFieldData(VS::CDateTimeType(anx.UpdateDate)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.TheoPriceBid)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.TheoPriceAsk)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.ContractPriceBid)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.ContractPriceAsk)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.BaseContractPriceBid)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.BaseContractPriceAsk)));
	fields.push_back(VS::CFieldData(static_cast<float>(anx.IntrinsicValue)));

	return static_cast<long>(fields.size());
};
//---------------------------------------------------------//
long
IvDataTransmitter::transmit(DataContainer& data) {

	CAutoLock l(lock_);

	BYTE* message = 0;
	long message_size = 0;
	
	TickCounter counter;
	
	try {
		
		counter.start();
		
		message_size = packer->pack(data, message);
		
		LOG4CPLUS_INFO(CServer::server_logger(), 
		"packing data complete in [" << counter.stop() << "] ticks.");
	}
	catch (...) {
		LOG4CPLUS_ERROR(CServer::server_logger(),
		"Unknown exception occured while packing data to transmit.");
		return 0;
	};
	
	CORBA::Any result;
	DDS::IVData msgSequence(message_size, message_size, message, 1);
	result <<= msgSequence;

	try {
		
		counter.start();
		
		data_manager->InsertRows(result);
		
		LOG4CPLUS_INFO(CServer::server_logger(), 
		"data inserted in [" << counter.stop() << "] ticks.");
	}
	catch(CORBA::SystemException& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"corba::SystemException: " << ToString(err));
	}
	catch(CORBA::Exception& err) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"corba::Exception: " << ToString(err));
	}
	catch(omniORB::fatalException& err) {		
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"omniORB::FatalException: " << ToString(err));
	}
	catch(...) {
		LOG4CPLUS_ERROR(CServer::server_logger(), 
		"Unknown exception occured while transmitting data to data broker.");
	};

	return message_size;
};
//---------------------------------------------------------//
void
IvDataTransmitter::initialize_by(IniReader::Section& settings) {
	settings.get_value("LOGIN", login_, "server");
	settings.get_value("PASSWORD", password_, "server");
	settings.get_value("RECEIVER", receiver_, "IVDataBroker");
	settings.get_value("SESSION_ID", session_id_, "filter_session");
};
//---------------------------------------------------------//
#define ADD_WRITER(__Id, __Type)		\
	VS::CStreamWriterFactory::Instance().AddField(__Id, VS::CStreamFactory::__Type)

#define PUSH_FILED(__list, __Id)	\
	__list.push_back(__Id)

void
TableInitializer::intialize_writers() {
	ADD_WRITER(IVRMFields::FIELD_SYMBOL,					STREAM_64BYTE_STRING_ID);
	ADD_WRITER(IVRMFields::FIELD_BASE_SYMBOL,				STREAM_64BYTE_STRING_ID);
	ADD_WRITER(IVRMFields::FIELD_SYMBOL_TYPE,				STREAM_INT_ID);
	ADD_WRITER(IVRMFields::FIELD_BASE_SYMBOL_TYPE,			STREAM_INT_ID);
	ADD_WRITER(IVRMFields::FIELD_IV,						STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_DELTA,						STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_VEGA,						STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_GAMMA,						STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_THETA,						STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_RHO,						STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_THEO_PRICE,				STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_CONTRACT_PRICE,			STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_BASECONTRACT_PRICE,		STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_VOLGA,						STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_DELTA_VEGA,				STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_DELTA_THETA,				STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_GAMMA_VEGA,				STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_GAMMA_THETA,				STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_THEO_VOLA,					STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_BID,						STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_BID_DATE,					STREAM_DATETIME_ID);
	ADD_WRITER(IVRMFields::FIELD_BID_EXCHANGE,				STREAM_EXCHANGE_ID);
	ADD_WRITER(IVRMFields::FIELD_BID_SIZE,					STREAM_INT_ID);
	ADD_WRITER(IVRMFields::FIELD_ASK,						STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_ASK_DATE,					STREAM_DATETIME_ID);
	ADD_WRITER(IVRMFields::FIELD_ASK_EXCHANGE,				STREAM_EXCHANGE_ID);
	ADD_WRITER(IVRMFields::FIELD_ASK_SIZE,					STREAM_INT_ID);
	ADD_WRITER(IVRMFields::FIELD_LAST,						STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_LAST_DATE,					STREAM_DATETIME_ID);
	ADD_WRITER(IVRMFields::FIELD_VOLUME,					STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_UPDATE_DATE,				STREAM_DATETIME_ID);
	ADD_WRITER(IVRMFields::FIELD_CONTRACT_PRICE_BID,		STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_CONTRACT_PRICE_ASK,		STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_BASECONTRACT_PRICE_BID,	STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_BASECONTRACT_PRICE_ASK,	STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_THEO_PRICE_BID,			STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_THEO_PRICE_ASK,			STREAM_FLOAT_ID);
	ADD_WRITER(IVRMFields::FIELD_INTRINSIC_VALUE,			STREAM_FLOAT_ID);
};
//---------------------------------------------------------//
void
TableInitializer::get_analytics_table(VS::FieldIDList &fieldIDList, 
									  VS::IDList &idList) {
	
	fieldIDList.clear();
	idList.clear();
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_SYMBOL);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_BASE_SYMBOL);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_SYMBOL_TYPE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_BASE_SYMBOL_TYPE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_IV);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_DELTA);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_VEGA);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_GAMMA);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_THETA);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_RHO);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_THEO_PRICE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_CONTRACT_PRICE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_BASECONTRACT_PRICE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_VOLGA);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_DELTA_VEGA);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_DELTA_THETA);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_GAMMA_VEGA);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_GAMMA_THETA);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_THEO_VOLA);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_BID);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_BID_DATE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_BID_EXCHANGE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_BID_SIZE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_ASK);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_ASK_DATE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_ASK_EXCHANGE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_ASK_SIZE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_LAST);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_LAST_DATE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_VOLUME);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_UPDATE_DATE);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_THEO_PRICE_BID);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_THEO_PRICE_ASK);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_CONTRACT_PRICE_BID);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_CONTRACT_PRICE_ASK);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_BASECONTRACT_PRICE_BID);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_BASECONTRACT_PRICE_ASK);
	PUSH_FILED(fieldIDList,IVRMFields::FIELD_INTRINSIC_VALUE);

	for (long i = 0; i < static_cast<long>(fieldIDList.size()); ++i) {
		idList.push_back(i);
	};
};
//---------------------------------------------------------//
IvRmFilter::IvRmFilter(IEtsMainPtr core, 
					   DataPacker *packer,
					   const std::string& object_name) {
	this->core = core;
	this->packer = packer;
	this->object_name = object_name;
	this->quotes_table.reserve(50000);
};
//---------------------------------------------------------//
CORBA::Any*
IvRmFilter::apply_filter_impl(const CORBA::Any& data) {
													  
	CAutoLock alock(this->filter_lock);

	CORBA::Any* result = new CORBA::Any(); 
	DDS::IVData* ivData = NULL;

	if (data >>= ivData) {
		
		TickCounter counter;
		counter.start();
		
		IvDataParser parser;
		long quotes_parsed = parser.parse(ivData->get_buffer(), ivData->length(), quotes_table);
		
		std::ostringstream info_line;
		info_line << "data parsed in [" << counter.stop() << "] and ";
		
		if (quotes_parsed > 0) {
			
			counter.start();
			
			TQ_container::iterator it = quotes_table.begin();
			TQ_container::iterator it_end = quotes_table.end();

			for ( ; it != it_end; it++) {
				TQ_pair& pair = *it;			
				core->SetQuote(&(pair.first)(), &(pair.second)());
			};
			
			info_line << "quotes updated in [" << counter.stop() << "] ticks.\n";
			LOG4CPLUS_INFO(CServer::server_logger(), info_line.str());

			//LPSAFEARRAY analytics = core->CalculateUpdatedContracts();
			//DataContainer data;
			//data.add_data(35, analytics);

			//BYTE* message = 0;
			//long message_size = packer->pack(data, message);

			//data.clear();

			//DDS::IVData msgSequence(message_size, message_size, message, 1);
			//*result <<= msgSequence;
		};
		quotes_table.clear();
			
	};

	return result;
};
//---------------------------------------------------------//
void
IvRmFilter::get_object_name(std::string& name) {
	name = object_name;
};
//---------------------------------------------------------//
IvRmFilter::~IvRmFilter() {
	this->core = NULL;
};
//---------------------------------------------------------//
CORBA::Any*
IvRmFilter::ApplyFilter(const CORBA::Any& anyData) {
	return this->apply_filter_impl(anyData);
};
//---------------------------------------------------------//
//---------------------------------------------------------//
//---------------------------------------------------------//
//---------------------------------------------------------//


