#include <numeric>
#include <functional>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <stdexcept>
#include <map>
#include <cmath>

#include <boost/math/statistics/univariate_statistics.hpp>

#include "DescriptiveStatistics.h"

namespace {

	void check_empty_data(const std::vector<double>& data)
	{
		if (data.empty()) throw std::invalid_argument("The data is empty.");
	}

	void check_data_size(const std::vector<double>& data, std::size_t expected)
	{
		if (data.size() < expected) throw std::invalid_argument("Insufficient data to perform the operation.");
	}
}

namespace Stats::DescriptiveStatistics
{
	//
	// Compute the mean of a vector of values
	//
	double Mean(const std::vector<double>& values)
	{
		check_empty_data(values);

		const auto n = values.size();
		const auto sum = std::accumulate(std::begin(values), std::end(values), 0.0);
		const auto mean = sum / n;
		return mean;
	}

	//
	// Compute the median of a vector of values
	//
	double Median(const std::vector<double>& values)
	{
		check_empty_data(values);

		const auto n = values.size();
		std::vector<double> _values(values);
		std::sort(std::begin(_values), std::end(_values));
		const auto mid = n / 2;
		return n % 2 == 0 ? (_values.at(mid) + _values.at(mid - 1)) / 2 : _values.at(mid);
	}

	//
	// Compute the specified quantile for a vector of values
	//
	double Quantile(const std::vector<double>& values, double quantile)
	{
		// https://www.open.edu/openlearn/science-maths-technology/prices-location-and-spread/content-section-3.2
		check_empty_data(values);

		const auto n = values.size();
		if (1 == n)
			return values[0];

		std::vector<double> _values(values);
		std::sort(std::begin(_values), std::end(_values));

		const auto index = (n - 1) * quantile;
		const auto left = floor(index);
		const auto right = ceil(index);
		const auto weight = (index - left);
		// Interpolate
		const auto q = (1.0 - weight) * _values[static_cast<std::size_t>(left)] + weight * _values[static_cast<std::size_t>(right)];
		return q;
	}

	//
	// Compute the variance of a vector of values
	//
	double Variance(const std::vector<double>& values, VarianceType type)
	{
		check_empty_data(values);

		if (values.size() <= 1)
		{
			return 0.0;
		}

		const auto n = (type == VarianceType::Population) ? values.size() : values.size() - 1;
		const auto mean = Mean(values);

		double sum_diff_sq{ 0.0 };
		for (auto value : values)
		{
			sum_diff_sq += (value - mean) * (value - mean);
		}

		const auto variance = sum_diff_sq / n;
		return variance;
	}

	//
	// Compute the standard deviation of a vector of values
	//
	double StandardDeviation(const std::vector<double>& values, VarianceType type)
	{
		const auto standard_deviation = std::sqrt(Variance(values, type));
		return standard_deviation;
	}

	//
	// Compute the standard error of a vector of values
	//
	double StandardError(const std::vector<double>& values, VarianceType type)
	{
		check_empty_data(values);

		const auto n = values.size();
		const auto standard_deviation = StandardDeviation(values, type);
		const auto standard_error = standard_deviation / std::sqrt(n);
		return standard_error;
	}

	//
	// Compute the skew of a vector of values
	//
	double Skew(const std::vector<double>& values)
	{
		check_data_size(values, 3);

		const double skew = boost::math::statistics::skewness(values);
		return skew;
	}

	//
	// Compute the kurtosis of a vector of values
	//
	double Kurtosis(const std::vector<double>& values)
	{
		// https://brownmath.com/stat/shape.htm
		check_data_size(values, 4);

		const double kurtosis = boost::math::statistics::kurtosis(values);
		return kurtosis;
	}

	//
	// Compute the excess kurtosis of a vector of values
	//
	double ExcessKurtosis(const std::vector<double>& values)
	{
		check_data_size(values, 4);

		const double kurtosis = boost::math::statistics::excess_kurtosis(values);
		return kurtosis;
	}

	//
	// Compute the range of a vector of values
	//
	double Range(const std::vector<double>& values)
	{
		check_empty_data(values);

		const auto [min, max] = std::minmax_element(std::begin(values), std::end(values));
		return (*max) - (*min);
	}

	//
	// Compute the minimum of a vector of values
	//
	double Minimum(const std::vector<double>& values)
	{
		check_empty_data(values);

		const auto [min, max] = std::minmax_element(std::begin(values), std::end(values));
		return *min;
	}

	//
	// Compute the maximum of a vector of values
	//
	double Maximum(const std::vector<double>& values)
	{
		check_empty_data(values);

		const auto [min, max] = std::minmax_element(std::begin(values), std::end(values));
		return *max;
	}

	//
	// Compute the sum of a vector of values
	//
	double Sum(const std::vector<double>& values)
	{
		const auto sum = std::accumulate(std::begin(values), std::end(values), 0.0);
		return sum;
	}

	//
	// Return the count of the values
	//
	std::size_t Count(const std::vector<double>& values)
	{
		return values.size();
	}

	//
	// Compute the product of a vector of values
	//
	double Product(const std::vector<double>& values)
	{
		check_empty_data(values);

		const auto product = std::accumulate(std::begin(values), std::end(values),
			1.0, std::multiplies<double>());
		return product;
	}
}
