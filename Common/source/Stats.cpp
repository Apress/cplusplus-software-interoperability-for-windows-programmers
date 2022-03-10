// Stats.cpp : Defines the functions for the library.
//

#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "Stats.h"
#include "DescriptiveStatistics.h"

namespace {

	using namespace Stats::DescriptiveStatistics;

	void check_same_size(const std::vector<double>& x, const std::vector<double>& y)
	{
		if (x.size() != y.size()) {
			throw std::invalid_argument("The datasets are different sizes.");
		}
	}
}

namespace Stats
{
	//
	// Retrieve a package of descriptive statistics for the input data
	//
	std::unordered_map<std::string, double> 
		GetDescriptiveStatistics(const std::vector<double>& data, 
			const std::vector<std::string>& keys /* = std::vector<std::string>() */)
	{
		// Map of summary statistics functions
		static const std::map<std::string, 
			std::function<double(const std::vector<double>& data)>> statistical_functions
		{
			{ "Mean", Mean },
			{ "Median",  Median },
			{
				"StdDev.P", [](const std::vector<double>& data)
							{ return StandardDeviation(data, VarianceType::Population); }
			},
			{
				"StdDev.S", [](const std::vector<double>& data)
							{ return StandardDeviation(data, VarianceType::Sample); }
			},
			{
				"StdErr", [](const std::vector<double>& data)
							{ return StandardError(data, VarianceType::Sample); }
			},
			{
				"Variance.P", [](const std::vector<double>& data)
							{ return Variance(data, VarianceType::Population); }
			},
			{
				"Variance.S", [](const std::vector<double>& data)
							{ return Variance(data, VarianceType::Sample); }
			},
			{ "Skew", Skew },
			{ "Kurtosis", Kurtosis },
			{ "Kurtosis.XS", ExcessKurtosis },
			{ "Range", Range },
			{ "Minimum", Minimum },
			{ "Maximum", Maximum },
			{ "Sum", Sum },
			{
				"Count", [](const std::vector<double>& data)
						{ return static_cast<double>(Count(data)); }
			},
			{
				"Q1", [](const std::vector<double>& data)
							{ return Quantile(data, 0.25); }
			},
			{
				"Q3", [](const std::vector<double>& data)
							{ return Quantile(data, 0.75); }
			}
		};

		std::unordered_map<std::string, double> results;
		if (keys.empty())
		{
			for (const auto& statistic : statistical_functions)
			{
				results[statistic.first] = statistic.second(data);
			}
		}
		else
		{
			// Retrieve the requested statistics
			for (const auto& key : keys)
			{
				const auto& it = statistical_functions.find(key);
				if (it == statistical_functions.end())
				{
					std::string invalidKey("Invalid key: " + key);
					results[invalidKey] = 0.0;
				}
				else
				{
					const auto& f = it->second;
					results[key] = f(data);
				}
			}
		}

		return results;
	}

	//
	// Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
	//
	std::unordered_map<std::string, double> LinearRegression(const std::vector<double>& xs, const std::vector<double>& ys)
	{
		using namespace Stats::DescriptiveStatistics;

		check_same_size(xs, ys);

		const double x_mean = Mean(xs);
		const double y_mean = Mean(ys);
		double ss_xy = 0;
		double ss_xx = 0;

		const std::size_t n = xs.size();

		for (std::size_t i = 0; i < n; ++i)
		{
			ss_xx += (xs[i] - x_mean) * (xs[i] - x_mean);
			ss_xy += (xs[i] - x_mean) * (ys[i] - y_mean);
		}

		const double b1 = ss_xy / ss_xx;
		const double b0 = y_mean - b1 * x_mean;

		std::unordered_map<std::string, double> results;

		results["x-mean"] = x_mean;
		results["y-mean"] = y_mean;
		results["SS_xx"] = ss_xx;
		results["SS_xy"] = ss_xy;
		results["b0"] = b0;
		results["b1"] = b1;

		return results;
	}
}
