#include "pch.h"

#include "DescriptiveStatistics.h"
#include "Stats.h"

using namespace Stats;

TEST(DescriptiveStatsTests, TestDefaultKeys)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto results = GetDescriptiveStatistics(v);

	// Assert
	EXPECT_DOUBLE_EQ(results.at("Mean"), 5.5);
	EXPECT_DOUBLE_EQ(results.at("Median"), 5.5);
	EXPECT_NEAR(results.at("StdDev.P"), 2.8722813232690143, 1e-14);
	EXPECT_NEAR(results.at("StdDev.S"), 3.0276503540974917, 1e-14);
	EXPECT_DOUBLE_EQ(results.at("StdErr"), 0.95742710775633810);
	EXPECT_NEAR(results.at("Variance.P"), 8.250000000000000, 1e-14);
	EXPECT_NEAR(results.at("Variance.S"), 9.166666666666666, 1e-14);
	EXPECT_DOUBLE_EQ(results.at("Skew"), 0.0);
	EXPECT_DOUBLE_EQ(results.at("Kurtosis"), 1.7757575757575756);
	EXPECT_DOUBLE_EQ(results.at("Kurtosis.XS"), -1.2242424242424244);
	EXPECT_DOUBLE_EQ(results.at("Range"), 9);
	EXPECT_DOUBLE_EQ(results.at("Minimum"), 1);
	EXPECT_DOUBLE_EQ(results.at("Maximum"), 10);
	EXPECT_DOUBLE_EQ(results.at("Sum"), 55.0);
	EXPECT_EQ(results.at("Count"), v.size());
}

TEST(DescriptiveStatsTests, TestEmptyKeys)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<std::string> keys;

	// Act
	const auto results = GetDescriptiveStatistics(v, keys);

	// Assert
	EXPECT_DOUBLE_EQ(results.at("Mean"), 5.5);
	EXPECT_DOUBLE_EQ(results.at("Median"), 5.5);
	EXPECT_NEAR(results.at("StdDev.P"), 2.8722813232690143, 1e-14);
	EXPECT_NEAR(results.at("StdDev.S"), 3.0276503540974917, 1e-14);
	EXPECT_DOUBLE_EQ(results.at("StdErr"), 0.95742710775633810);
	EXPECT_NEAR(results.at("Variance.P"), 8.250000000000000, 1e-14);
	EXPECT_NEAR(results.at("Variance.S"), 9.166666666666666, 1e-14);
	EXPECT_DOUBLE_EQ(results.at("Skew"), 0.0);
	EXPECT_DOUBLE_EQ(results.at("Kurtosis"), 1.7757575757575756);
	EXPECT_DOUBLE_EQ(results.at("Kurtosis.XS"), -1.2242424242424244);
	EXPECT_DOUBLE_EQ(results.at("Range"), 9);
	EXPECT_DOUBLE_EQ(results.at("Minimum"), 1);
	EXPECT_DOUBLE_EQ(results.at("Maximum"), 10);
	EXPECT_DOUBLE_EQ(results.at("Sum"), 55.0);
	EXPECT_EQ(results.at("Count"), v.size());
}

TEST(DescriptiveStatsTests, TestCorrectKeys)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<std::string> keys
	{
		"Mean",
		"Median",
		"Sum"
	};

	// Act
	const auto results = GetDescriptiveStatistics(v, keys);

	// Assert
	EXPECT_EQ(keys.size(), results.size());
	EXPECT_DOUBLE_EQ(results.at("Mean"), 5.5);
	EXPECT_DOUBLE_EQ(results.at("Median"), 5.5);
	EXPECT_DOUBLE_EQ(results.at("Sum"), 55.0);
}

TEST(DescriptiveStatsTests, TestIncorrectKeys)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<std::string> keys
	{
		"Meanie",
		"Medium",
		"Sun"
	};

	// Act
	const auto results = GetDescriptiveStatistics(v, keys);

	// Assert
	EXPECT_EQ(keys.size(), results.size());
	EXPECT_DOUBLE_EQ(results.at("Invalid key: Meanie"), 0.0);
	EXPECT_DOUBLE_EQ(results.at("Invalid key: Medium"), 0.0);
	EXPECT_DOUBLE_EQ(results.at("Invalid key: Sun"), 0.0);
}

TEST(DescriptiveStatsTests, TestDescriptiveStatisticsNoData)
{
	// Arrange
	std::vector<double> v{ };
	std::vector<std::string> keys{ };

	// Act / Assert
	EXPECT_THROW(GetDescriptiveStatistics(v, keys), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestMean) 
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto mean = DescriptiveStatistics::Mean(v);

	// Assert
	EXPECT_DOUBLE_EQ(mean, 5.5);
}

TEST(DescriptiveStatsTests, TestMeanNoData)
{
	// Arrange
	std::vector<double> v{ };

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::Mean(v), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestStandardError)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto standard_error = DescriptiveStatistics::StandardError(v, DescriptiveStatistics::VarianceType::Sample);

	// Assert
	EXPECT_DOUBLE_EQ(standard_error, 0.95742710775633810);
}

TEST(DescriptiveStatsTests, TestStandardErrorNoData)
{
	// Arrange
	std::vector<double> v{ };
	auto var_type = DescriptiveStatistics::VarianceType::Sample;

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::StandardError(v, var_type), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestMedianOdd)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

	// Act
	const auto median = DescriptiveStatistics::Median(v);

	// Assert
	EXPECT_DOUBLE_EQ(median, 6);
}

TEST(DescriptiveStatsTests, TestMedianEven)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto median = DescriptiveStatistics::Median(v);

	// Assert
	EXPECT_DOUBLE_EQ(median, 5.5);
}

TEST(DescriptiveStatsTests, TestMedianNoData)
{
	// Arrange
	std::vector<double> v{ };

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::Median(v), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestSampleStandardDeviation)
{
	// Arrange
	std::vector<double> v{ 2, 2, 4, 4, 9, 5, 10, 10, 6, 9, 5, 4, 4, 9, 3, 1, 3, 10, 5, 4 };

	// Act
	const auto sd = DescriptiveStatistics::StandardDeviation(v, DescriptiveStatistics::VarianceType::Sample);

	// Assert
	EXPECT_NEAR(sd, 2.964260802504250, 1e-14);
}

TEST(DescriptiveStatsTests, TestPopulationStandardDeviation)
{
	// Arrange
	std::vector<double> v{ 2, 2, 4, 4, 9, 5, 10, 10, 6, 9, 5, 4, 4, 9, 3, 1, 3, 10, 5, 4 };

	// Act
	const auto sd = DescriptiveStatistics::StandardDeviation(v, DescriptiveStatistics::VarianceType::Population);

	// Assert
	EXPECT_NEAR(sd, 2.889204042638730, 1e-14);
}

TEST(DescriptiveStatsTests, TestStandardDeviationNoData)
{
	// Arrange
	std::vector<double> v{ };
	auto var_type = DescriptiveStatistics::VarianceType::Sample;

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::StandardDeviation(v, var_type), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestSampleVariance)
{
	// Arrange
	std::vector<double> v{ 2, 2, 4, 4, 9, 5, 10, 10, 6, 9, 5, 4, 4, 9, 3, 1, 3, 10, 5, 4 };

	// Act
	const auto variance = DescriptiveStatistics::Variance(v, DescriptiveStatistics::VarianceType::Sample);

	// Assert
	EXPECT_NEAR(variance, 8.786842105263160, 1e-14);
}

TEST(DescriptiveStatsTests, TestPopulationVariance)
{
	// Arrange
	std::vector<double> v{ 2, 2, 4, 4, 9, 5, 10, 10, 6, 9, 5, 4, 4, 9, 3, 1, 3, 10, 5, 4 };

	// Act
	const auto variance = DescriptiveStatistics::Variance(v, DescriptiveStatistics::VarianceType::Population);

	// Assert
	EXPECT_NEAR(variance, 8.347500000000000, 1e-14);
}

TEST(DescriptiveStatsTests, TestVarianceNoData)
{
	// Arrange
	std::vector<double> v{ };
	auto var_type = DescriptiveStatistics::VarianceType::Sample;

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::Variance(v, var_type), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestSkew)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto skew = DescriptiveStatistics::Skew(v);

	// Assert
	EXPECT_DOUBLE_EQ(skew, 0.0);
}

TEST(DescriptiveStatsTests, TestSkewNoData)
{
	// Arrange
	std::vector<double> v{ };

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::Skew(v), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestKurtosis)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto kurtosis = DescriptiveStatistics::Kurtosis(v);

	// Assert
	EXPECT_DOUBLE_EQ(kurtosis, 1.7757575757575756);
}

TEST(DescriptiveStatsTests, TestKurtosisNoData)
{
	// Arrange
	std::vector<double> v{ };

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::Kurtosis(v), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestExcessKurtosis)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto kurtosis = DescriptiveStatistics::ExcessKurtosis(v);

	// Assert
	EXPECT_DOUBLE_EQ(kurtosis, -1.2242424242424244);
}

TEST(DescriptiveStatsTests, TestExcessKurtosisNoData)
{
	// Arrange
	std::vector<double> v{ };

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::ExcessKurtosis(v), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestRange)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto range = DescriptiveStatistics::Range(v);

	// Assert
	EXPECT_DOUBLE_EQ(range, 9);
}

TEST(DescriptiveStatsTests, TestRangeNoData)
{
	// Arrange
	std::vector<double> v{ };

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::Range(v), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestMinimum)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto min = DescriptiveStatistics::Minimum(v);

	// Assert
	EXPECT_DOUBLE_EQ(min, 1);
}

TEST(DescriptiveStatsTests, TestMinimumNoData)
{
	// Arrange
	std::vector<double> v{ };

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::Minimum(v), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestMaximum)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto max = DescriptiveStatistics::Maximum(v);

	// Assert
	EXPECT_DOUBLE_EQ(max, 10);
}

TEST(DescriptiveStatsTests, TestMaximumNoData)
{
	// Arrange
	std::vector<double> v{ };

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::Maximum(v), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestSum)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto sum = DescriptiveStatistics::Sum(v);

	// Assert
	EXPECT_DOUBLE_EQ(sum, 55.0);
}

TEST(DescriptiveStatsTests, TestSumNoData)
{
	// Arrange
	std::vector<double> v{ };

	// Act
	const auto sum = DescriptiveStatistics::Sum(v);

	// Assert
	EXPECT_DOUBLE_EQ(sum, 0.0);
}

TEST(DescriptiveStatsTests, TestProduct)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Act
	const auto product = DescriptiveStatistics::Product(v);

	// Assert
	EXPECT_DOUBLE_EQ(product, 3628800.0);
}

TEST(DescriptiveStatsTests, TestProductNoData)
{
	// Arrange
	std::vector<double> v{ };

	// Act / Assert
	EXPECT_THROW(DescriptiveStatistics::Product(v), std::invalid_argument);
}

TEST(DescriptiveStatsTests, TestCount)
{
	// Arrange
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	const auto size = v.size();

	// Act
	const auto count = DescriptiveStatistics::Count(v);

	// Assert
	EXPECT_EQ(count, size);
}

TEST(DescriptiveStatsTests, TestCountNoData)
{
	// Arrange
	std::vector<double> v{ };
	const auto size = v.size();

	// Act
	const auto count = DescriptiveStatistics::Count(v);

	// Assert
	EXPECT_EQ(count, size);
}

TEST(DescriptiveStatsTests, TestQuantile50)
{
	// Arrange
	std::vector<double> v{ 2, 2, 4, 4, 9, 5, 10, 10, 6, 9, 5, 4, 4, 9, 3, 1, 3, 10, 5, 4 };

	// Act
	const auto q2 = DescriptiveStatistics::Quantile(v, 0.5);
	const auto median = DescriptiveStatistics::Median(v);

	// Assert
	EXPECT_EQ(q2, median);
}

TEST(DescriptiveStatsTests, TestQuantile25)
{
	// Arrange
	std::vector<double> v{ 2, 2, 4, 4, 9, 5, 10, 10, 6, 9, 5, 4, 4, 9, 3, 1, 3, 10, 5, 4 };

	// Act
	const auto q1 = DescriptiveStatistics::Quantile(v, 0.25);

	// Assert
	EXPECT_EQ(q1, 3.75);
}

TEST(DescriptiveStatsTests, TestQuantile75)
{
	// Arrange
	std::vector<double> v{ 2, 2, 4, 4, 9, 5, 10, 10, 6, 9, 5, 4, 4, 9, 3, 1, 3, 10, 5, 4 };

	// Act
	const auto q3 = DescriptiveStatistics::Quantile(v, 0.75);

	// Assert
	EXPECT_EQ(q3, 9.0);
}
