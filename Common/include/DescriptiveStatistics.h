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

namespace Stats
{
	namespace DescriptiveStatistics
	{
		// The type of variance statistic
		enum class STATSDLL_API VarianceType
		{
			Sample,
			Population
		};

		// Compute the mean of a vector of values
		STATSDLL_API double Mean(const std::vector<double>& values);

		// Compute the median of a vector of values
		STATSDLL_API double Median(const std::vector<double>& values);

		// Compute the specified quantile for a vector of values
		STATSDLL_API double Quantile(const std::vector<double>& values, double quantile);

		// Compute the variance of a vector of values
		STATSDLL_API double Variance(const std::vector<double>& values, VarianceType type);

		// Compute the standard deviation of a vector of values
		STATSDLL_API double StandardDeviation(const std::vector<double>& values, VarianceType type);

		// Compute the standard error of a vector of values
		STATSDLL_API double StandardError(const std::vector<double>& values, VarianceType type);

		// Compute the skew of a vector of values
		STATSDLL_API double Skew(const std::vector<double>& values);

		// Compute the kurtosis of a vector of values
		STATSDLL_API double Kurtosis(const std::vector<double>& values);

		// Compute the excess kurtosis of a vector of values
		STATSDLL_API double ExcessKurtosis(const std::vector<double>& values);

		// Compute the range of a vector of values
		STATSDLL_API double Range(const std::vector<double>& values);

		// Compute the minimum of a vector of values
		STATSDLL_API double Minimum(const std::vector<double>& values);

		// Compute the maximum of a vector of values
		STATSDLL_API double Maximum(const std::vector<double>& values);

		// Compute the sum of a vector of values
		STATSDLL_API double Sum(const std::vector<double>& values);

		// Return the count of the values
		STATSDLL_API std::size_t Count(const std::vector<double>& values);

		// Compute the product of a vector of values
		STATSDLL_API double Product(const std::vector<double>& values);
	}
}
