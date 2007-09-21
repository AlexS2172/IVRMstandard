// UnderlyingUpdate.h : Declaration of the CUnderlyingUpdate

#ifndef __UNDERLYINGUPDATE_H_
#define __UNDERLYINGUPDATE_H_

#pragma once
#include "resource.h"       // main symbols
#include "MsgPacking.h"
#include "MsgStruct.h"
#include "MsgPropImpl.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif


struct __UnderlyingUpdateData
{
	BEGIN_PACKING
		FIELD_ENTRY(m_nUndID)
		FIELD_ENTRY(m_dCoeff)
		FIELD_ENTRY(m_bUseHead)
		FIELD_ENTRY(m_enUpdStatus)
	END_PACKING

	LongF			m_nUndID;
	DoubleF			m_dCoeff;
	BoolF			m_bUseHead;


	TStaticField<UNDERLYING_UPDATE_STATUS>		m_enUpdStatus;
};


// CUnderlyingUpdate

class ATL_NO_VTABLE CUnderlyingUpdate :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUnderlyingUpdate, &CLSID_UnderlyingUpdate>,
	public ISupportErrorInfo,
	public IDispatchImpl<IUnderlyingUpdate, &IID_IUnderlyingUpdate, &LIBID_MSGSTRUCTLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public INetPackingConstSizeDataImpl<CUnderlyingUpdate, __UnderlyingUpdateData>
{
public:
	CUnderlyingUpdate()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_UNDERLYINGUPDATE)


BEGIN_COM_MAP(CUnderlyingUpdate)
	COM_INTERFACE_ENTRY(IUnderlyingUpdate)
	COM_INTERFACE_ENTRY2(IDispatch, IUnderlyingUpdate)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	COM_INTERFACE_ENTRY(INetPacking)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

public:

	IMPLEMENT_LONG_PROP		(UndID,					m_nUndID)
	IMPLEMENT_DOUBLE_PROP	(Coeff,					m_dCoeff)
	IMPLEMENT_BOOL_PROP		(UseHead,				m_bUseHead)

	
	IMPLEMENT_SIMPLE_PROP(UNDERLYING_UPDATE_STATUS, UpdStatus, m_enUpdStatus)

};

OBJECT_ENTRY_AUTO(__uuidof(UnderlyingUpdate), CUnderlyingUpdate)

#endif