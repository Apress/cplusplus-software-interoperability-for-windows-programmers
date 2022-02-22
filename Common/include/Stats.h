#pragma once

#ifdef DYNAMIC
#   ifdef STATSDLL_EXPORTS
#       define STATSDLL_API __declspec(dllexport)
#   else
#       define STATSDLL_API __declspec(dllimport)
#   endif
#else
#   define STATSDLL_API
#endif

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

namespace Stats
{
	// Retrieve a package of descriptive statistics for the input data
	STATSDLL_API std::unordered_map<std::string, double> 
		GetDescriptiveStatistics(const std::vector<double>& data, 
			const std::vector<std::string>& keys = std::vector<std::string>());

	// Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
	STATSDLL_API std::unordered_map<std::string, double> 
		LinearRegression(const std::vector<double>& xs, const std::vector<double>& ys);
}
