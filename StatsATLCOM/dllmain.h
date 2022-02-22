// dllmain.h : Declaration of module class.

class CStatsATLCOMModule : public ATL::CAtlDllModuleT< CStatsATLCOMModule >
{
public :
	DECLARE_LIBID(LIBID_StatsATLCOMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_STATSATLCOM, "{19393278-b368-4b36-91c4-7fb4eb095ccf}")
};

extern class CStatsATLCOMModule _AtlModule;
