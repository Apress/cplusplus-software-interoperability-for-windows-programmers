// CTTest.h : Declaration of the CCTTest

#pragma once
#include "resource.h"       // main symbols

#include "StatsATLCOM_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

// CCTTest
class ATL_NO_VTABLE CCTTest :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCTTest, &CLSID_CTTest>,
	public ISupportErrorInfo,
	public IDispatchImpl<IStatisticalTest, &IID_IStatisticalTest, &LIBID_StatsATLCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CCTTest()
	{
	}

DECLARE_REGISTRY_RESOURCEID(107)

BEGIN_COM_MAP(CCTTest)
	COM_INTERFACE_ENTRY(IStatisticalTest)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(SummaryDataTTest)(DOUBLE mu0, DOUBLE xbar, DOUBLE sx, DOUBLE n, VARIANT* pvResults);
	STDMETHOD(OneSampleTTest)(DOUBLE mu0, VARIANT vX1, VARIANT* pvResults);
	STDMETHOD(TwoSampleTTest)(VARIANT vX1, VARIANT vX2, VARIANT* pvResults);
};

OBJECT_ENTRY_AUTO(__uuidof(CTTest), CCTTest)
