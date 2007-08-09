// SymbolVolatility.h : Declaration of the CSymbolVolatility

#ifndef __SYMBOLVOLATILITY_H_
#define __SYMBOLVOLATILITY_H_

#include "resource.h"

#include "DataHolder.h"


class CVolatilitySource;
_COM_SMARTPTR_TYPEDEF(IVSSymbolVolatility, IID_IVSSymbolVolatility);

/////////////////////////////////////////////////////////////////////////////
// CSymbolVolatility
class ATL_NO_VTABLE CSymbolVolatility : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSymbolVolatility, &CLSID_SymbolVolatility>,
	public ISupportErrorInfo,
	public IDispatchImpl<IVSSymbolVolatility, &IID_IVSSymbolVolatility, &LIBID_VMELib>,
	public IDispatchImpl<IVSTargetVolatility, &IID_IVSTargetVolatility, &LIBID_VMELib>,
	public IDispEventImpl <1, CSymbolVolatility, &DIID__IOnMessages>
{
	bool		 m_bInitialized;

	VARIANT_BOOL m_bEnableEvents;
	VARIANT_BOOL m_bEnableCache;
	VARIANT_BOOL m_bEnableEditing;
	double		 m_dDefaultVola;

	CVolatilitySource*  m_pSource; // To call notifications
	IVAManagementPtr	m_spDS;

	// Message source
	IPubManagerPtr	 m_spPubManager;
	ISubManagerPtr	 m_spSubManager;
	ISymbolObjectPtr m_spSymbolObject;
	IVMESurfacePtr	 m_spVMESurface;

	_bstr_t		   m_bsSymbolName;
	SYMBOL_TYPE	   m_enSymbolType;

	long	  m_nSurfaceID;
	EOptType  m_enOptType;

	CDataHolder m_data;

// Construction/destruction/initialization
public:
	CSymbolVolatility();
	HRESULT FinalConstruct();
	void	FinalRelease();

	STDMETHOD(Init)( CVolatilitySource* pSource, const _bstr_t& bsSymbolName, SYMBOL_TYPE enSymbolType );
	STDMETHOD(Deinit)();
	STDMETHOD(LoadData)();
	STDMETHOD(Save)();

	//STDMETHOD(RegisterPublisher)();
	//STDMETHOD(UnregisterPublisher)();
	STDMETHOD(PublishChanges)( _RecordsetPtr& spRS );

	STDMETHOD(SetSurfaceData) ( _RecordsetPtr& spData  );
	STDMETHOD(SetSurfaceProps)( _RecordsetPtr& spProps );
	STDMETHOD(GetSurfaceData) ( _RecordsetPtr& spData  );
	STDMETHOD(GetSurfaceProps)( _RecordsetPtr& spProps );

	STDMETHOD(EnableEvents) ( VARIANT_BOOL bEnable );
	STDMETHOD(EnableCache)  ( VARIANT_BOOL bEnable );
	STDMETHOD(EnableEditing)( VARIANT_BOOL bEnable );
	STDMETHOD(DefaultVola)  ( double dVola );

	//STDMETHOD(SetSubManager)(ISubManagerPtr spSubManger);
	//STDMETHOD(SetPubManager)(IPubManagerPtr spPubManger);

DECLARE_REGISTRY_RESOURCEID(IDR_SYMBOLVOLATILITY)

DECLARE_NOT_AGGREGATABLE( CSymbolVolatility );
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSymbolVolatility)
	COM_INTERFACE_ENTRY(IVSTargetVolatility)
	COM_INTERFACE_ENTRY(IVSSymbolVolatility)
	COM_INTERFACE_ENTRY2(IDispatch, IVSSymbolVolatility)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_SINK_MAP(CSymbolVolatility)
	SINK_ENTRY_INFO(1, DIID__IOnMessages, DISPID_OnVola, OnVMESurface, &m_OnVMESurfaceInfo)
END_SINK_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVSSymbolVolatility
public:
	STDMETHOD(get_Volatility)(/*[in]*/double UnderlinePrice, /*[in]*/double Strike, /*[in]*/DATE ExpDate, /*[out, retval]*/ double *pVal);
	STDMETHOD(put_Volatility)(/*[in]*/double UnderlinePrice, /*[in]*/double Strike, /*[in]*/DATE ExpDate, /*[in]*/ double newVal);

// _IOnMessages
public:
	STDMETHOD(VolatilityShift)(/*[in]*/ DATE expDate, /*[in]*/ double shift);
	STDMETHOD(VolatilitySet)(/*[in]*/ DATE expDate, /*[in]*/ double newVola);
	STDMETHOD(VolatilitySetAll)(/*[in]*/ double newVola);
	STDMETHOD(VolatilitySetAllByExp)(/*[in]*/ LPSAFEARRAY* saData);	
	STDMETHOD(VolatilitySetAllByExpAndStrike)(/*[in]*/ LPSAFEARRAY* saData);
	STDMETHOD(get_TargetVolatility)(/*[in]*/double UnderlinePrice, /*[in]*/ double Strike, /*[in]*/ DATE expDate, /*[out, retval]*/ double *pVal);
	static _ATL_FUNC_INFO m_OnVMESurfaceInfo;

	STDMETHOD (OnVMESurface)(/*[in]*/IDispatch* Symbol, /*[in]*/IDispatch* Data);
};
_COM_SMARTPTR_TYPEDEF(IVSTargetVolatility, __uuidof(IVSTargetVolatility));


#endif //__SYMBOLVOLATILITY_H_
