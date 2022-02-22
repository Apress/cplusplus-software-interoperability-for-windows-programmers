// StatsLibWrapper.h : Declaration of the CStatsLibWrapper

#pragma once
#include "resource.h"       // main symbols

#include "StatsATLCOM_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

// CStatsLibWrapper
class ATL_NO_VTABLE CStatsLibWrapper :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStatsLibWrapper, &CLSID_StatsLibWrapper>,
	public ISupportErrorInfo,
	public IDispatchImpl<IStatsLibWrapper, &IID_IStatsLibWrapper, &LIBID_StatsATLCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CStatsLibWrapper()	{ }

DECLARE_REGISTRY_RESOURCEID(106)

BEGIN_COM_MAP(CStatsLibWrapper)
	COM_INTERFACE_ENTRY(IStatsLibWrapper)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct() { return S_OK; }

	void FinalRelease() { }

public:
	STDMETHOD(DescriptiveStatistics)(VARIANT vData, VARIANT vKeys, VARIANT* pvResults);
	STDMETHOD(LinearRegression)(VARIANT vXs, VARIANT vYs, VARIANT* pvResults);
};

OBJECT_ENTRY_AUTO(__uuidof(StatsLibWrapper), CStatsLibWrapper)
