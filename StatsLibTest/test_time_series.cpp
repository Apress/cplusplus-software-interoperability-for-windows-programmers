#include "pch.h"

#include "TimeSeries.h"

using namespace Stats;

TEST(TimeSeries, TestMovingAverage)
{
	// Arrange
	const std::string moving_average = testSettings.GetDataDirectory() + "\\moving_average.txt";

	std::vector<double> observations = StatsLibTest::Utils::ReadData(moving_average);
	std::vector<Stats::Date> dates(observations.size());
	std::iota(dates.begin(), dates.end(), 1);

	Stats::TimeSeries time_series(dates, observations);

	// Act
	std::vector<double> results = time_series.MovingAverage(3);

	// Assert
	EXPECT_TRUE(std::isnan(results.at(0)));
	EXPECT_TRUE(std::isnan(results.at(1)));
	EXPECT_NEAR(results.at(2), 3, 1e-5);
	EXPECT_NEAR(results.at(3), 5, 1e-5);
	EXPECT_NEAR(results.at(4), 6.66667, 1e-5);
	EXPECT_NEAR(results.at(5), 11, 1e-5);
	EXPECT_NEAR(results.at(6), 10, 1e-5);
	EXPECT_NEAR(results.at(7), 7.66667, 1e-5);
	EXPECT_NEAR(results.at(8), 3, 1e-5);
	EXPECT_NEAR(results.at(9), 2.66667, 1e-5);
	EXPECT_NEAR(results.at(10), 4, 1e-5);
	EXPECT_NEAR(results.at(11), 5, 1e-5);
	EXPECT_NEAR(results.at(12), 5.66667, 1e-5);
	EXPECT_NEAR(results.at(13), 6, 1e-5);
	EXPECT_NEAR(results.at(14), 6, 1e-5);
}
