// Statistics.cpp

#include "pch.h"

#include "..\include\Stats.h"
#include "..\include\DescriptiveStatistics.h"

#include "Conversion.h"

#include "Statistics.h"


namespace StatsCLR
{
	//
	// Return descriptive statistics for the input data
	//
	Dictionary<String^, double>^ Statistics::DescriptiveStatistics(List<double>^ data, List<String^>^ keys)
	{
		STATS_TRY
		std::vector<double> _data = Conversion::ListToVector(data);
		std::vector<std::string> _keys = Conversion::ListToVector(keys);

		const auto _results = Stats::GetDescriptiveStatistics(_data, _keys);
		Dictionary<String^, double>^ results = Conversion::ResultsToDictionary(_results);
		return results;
		STATS_CATCH
	}
	//
	// Return descriptive statistics for the input data
	//
	Dictionary<String^, double>^ Statistics::DescriptiveStatistics(List<double>^ data)
	{
		return DescriptiveStatistics(data, nullptr);
	}

	//
	// Perform simple univariate linear regression: y ~ x, (y = B0 + xB1)
	//
	Dictionary<String^, double>^ Statistics::LinearRegression(List<double>^ xs, List<double>^ ys)
	{
		STATS_TRY
		const auto _xs = Conversion::ListToVector(xs);
		const auto _ys = Conversion::ListToVector(ys);

		const auto _results = Stats::LinearRegression(_xs, _ys);
		const auto results = Conversion::ResultsToDictionary(_results);
		return results;
		STATS_CATCH
	}
}
