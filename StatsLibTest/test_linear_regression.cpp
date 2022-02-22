#include "pch.h"

#include "Stats.h"

using namespace Stats;

TEST(LinearRegressionTests, TestLinearRegression)
{
	// Arrange
	const double b0{ 1.2363636363636363 };
	const double b1{ 1.1696969696969697 };

	std::vector<double> x{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<double> y{ 1, 3, 2, 5, 7, 8, 8, 9, 10, 12 };

	// Act
	const auto results = LinearRegression(x, y);

	// Assert
	EXPECT_EQ(results.at("b0"), b0);
	EXPECT_EQ(results.at("b1"), b1);
}

TEST(LinearRegressionTests, TestLinearRegressionNoData)
{
	// Arrange
	std::vector<double> x{ };
	std::vector<double> y{ };

	// Act / Assert
	EXPECT_THROW(LinearRegression(x, y), std::invalid_argument);
}

