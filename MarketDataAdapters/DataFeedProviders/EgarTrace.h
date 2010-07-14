#include "stdafx.h"

class CEgTrace : public	EgLib::CEgLibTraceManager
{
public:
	CEgTrace(void)
		:EgLib::CEgLibTraceManager(EgLib::CEgLibTraceManager::enRelativeMyDocuments, _T("Core\\Logs"))
	{
		EgLib::CEgLibTraceManager::FileName = L"ClientDataProvider";
	}

	virtual ~CEgTrace(void)
	{
	}
	static void Trace()
	{
	}
};