// StatsLibWrapper.cpp : Implementation of CStatsLibWrapper

#include "pch.h"
#include "StatsLibWrapper.h"

#include "Conversion.h"

// CStatsLibWrapper

STDMETHODIMP CStatsLibWrapper::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_IStatsLibWrapper
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStatsLibWrapper::DescriptiveStatistics(VARIANT vData, VARIANT vKeys, VARIANT* pvResults)
{
	COMHRESULT hr = S_OK;

	try
	{
		std::vector<double> data;
		std::vector<std::string> keys;

		hr = Conversion::VariantToVector(vData, data);

		if (V_VT(&vKeys) == (VT_BSTR | VT_BYREF | VT_VARIANT))
		{
			CComVariant v(vKeys);
			HRESULT hRes = v.ChangeType(VT_BSTR);
			if (SUCCEEDED(hRes))
			{
				_bstr_t bstr(v.bstrVal);
				std::string k = std::string((LPCSTR)bstr);
				if(!k.empty())
					keys.push_back(k);
			}
		}
		else
		{
			Conversion::VariantToVector(vKeys, keys);
		}

		std::unordered_map<std::string, double> results = Stats::GetDescriptiveStatistics(data, keys);
		hr = Conversion::ResultsToVariant(results, pvResults);
	}
	catch (const CAtlException& e)
	{
		return e;
	}
	return hr;
}

STDMETHODIMP CStatsLibWrapper::LinearRegression(VARIANT vXs, VARIANT vYs, VARIANT* pvResults)
{
	COMHRESULT hr = S_OK;
	try
	{
		std::vector<double> xs;
		std::vector<double> ys;

		hr = Conversion::VariantToVector(vXs, xs);
		hr = Conversion::VariantToVector(vYs, ys);

		std::unordered_map<std::string, double> results = Stats::LinearRegression(xs, ys);
		hr = Conversion::ResultsToVariant(results, pvResults);
	}
	catch (const CAtlException& e)
	{
		return e;
	}
	return hr;
}
