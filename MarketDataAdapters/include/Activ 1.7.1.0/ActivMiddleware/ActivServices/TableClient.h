/**
 *  @file	TableClient.h
 *
 *	@brief	Header file for the table client class.
 *
 *	$Log: $
 */

#if (!defined ACTIV_SERVICES_TABLE_CLIENT_H)
#define ACTIV_SERVICES_TABLE_CLIENT_H

#include "ActivMiddleware/ActivServices/External.h"
#include "ActivMiddleware/ActivServices/TableResponses.h"

#include "ActivMiddleware/ActivDatabase/ITable.h"
#include "ActivMiddleware/ActivDatabase/Key.h"
#include "ActivMiddleware/ActivDatabase/Record.h"
#include "ActivMiddleware/ActivBase/ThreadSpecificData.h"


#include <memory>

/**
 *	@brief	List of table client states.
 */
#define ACTIV_TABLE_CLIENT_STATE_LIST(d)	\
	d(STATE_INITIALIZED)					\
	d(STATE_W4_CONNECT)						\
	d(STATE_OPEN)

namespace Activ
{

class OpenTableResponse;
class TableMessage;

/**
 *	@brief	Remote table class.
 */
class TableClient : public Component, public Database::ITable, public TableResponses
{
public:
	/**
	 *	@brief	States.
	 */
	enum State
	{
		ACTIV_TABLE_CLIENT_STATE_LIST(ACTIV_DECLARE_VALUE_WITH_COMMA)
		NUM_STATES
	};

	/**
	 *	@brief	Constructor.
	 *
	 *	@param	application the application creating the remote table.
	 *	@param	managedEndPoint endpoint to attach to.
	 *	@param	portName name of the port, local to the endpoint.
	 *	@param	pHeap default heap to use for sending messages. Default implies the system heap.
	 *	@param	componentId the component id.
	 */
	ACTIV_SERVICES_API TableClient(Application &application, ManagedEndPoint &managedEndPoint, const std::string &portName = Port::anonymousName, IHeap * const pHeap = 0, const std::string &componentId = defaultComponentId);

	/**
	 *	@brief	Destructor.
	 */
	ACTIV_SERVICES_API ~TableClient();

	/**
	 *	@brief	Open a connection to a table service.
	 *
	 *	The \a serviceHandle object must have the m_url member filled with the url of the service you wish to open.
	 *	The m_serviceInstance.m_serviceId member must contain the id of the service you wish to open.
	 *
	 *	@param	serviceHandle reference to a ServiceHandle object.
	 *	@param	timeout how long to wait for the connection to be established, in ms.
	 *
	 *	@retval	STATUS_CODE_SUCCESS if synchronous, service is open. Asynchronous, connection initiated.
	 *	@retval	STATUS_CODE_WRONG_STATE.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode OpenService(ServiceHandle &serviceHandle, const TimeoutPeriod timeout = defaultTimeout);

	/**
	 *	@brief	Close the connection to the table service.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode CloseService();

	/**
	 *	@brief	Add a split table client to the chain.
	 *
	 *	@param	newSplitTableClient the new split table client to add to the chain.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	STATUS_CODE_NOT_OPEN
	 *	@retval	STATUS_CODE_INVALID_TABLE
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode AddSplitTableClient(TableClient &newSplitTableClient);

	ACTIV_SERVICES_API virtual void CreateRecordFile();

	ACTIV_SERVICES_API virtual StatusCode OpenRecordFile();

	ACTIV_SERVICES_API virtual StatusCode CloseRecordFile();

	ACTIV_SERVICES_API virtual StatusCode Convert();

	ACTIV_SERVICES_API virtual StatusCode Save(const std::string &directory);

	ACTIV_SERVICES_API virtual StatusCode CopyFiles(const std::string &sourceDirectory, const std::string &targetDirectory) const;

	ACTIV_SERVICES_API virtual void CreateIndexes(std::vector<Database::IndexSpecification> &indexSpecificationList);

	ACTIV_SERVICES_API virtual void CreateTemporaryIndex(Database::IndexSpecification &indexSpecification);

	ACTIV_SERVICES_API virtual ITable *Clone(const std::string &directory = std::string(), const bool createMutex = false, const bool copyRecords = true, size_t recordsPerRequest = 20) const;

	ACTIV_SERVICES_API virtual StatusCode Clear();

	ACTIV_SERVICES_API virtual StatusCode Copy(const Database::ITable *pSourceTable, const bool clearTargetTable, size_t recordsPerRequest = 20);

	ACTIV_SERVICES_API virtual StatusCode SerializeSpecification(MessageBuilder &messageBuilder) const;
	ACTIV_SERVICES_API virtual StatusCode Serialize(MessageBuilder &messageBuilder, const Database::KeyList &keyList) const;
	ACTIV_SERVICES_API virtual StatusCode Serialize(MessageBuilder &messageBuilder, const Database::RecordList &recordList) const;
	ACTIV_SERVICES_API virtual StatusCode Serialize(MessageBuilder &messageBuilder, const Database::DataId &recordId, const Database::RecordList &recordList) const;
	ACTIV_SERVICES_API virtual StatusCode Serialize(MessageBuilder &messageBuilder, const std::vector<StatusCode> &statusCodeList, const Database::RecordList &recordList) const;

	ACTIV_SERVICES_API virtual StatusCode Deserialize(MessageValidator &messageValidator, Database::KeyList &keyList) const;
	ACTIV_SERVICES_API virtual StatusCode Deserialize(MessageValidator &messageValidator, Database::RecordList &recordList) const;
	ACTIV_SERVICES_API virtual StatusCode Deserialize(MessageValidator &messageValidator, Database::DataId &recordId, Database::RecordList &recordList) const;
	ACTIV_SERVICES_API virtual StatusCode Deserialize(MessageValidator &messageValidator, Database::DataId &recordId, size_t &maxResponseRecords) const;
	ACTIV_SERVICES_API virtual StatusCode Deserialize(MessageValidator &messageValidator, std::vector<StatusCode> &statusCodeList, Database::RecordList &recordList) const;

	ACTIV_SERVICES_API virtual StatusCode ResetRecord(Database::Record &record) const;

	ACTIV_SERVICES_API virtual StatusCode Add(Database::Record &record);
	ACTIV_SERVICES_API virtual StatusCode Add(Database::Record &record, Database::Record &originalRecord);

	ACTIV_SERVICES_API virtual StatusCode Delete(const Database::Key &key);
	ACTIV_SERVICES_API virtual StatusCode Delete(const Database::Key &key, Database::Record &record);

	ACTIV_SERVICES_API virtual StatusCode GetEqual(const Database::Key &key, Database::Record &record) const;
	ACTIV_SERVICES_API virtual StatusCode GetEqual(const Database::KeyList &keyList, std::vector<StatusCode> &statusCodeList, Database::RecordList &recordList) const;

	ACTIV_SERVICES_API virtual StatusCode GetFirst(Database::Key &key, Database::Record &record) const;
	ACTIV_SERVICES_API virtual StatusCode GetFirst(Database::Key &key, Database::RecordList &recordList, const size_t maxResponseRecords = 0) const;

	ACTIV_SERVICES_API virtual StatusCode GetLast(Database::Key &key, Database::Record &record) const;
	ACTIV_SERVICES_API virtual StatusCode GetLast(Database::Key &key, Database::RecordList &recordList, const size_t maxResponseRecords = 0) const;

	ACTIV_SERVICES_API virtual StatusCode GetNext(Database::Key &key, Database::Record &record) const;
	ACTIV_SERVICES_API virtual StatusCode GetNext(Database::Key &key, Database::RecordList &recordList, const size_t maxResponseRecords = 0) const;

	ACTIV_SERVICES_API virtual StatusCode GetPrevious(Database::Key &key, Database::Record &record) const;
	ACTIV_SERVICES_API virtual StatusCode GetPrevious(Database::Key &key, Database::RecordList &recordList, const size_t maxResponseRecords = 0) const;

	ACTIV_SERVICES_API virtual StatusCode GetFirstPartial(Database::Key &key, Database::Record &record, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE) const;
	ACTIV_SERVICES_API virtual StatusCode GetFirstPartial(Database::Key &key, Database::RecordList &recordList, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE, const size_t maxResponseRecords = 0) const;

	ACTIV_SERVICES_API virtual StatusCode GetLastPartial(Database::Key &key, Database::Record &record, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE) const;
	ACTIV_SERVICES_API virtual StatusCode GetLastPartial(Database::Key &key, Database::RecordList &recordList, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE, const size_t maxResponseRecords = 0) const;

	ACTIV_SERVICES_API virtual StatusCode GetNextPartial(Database::Key &key, Database::Record &record, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE) const;
	ACTIV_SERVICES_API virtual StatusCode GetNextPartial(Database::Key &key, Database::RecordList &recordList, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE, const size_t maxResponseRecords = 0) const;

	ACTIV_SERVICES_API virtual StatusCode GetPreviousPartial(Database::Key &key, Database::Record &record, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE) const;
	ACTIV_SERVICES_API virtual StatusCode GetPreviousPartial(Database::Key &key, Database::RecordList &recordList, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE, const size_t maxResponseRecords = 0) const;

	ACTIV_SERVICES_API virtual StatusCode StepFirst(Database::DataId &recordId, Database::Record &record) const;
	ACTIV_SERVICES_API virtual StatusCode StepFirst(Database::DataId &recordId, Database::RecordList &recordList, const size_t maxResponseRecords = 0) const;

	ACTIV_SERVICES_API virtual StatusCode StepNext(Database::DataId &recordId, Database::Record &record) const;
	ACTIV_SERVICES_API virtual StatusCode StepNext(Database::DataId &recordId, Database::RecordList &recordList, const size_t maxResponseRecords = 0) const;

	ACTIV_SERVICES_API virtual StatusCode SetIndexFields(Database::Record &record, const Database::IndexSpecification::Number indexNo, const ScatterBufferHelper &scatterBufferHelper) const;

	ACTIV_SERVICES_API virtual void CheckIntegrity() const;

	ACTIV_SERVICES_API virtual Database::TableSpecification GetTableSpecification() const;

	ACTIV_SERVICES_API virtual const Database::FieldList &GetFieldList() const;

	ACTIV_SERVICES_API virtual Database::FieldSpecificationList GetFieldSpecificationList() const;

	ACTIV_SERVICES_API virtual bool GetFieldSpecificationList(const Database::FieldSpecification &fieldSpecification, Database::FieldSpecificationList &matchingFieldSpecificationList) const;

	ACTIV_SERVICES_API virtual StatusCode GetFieldSpecification(const Database::FieldSpecification::Id fieldId, Database::FieldSpecification &fieldSpecification) const;

	ACTIV_SERVICES_API virtual void GetFirstFieldSpecification(Database::FieldSpecification &fieldSpecification) const;

	ACTIV_SERVICES_API virtual StatusCode GetNextFieldSpecification(Database::FieldSpecification &fieldSpecification) const;

	ACTIV_SERVICES_API virtual std::vector<Database::IndexSpecification> GetIndexSpecificationList() const;

	ACTIV_SERVICES_API virtual bool GetIndexSpecificationList(const Database::IndexSpecification &indexSpecification, Database::IndexSpecificationList &matchingIndexSpecificationList) const;

	ACTIV_SERVICES_API virtual StatusCode GetIndexSpecification(const Database::IndexSpecification::Number indexNo, Database::IndexSpecification &indexSpecification) const;

	ACTIV_SERVICES_API virtual std::vector<Database::FieldSpecification::Id> GetFieldIdList() const;

	ACTIV_SERVICES_API virtual void GetFirstFieldId(Database::FieldSpecification::Id &fieldId) const;

	ACTIV_SERVICES_API virtual StatusCode GetNextFieldId(Database::FieldSpecification::Id &fieldId) const;

	ACTIV_SERVICES_API virtual StatusCode GetType(const Database::FieldSpecification::Id fieldId, Database::FieldSpecification::Type &type) const;

	ACTIV_SERVICES_API virtual std::string GetName() const;

	ACTIV_SERVICES_API virtual std::string GetDirectory() const;

	ACTIV_SERVICES_API virtual std::string GetBasicFileName() const;

	ACTIV_SERVICES_API virtual StatusCode GetMaxRecords(size_t &maxRecords) const;

	ACTIV_SERVICES_API virtual StatusCode GetCurrentRecords(size_t &nRecords) const;

	ACTIV_SERVICES_API virtual size_t GetRecordLength() const;

	ACTIV_SERVICES_API virtual size_t GetNumberOfIndexes() const;

	ACTIV_SERVICES_API virtual Database::IndexSpecification::Number GetPrimaryIndexNumber() const;

	ACTIV_SERVICES_API virtual StatusCode GetIndexPointer(const Database::IndexSpecification::Number indexNo, Database::IIndex *&pIndex) const;

	ACTIV_SERVICES_API virtual bool IsRecordFileOpen() const;

	ACTIV_SERVICES_API virtual bool IsTemporary() const;

	ACTIV_SERVICES_API virtual bool IsAdd(const Database::Record &record, const Database::Record &originalRecord) const;

	ACTIV_SERVICES_API virtual bool IsUpdate(const Database::Record &record, const Database::Record &originalRecord) const;

	ACTIV_SERVICES_API virtual bool IsFound(const Database::FieldSpecification::Id fieldId) const;

	ACTIV_SERVICES_API virtual bool IsManaged() const;

	/**
	 *	@brief	Post an asynchronous get equal request.
	 *
	 *	If the request is sent successfully, OnGetEqualResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *
	 *	@retval	STATUS_CODE_SUCCESS
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetEqualRequest(const RequestId &requestId, const Database::Key &key) const;

	/**
	 *	@brief	Post an asynchronous get multiple equal request.
	 *
	 *	@param	keyList list of key information that will be searched for.
	 *
	 *	@retval	STATUS_CODE_SUCCESS
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetMultipleEqualRequest(const RequestId &requestId, const Database::KeyList &keyList) const;

	/**
	 *	@brief	Post an asynchronous get first request.
	 *
	 *	If the request is sent successfully, OnGetFirstResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetFirstRequest(const RequestId &requestId, const Database::Key &key) const;

	/**
	 *	@brief	Post an asynchronous get last request.
	 *
	 *	If the request is sent successfully, OnGetLastResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetLastRequest(const RequestId &requestId, const Database::Key &key) const;

	/**
	 *	@brief	Post an asynchronous get next request.
	 *
	 *	If the request is sent successfully, OnGetNextResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetNextRequest(const RequestId &requestId, const Database::Key &key) const;

	/**
	 *	@brief	Post an asynchronous get previous request.
	 *
	 *	If the request is sent successfully, OnGetPreviousResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetPreviousRequest(const RequestId &requestId, const Database::Key &key) const;

	/**
	 *	@brief	Post an asynchronous get first partial request.
	 *
	 *	If the request is sent successfully, OnGetFirstPartialResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	lastKeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetFirstPartialRequest(const RequestId &requestId, const Database::Key &key, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE) const;

	/**
	 *	@brief	Post an asynchronous get last partial request.
	 *
	 *	If the request is sent successfully, OnGetLastPartialResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	lastKeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetLastPartialRequest(const RequestId &requestId, const Database::Key &key, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE) const;

	/**
	 *	@brief	Post an asynchronous get next partial request.
	 *
	 *	If the request is sent successfully, OnGetNextPartialResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	lastKeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetNextPartialRequest(const RequestId &requestId, const Database::Key &key, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE) const;

	/**
	 *	@brief	Post an asynchronous get previous partial request.
	 *
	 *	If the request is sent successfully, OnGetPreviousPartialResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	lastKeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetPreviousPartialRequest(const RequestId &requestId, const Database::Key &key, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE) const;

	/**
	 *	@brief	Post an asynchronous get multiple first request.
	 *
	 *	If the request is sent successfully, OnGetMultipleFirstResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	maxResponseRecords the maximum number of records to include in the response. Default of zero implies all matching records will be returned.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetMultipleFirstRequest(const RequestId &requestId, const Database::Key &key, const size_t maxResponseRecords = 0) const;

	/**
	 *	@brief	Post an asynchronous get multiple last request.
	 *
	 *	If the request is sent successfully, OnGetMultipleLastResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	maxResponseRecords the maximum number of records to include in the response. Default of zero implies all matching records will be returned.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetMultipleLastRequest(const RequestId &requestId, const Database::Key &key, const size_t maxResponseRecords = 0) const;

	/**
	 *	@brief	Post an asynchronous get multiple next request.
	 *
	 *	If the request is sent successfully, OnGetMultipleNextResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	maxResponseRecords the maximum number of records to include in the response. Default of zero implies all matching records will be returned.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetMultipleNextRequest(const RequestId &requestId, const Database::Key &key, const size_t maxResponseRecords = 0) const;

	/**
	 *	@brief	Post an asynchronous get multiple previous request.
	 *
	 *	If the request is sent successfully, OnGetMultiplePreviousResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	maxResponseRecords the maximum number of records to include in the response. Default of zero implies all matching records will be returned.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetMultiplePreviousRequest(const RequestId &requestId, const Database::Key &key, const size_t maxResponseRecords = 0) const;

	/**
	 *	@brief	Post an asynchronous get multiple first partial request.
	 *
	 *	If the request is sent successfully, OnGetMultipleFirstPartialResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	lastDatabase::KeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *	@param	maxResponseRecords the maximum number of records to include in the response. Default of zero implies all matching records will be returned.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetMultipleFirstPartialRequest(const RequestId &requestId, const Database::Key &key, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE, const size_t maxResponseRecords = 0) const;

	/**
	 *	@brief	Post an asynchronous get multiple last partial request.
	 *
	 *	If the request is sent successfully, OnGetMultipleLastPartialResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	lastKeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *	@param	maxResponseRecords the maximum number of records to include in the response. Default of zero implies all matching records will be returned.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetMultipleLastPartialRequest(const RequestId &requestId, const Database::Key &key, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE, const size_t maxResponseRecords = 0) const;

	/**
	 *	@brief	Post an asynchronous get multiple next partial request.
	 *
	 *	If the request is sent successfully, OnGetMultipleNextPartialResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	lastKeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *	@param	maxResponseRecords the maximum number of records to include in the response. Default of zero implies all matching records will be returned.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetMultipleNextPartialRequest(const RequestId &requestId, const Database::Key &key, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE, const size_t maxResponseRecords = 0) const;

	/**
	 *	@brief	Post an asynchronous get multiple previous partial request.
	 *
	 *	If the request is sent successfully, OnGetMultiplePreviousPartialResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	lastKeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *	@param	maxResponseRecords the maximum number of records to include in the response. Default of zero implies all matching records will be returned.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostGetMultiplePreviousPartialRequest(const RequestId &requestId, const Database::Key &key, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength = Database::FIELD_COMPARE_LENGTH_WHOLE, const size_t maxResponseRecords = 0) const;

	/**
	 *	@brief	Post an asynchronous step first request.
	 *
	 *	If the request is sent successfully, OnStepFirstResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostStepFirstRequest(const RequestId &requestId) const;

	/**
	 *	@brief	Post an asynchronous step next request.
	 *
	 *	If the request is sent successfully, OnStepNextResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	recordId the id of the record to continue the step search from.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostStepNextRequest(const RequestId &requestId, const Database::DataId &recordId) const;

	/**
	 *	@brief	Post an asynchronous step multiple first request.
	 *
	 *	If the request is sent successfully, OnStepMultipleFirstResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	maxResponseDatabase the maximum number of records to include in the response. Default of zero implies all matching records will be returned.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostStepMultipleFirstRequest(const RequestId &requestId, const size_t maxResponseRecords = 0) const;

	/**
	 *	@brief	Post an asynchronous step multiple next request.
	 *
	 *	If the request is sent successfully, OnStepMultipleNextResponse() will be invoked with the response.
	 *
	 *	@param	requestId request id for the outgoing request.
	 *	@param	recordId the id of the record to continue the search from.
	 *	@param	maxResponseRecords the maximum number of records to include in the response. Default of zero implies all matching records will be returned.
	 *
	 *	@retval	STATUS_CODE_SUCCESS the request was sent successfully.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode PostStepMultipleNextRequest(const RequestId &requestId, const Database::DataId &recordId, const size_t maxResponseRecords = 0) const;

	/**
	 *	@brief	Deserialize a get response.
	 *
	 *	@param	response the response message.
	 *	@param	key reference to a Database::Key to receive the returned Database::Key.
	 *	@param	record reference to a Database::Record to receive the returned Database::Record.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	STATUS_CODE_NOT_FOUND.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode DeserializeGetResponse(const HeapMessage &response, Database::Key &key, Database::Record &record) const;

	/**
	 *	@brief	Deserialize a get multiple equal response.
	 *
	 *	@param	response the response message.
	 *	@param	statusCodeList the status code associated with each look up is stored in this parameter.
	 *	@param	recordList the record matching each supplied key information is stored in this parameter, or a blank record if no match is found.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	STATUS_CODE_NOT_FOUND.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode DeserializeGetMultipleEqualResponse(const HeapMessage &response, std::vector<StatusCode> &statusCodeList, Database::RecordList &recordList) const;

	/**
	 *	@brief	Deserialize a get multiple response.
	 *
	 *	@param	response the response message.
	 *	@param	key reference to a Database::Key to receive the returned Database::Key.
	 *	@param	recordList all located records are stored in this parameter.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	STATUS_CODE_NOT_FOUND.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode DeserializeGetMultipleResponse(const HeapMessage &response, Database::Key &key, Database::RecordList &recordList) const;

	/**
	 *	@brief	Deserialize a step response.
	 *
	 *	@param	response the response message.
	 *	@param	recordId reference to a Database::DataId to received the returned Database::DataId.
	 *	@param	record reference to a Database::Record to receive the returned Database::Record.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	STATUS_CODE_NOT_FOUND.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode DeserializeStepResponse(const HeapMessage &response, Database::DataId &recordId, Database::Record &record) const;

	/**
	 *	@brief	Deserialize a step multiple response.
	 *
	 *	@param	response the response message.
	 *	@param	recordId reference to a Database::DataId to received the returned Database::DataId.
	 *	@param	recordList all located records are stored in this parameter.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	STATUS_CODE_NOT_FOUND.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode DeserializeStepMultipleResponse(const HeapMessage &response, Database::DataId &recordId, Database::RecordList &recordList) const;

	/**
	 *	@brief	Process response.
	 *
	 *	@param	responseHeapMessage the response heap message.
	 *	@param	tableResponses the table responses.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	...
	 */
	ACTIV_SERVICES_API StatusCode ProcessResponse(HeapMessage &responseHeapMessage, TableResponses &tableResponses);

#if defined (_DEBUG)
	ACTIV_SERVICES_API virtual void DisplayFieldInformation(std::ostream &os = std::cout) const;

	ACTIV_SERVICES_API virtual void DisplayKeyFieldInformation(const Database::IndexSpecification::Number indexNo, std::ostream &os = std::cout) const;
#endif

	/**
	 *	@brief	Get the state of the connection to the service.
	 */
	ACTIV_SERVICES_API State GetState() const;

	/**
	 *	@brief	Return the state as a string.
	 *
	 *	@return	String representation of state.
	 */
	ACTIV_SERVICES_API static std::string StateToString(const State state);

	/**
	 *	@brief	Is split.
	 *
	 *	@return	whether the table client is split.
	 */
	bool IsSplit() const;

protected:
	ACTIV_SERVICES_API virtual StatusCode OnConnect(HeapMessage &connectMessage);
	ACTIV_SERVICES_API virtual StatusCode OnBreak(HeapMessage &breakMessage);
	ACTIV_SERVICES_API virtual StatusCode OnResponse(HeapMessage &response);

	/**
	 *	@brief	Process connection to remote table coming up.
	 *
	 *	@param	openTableResponse response from open request to service.
	 */
	ACTIV_SERVICES_API StatusCode ProcessConnect(const OpenTableResponse &openTableResponse);

	/**
	 *	@brief	Is matching table client.
	 *
	 *	@param	key the search key.
	 *
	 *	@return	true if the table client would normally contain the key.
	 */
	ACTIV_SERVICES_API virtual bool IsMatchingTableClient(const Database::Key &key) const;

private:
	/**
	 *	@brief	Thread info class.
	 */
	class ThreadInfo
	{
	public:
		byte_t		m_messageBuffer[32768];	///< The message buffer.
	};

	typedef uint8_t		SplitIndex;			///< Type for index of a table within a split table client chain.

	/**
	 *	@brief	Build and send a get request for the remote table.
	 *
	 *	@param	type the type of the request.
	 *	@param	key key information which will be searched for.
	 *	@param	record matching record information will be stored in this parameter.
	 *
	 *	@retval	STATUS_CODE_SUCCESS
	 *	@retval	STATUS_CODE_INVALID_FIELD
	 *	@retval	STATUS_CODE_INVALID_INDEX
	 *	@retval	STATUS_CODE_INVALID_KEY
	 *	@retval	STATUS_CODE_INVALID_PARAMETER
	 *	@retval	STATUS_CODE_HEAP_EMPTY
	 *	@retval	STATUS_CODE_NOT_FOUND
	 *	@retval	STATUS_CODE_OUT_OF_RANGE
	 */
	StatusCode Get(const MessageType type, Database::Key &key, Database::Record &record) const;

	/**
	 *	@brief	Build and send a get request for the remote table.
	 *
	 *	@param	type the type of the request.
	 *	@param	shouldMatchAllKeys whether all keys should be matched for the search.
	 *	@param	key key information which will be searched for.
	 *	@param	record matching record information will be stored in this parameter.
	 *	@param	lastKeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *
	 *	@retval	STATUS_CODE_SUCCESS
	 *	@retval	STATUS_CODE_INVALID_FIELD
	 *	@retval	STATUS_CODE_INVALID_INDEX
	 *	@retval	STATUS_CODE_INVALID_KEY
	 *	@retval	STATUS_CODE_INVALID_PARAMETER
	 *	@retval	STATUS_CODE_HEAP_EMPTY
	 *	@retval	STATUS_CODE_NOT_FOUND
	 *	@retval	STATUS_CODE_OUT_OF_RANGE
	 */
	StatusCode Get(const MessageType type, const bool shouldMatchAllKeys, Database::Key &key, Database::Record &record, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength) const;

	/**
	 *	@brief	Build and send a get request for the remote table.
	 *
	 *	@param	type the type of the request.
	 *	@param	value set equal to the returned value,
	 *
	 *	@retval	STATUS_CODE_SUCCESS
	 *	@retval	STATUS_CODE_INVALID_FIELD
	 *	@retval	STATUS_CODE_INVALID_INDEX
	 *	@retval	STATUS_CODE_INVALID_KEY
	 *	@retval	STATUS_CODE_INVALID_PARAMETER
	 *	@retval	STATUS_CODE_HEAP_EMPTY
	 *	@retval	STATUS_CODE_NOT_FOUND
	 *	@retval	STATUS_CODE_OUT_OF_RANGE
	 */
	StatusCode Get(const MessageType type, size_t &value) const;

	/**
	 *	@brief	Build and send a get multiple request for the remote table.
	 *
	 *	@param	type the type of the request.
	 *	@param	key key information which will be searched for.
	 *	@param	recordList set equal to the list of returned matching records.
	 *	@param	maxResponseDatabase::Records the maximum number of records to include in the response.
	 *
	 *	@retval	STATUS_CODE_SUCCESS
	 *	@retval	STATUS_CODE_INVALID_FIELD
	 *	@retval	STATUS_CODE_INVALID_INDEX
	 *	@retval	STATUS_CODE_INVALID_KEY
	 *	@retval	STATUS_CODE_INVALID_PARAMETER
	 *	@retval	STATUS_CODE_HEAP_EMPTY
	 *	@retval	STATUS_CODE_NOT_FOUND
	 *	@retval	STATUS_CODE_OUT_OF_RANGE
	 */
	StatusCode GetMultiple(const MessageType type, Database::Key &key, Database::RecordList &recordList, const size_t maxResponseRecords) const;

	/**
	 *	@brief	Build and send a get multiple request for the remote table.
	 *
	 *	@param	type the type of the request.
	 *	@param	shouldMatchAllKeys whether all keys should be matched for the search.
	 *	@param	key key information which will be searched for.
	 *	@param	recordList set equal to the list of returned matching records.
	 *	@param	lastKeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *	@param	maxResponseDatabase::Records the maximum number of records to include in the response.
	 *
	 *	@retval	STATUS_CODE_SUCCESS
	 *	@retval	STATUS_CODE_INVALID_FIELD
	 *	@retval	STATUS_CODE_INVALID_INDEX
	 *	@retval	STATUS_CODE_INVALID_KEY
	 *	@retval	STATUS_CODE_INVALID_PARAMETER
	 *	@retval	STATUS_CODE_HEAP_EMPTY
	 *	@retval	STATUS_CODE_NOT_FOUND
	 *	@retval	STATUS_CODE_OUT_OF_RANGE
	 */
	StatusCode GetMultiple(const MessageType type, const bool shouldMatchAllKeys, Database::Key &key, Database::RecordList &recordList, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength, const size_t maxResponseRecords) const;

	/**
	 *	@brief	Build and send a step request for the remote table.
	 *
	 *	@param	type the type of the request.
	 *	@param	recordId set equal to the id of the located record.
	 *	@param	record set equal to the located record information.
	 *
	 *	@retval	STATUS_CODE_SUCCESS
	 *	@retval	STATUS_CODE_INVALID_FIELD
	 *	@retval	STATUS_CODE_INVALID_INDEX
	 *	@retval	STATUS_CODE_INVALID_KEY
	 *	@retval	STATUS_CODE_INVALID_PARAMETER
	 *	@retval	STATUS_CODE_HEAP_EMPTY
	 *	@retval	STATUS_CODE_NOT_FOUND
	 *	@retval	STATUS_CODE_OUT_OF_RANGE
	 */
	StatusCode Step(const MessageType type, Database::DataId &recordId, Database::Record &record) const;

	/**
	 *	@brief	Build and send a step multiple request for the remote table.
	 *
	 *	@param	type the type of the request.
	 *	@param	recordId record id information which will be searched for.
	 *	@param	recordList set equal to the list of returned matching records.
	 *	@param	maxResponseRecords the maximum number of records to include in the response.
	 *
	 *	@retval	STATUS_CODE_SUCCESS
	 *	@retval	STATUS_CODE_INVALID_FIELD
	 *	@retval	STATUS_CODE_INVALID_INDEX
	 *	@retval	STATUS_CODE_INVALID_KEY
	 *	@retval	STATUS_CODE_INVALID_PARAMETER
	 *	@retval	STATUS_CODE_HEAP_EMPTY
	 *	@retval	STATUS_CODE_NOT_FOUND
	 *	@retval	STATUS_CODE_OUT_OF_RANGE
	 */
	StatusCode StepMultiple(const MessageType type, Database::DataId &recordId, Database::RecordList &recordList, const size_t maxResponseRecords) const;

	/**
	 *	@brief	Post an aysnc get request.
	 *
	 *	@param	type the type of the request.
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	...
	 */
	StatusCode PostGetRequest(const MessageType type, const RequestId &requestId, const Database::Key &key) const;

	/**
	 *	@brief	Post an aysnc partial get request.
	 *
	 *	@param	type the type of the request.
	 *	@param	shouldMatchAllKeys whether all keys should be matched in the search.
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	lastKeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	...
	 */
	StatusCode PostGetPartialRequest(const MessageType type, const bool shouldMatchAllKeys, const RequestId &requestId, const Database::Key &key, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength) const;

	/**
	 *	@brief	Post an async get multiple request.
	 *
	 *	@param	type the type of the request.
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	maxResponseRecords the maximum number of records to include in the response.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	...
	 */
	StatusCode PostGetMultipleRequest(const MessageType type, const RequestId &requestId, const Database::Key &key, const size_t maxResponseRecords) const;

	/**
	 *	@brief	Post an async get multiple partial request.
	 *
	 *	@param	type the type of the request.
	 *	@param	shouldMatchAllKeys whether all keys should be matched in the search.
	 *	@param	requestId request id for the outgoing request.
	 *	@param	key key information which will be searched for.
	 *	@param	lastKeyFieldId the field identifier of the last key field to be used for the partial search.
	 *	@param	lastKeyCompareLength the amount of the last key field that should be used in the partial key comparisons.
	 *	@param	maxResponseRecords the maximum number of records to include in the response.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	...
	 */
	StatusCode PostGetMultiplePartialRequest(const MessageType type, const bool shouldMatchAllKeys, const RequestId &requestId, const Database::Key &key, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength, const size_t maxResponseRecords) const;

	/**
	 *	@brief	Post an aysnc step request.
	 *
	 *	@param	type the type of the request.
	 *	@param	requestId request id for the outgoing request.
	 *	@param	recordId the id of the record which will be searched for.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	...
	 */
	StatusCode PostStepRequest(const MessageType type, const RequestId &requestId, const Database::DataId &recordId) const;

	/**
	 *	@brief	Post an async step multiple request.
	 *
	 *	@param	type the type of the request.
	 *	@param	requestId request id for the outgoing request.
	 *	@param	recordId the id of the record to continue the search from.
	 *	@param	maxResponseRecords the maximum number of records to include in the response.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	...
	 */
	StatusCode PostStepMultipleRequest(const MessageType type, const RequestId &requestId, const Database::DataId &recordId, const size_t maxResponseRecords) const;

	/**
	 *	@brief	Send table get request.
	 *
	 *	@param	type the type of the request.
	 *	@param	messageBuilder the message builder.
	 *	@param	response HeapMessage to receive the response.
	 *
	 *	@retval	STATUS_CODE_SUCCESS.
	 *	@retval	...
	 */
	StatusCode SendTableGetRequest(const MessageType type, const MessageBuilder &messageBuilder, HeapMessage &response) const;

	/**
	 *	@brief	Deserialize a get response.
	 */
	StatusCode DeserializeGetResponse(const HeapMessage &response, Database::Key &key, Database::Record &record, byte_t *pBuffer, const size_t bufferLength) const;

	/**
	 *	@brief	Deserialize a get multiple equal response.
	 */
	StatusCode DeserializeGetMultipleEqualResponse(const HeapMessage &response, std::vector<StatusCode> &statusCodeList, Database::RecordList &recordList, byte_t *pBuffer, const size_t bufferLength) const;

	/**
	 *	@brief	Deserialize a get multiple response.
	 */
	StatusCode DeserializeGetMultipleResponse(const HeapMessage &response, Database::Key &key, Database::RecordList &recordList, byte_t *pBuffer, const size_t bufferLength) const;

	/**
	 *	@brief	Deserialize a step response.
	 */
	StatusCode DeserializeStepResponse(const HeapMessage &response, Database::DataId &recordId, Database::Record &record, byte_t *pBuffer, const size_t bufferLength) const;

	/**
	 *	@brief	Deserialize a step multiple response.
	 */
	StatusCode DeserializeStepMultipleResponse(const HeapMessage &response, Database::DataId &recordId, Database::RecordList &recordList, byte_t *pBuffer, const size_t bufferLength) const;

	/**
	 *	@brief	Get matching table client.
	 *
	 *	@param	key the search key.
	 *
	 *	@return	the table client that would normally contain the key.
	 */
	const TableClient *GetMatchingTableClient(const Database::Key &key) const;

	/**
	 *	@brief	Get table client.
	 *
	 *	@param	splitIndex the split index
	 *
	 *	@return	the table client that corresponds to the split index supplied.
	 */
	const TableClient *GetTableClient(const SplitIndex splitIndex) const;

	/**
	 *	@brief	Get next table client.
	 *
	 *	@param	splitIndex the split index
	 *
	 *	@return	the next table client from the supplied split index.
	 */
	const TableClient *GetNextTableClient(const SplitIndex splitIndex) const;

	/**
	 *	@brief	Get previous table client.
	 *
	 *	@param	splitIndex the split index
	 *
	 *	@return	the previous table client from the supplied split index.
	 */
	const TableClient *GetPreviousTableClient(const SplitIndex splitIndex) const;

	/**
	 *	@brief	Get thread info.
	 *
	 *	@return	the thread info.
	 */
	ThreadInfo *GetThreadInfo() const;

	/**
	 *	@brief	Allocate thread info.
	 *
	 *	@return	the allocated thread info.
	 */
	ThreadInfo *AllocateThreadInfo() const;

	/**
	 *	@brief	Is open.
	 *
	 *	@return	whether the state is open.
	 */
	bool IsOpen() const;

	/**
	 *	@brief	Is open.
	 *
	 *	@return	whether the state is open.
	 */
	static bool ShouldMatchAllKeys(const Database::Key &key, const Database::FieldSpecification::Id lastKeyFieldId, const size_t lastKeyCompareLength);

	/**
	 *	@brief	Is key defined.
	 *
	 *	@return	whether the key is defined.
	 */
	static bool IsKeyDefined(const Database::Key &key);

	typedef ThreadSpecificData<ThreadInfo, DeleteObject> ThreadInfoThreadSpecificData;

	static ThreadInfoThreadSpecificData	m_threadInfo;	///< The thread local info.

	State				m_state;			///< State of the connection to the service.
	ServiceHandle		m_serviceHandle;	///< Handle to the remote table.
	Database::ITable *	m_pDatabaseTable;	///< Remote table.

	SplitIndex			m_splitIndex;		///< Index of this table in a split table client chain.

	TableClient *		m_pHead;			///< The head of the split table client chain.
	TableClient *		m_pTail;			///< The tail of the split table client chain.
	TableClient *		m_pPrevious;		///< The previous table client in a split table client chain.
	TableClient *		m_pNext;			///< The next table client in a split table client chain.
};

// ---------------------------------------------------------------------------------------------------------------------------------

inline bool TableClient::IsSplit() const
{
	return (m_pNext || m_pPrevious);
}

// ---------------------------------------------------------------------------------------------------------------------------------

} // namespace Activ

#endif // (!defined ACTIV_SERVICES_TABLE_CLIENT_H)
