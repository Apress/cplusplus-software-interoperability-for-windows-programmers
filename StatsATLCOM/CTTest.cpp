// CTTest.cpp : Implementation of CCTTest

#include "pch.h"
#include "CTTest.h"

#include "Conversion.h"

// CCTTest

STDMETHODIMP CCTTest::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_IStatisticalTest
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCTTest::SummaryDataTTest(DOUBLE mu0, DOUBLE xbar, DOUBLE sx, DOUBLE n, VARIANT* pvResults)
{
	COMHRESULT hr = S_OK;
	try
	{
		Stats::TTest test(mu0, xbar, sx, n);

		hr = test.Perform() ? S_OK : E_FAIL;

		std::unordered_map<std::string, double> results = test.Results();
		hr = Conversion::ResultsToVariant(results, pvResults);
	}
	catch (const CAtlException& e)
	{
		return e;
	}
	return hr;
}

STDMETHODIMP CCTTest::OneSampleTTest(DOUBLE mu0, VARIANT vX1, VARIANT* pvResults)
{
	COMHRESULT hr = S_OK;
	try
	{
		std::vector<double> x1;

		hr = Conversion::VariantToVector(vX1, x1);

		Stats::TTest test(mu0, x1);
		hr = test.Perform() ? S_OK : E_FAIL;
	
		std::unordered_map<std::string, double> results = test.Results();
		hr = Conversion::ResultsToVariant(results, pvResults);
	}
	catch (const CAtlException& e)
	{
		return e;
	}
	return hr;
}

STDMETHODIMP CCTTest::TwoSampleTTest(VARIANT vX1, VARIANT vX2, VARIANT* pvResults)
{
	COMHRESULT hr = S_OK;
	try
	{
		std::vector<double> x1;
		std::vector<double> x2;

		hr = Conversion::VariantToVector(vX1, x1);
		hr = Conversion::VariantToVector(vX2, x2);

		Stats::TTest test(x1, x2);
		hr = test.Perform() ? S_OK : E_FAIL;

		std::unordered_map<std::string, double> results = test.Results();
		hr = Conversion::ResultsToVariant(results, pvResults);
	}
	catch (const CAtlException& e)
	{
		return e;
	}
	return hr;
}
