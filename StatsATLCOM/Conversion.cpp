// Conversion.cpp
// Central location for simple type conversion facilities
//

#include "pch.h"
#include "Conversion.h"

using namespace ATL;

namespace Conversion
{
	//
	// Convert a VARIANT (an array of doubles) to a std::vector<double>
	//
	HRESULT VariantToVector(VARIANT vIn, std::vector<double>& out)
	{
		HRESULT hr = S_OK;

		CComSafeArray<VARIANT> sa;
		switch (vIn.vt)
		{
		case VT_ARRAY | VT_VARIANT:
			hr = sa.Attach(vIn.parray);
			break;
		case VT_VARIANT | VT_BYREF:
			switch (vIn.pvarVal->vt)
			{
			case VT_ARRAY | VT_VARIANT | VT_BYREF:
				hr = sa.Attach(*(vIn.pvarVal->pparray));
				break;
			case VT_ARRAY | VT_VARIANT:
				hr = sa.Attach(vIn.pvarVal->parray);
				break;
			default:
				hr = DISP_E_TYPEMISMATCH;
			}
			break;
		default:
			hr = DISP_E_TYPEMISMATCH;
		}

		if (FAILED(hr))
			return hr;

		ULONG count = sa.GetCount();
		out.resize(count);
		std::size_t idx = 0;
		const LONG lb = sa.GetLowerBound();
		const LONG ub = sa.GetUpperBound();
		for (LONG i = lb; i <= ub; i++)
		{
			CComVariant v(sa.GetAt((int)i));
			HRESULT hRes = v.ChangeType(VT_R4 | VT_R8);
			if (SUCCEEDED(hRes))
				out[idx++] = v.dblVal;
		}

		sa.Detach();
		return hr;
	}

	//
	// Convert a VARIANT (an array of strings) to a std::vector<std::string>
	//
	HRESULT VariantToVector(VARIANT vIn, std::vector<std::string>& out)
	{
		HRESULT hr = S_OK;

		CComSafeArray<VARIANT> sa;

		switch (vIn.vt)
		{
		case VT_ARRAY | VT_VARIANT:
			hr = sa.Attach(vIn.parray);
			break;
		case VT_VARIANT | VT_BYREF:
			switch (vIn.pvarVal->vt)
			{
			case VT_ARRAY | VT_VARIANT | VT_BYREF:
				hr = sa.Attach(*(vIn.pvarVal->pparray));
				break;
			case VT_ARRAY | VT_VARIANT:
				hr = sa.Attach(vIn.pvarVal->parray);
				break;
			default:
				hr = DISP_E_TYPEMISMATCH;
			}
			break;
		default:
			hr = DISP_E_TYPEMISMATCH;
		}

		if (FAILED(hr))
			return hr;

		ULONG count = sa.GetCount();
		out.resize(count);
		std::size_t idx = 0;
		const LONG lb = sa.GetLowerBound();
		const LONG ub = sa.GetUpperBound();
		for (LONG i = lb; i <= ub; i++)
		{
			CComVariant v(sa.GetAt(i));
			HRESULT hRes = v.ChangeType(VT_BSTR);
			if (SUCCEEDED(hRes))
			{
				_bstr_t bstr(v.bstrVal);
				out[idx++] = std::string((LPCSTR)bstr);
			}
		}

		sa.Detach();
		return hr;
	}

	//
	// Convert std::unordered_map to a 2d variant array
	//
	HRESULT ResultsToVariant(const std::unordered_map<std::string, double>& results, VARIANT* pvResults)
	{
		CComSafeArrayBound bound[2];
		bound[0].SetCount((long)results.size());
		bound[0].SetLowerBound(1);
		bound[1].SetCount(2);
		bound[1].SetLowerBound(1);
		CComSafeArray<VARIANT> vOut(bound, 2 /* dims */);

		LONG aIndex[2]{};
		int i = 1;
		for (const auto& result : results)
		{
			CComVariant key(result.first.c_str());
			CComVariant value(result.second);

			aIndex[0] = i;
			aIndex[1] = 1;
			vOut.MultiDimSetAt(aIndex, key);
			aIndex[0] = i;
			aIndex[1] = 2;
			vOut.MultiDimSetAt(aIndex, value);
			++i;
		}

		VariantInit(pvResults);
		pvResults->vt = VT_ARRAY | VT_VARIANT;
		HRESULT hr = ::SafeArrayCopy(vOut.Detach(), &pvResults->parray);
		return hr;
	}
}
