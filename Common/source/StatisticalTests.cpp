// StatisticalTests.cpp : Defines the functions for the entity.
//

#include <iostream>
#include <random>

/*
* Including this file directly in a clr project and compiling with /clr or /clr:pure
* caused some issue: i.e. including / compiling boost inside a clr project did not work.
* However, wrapping it inside a C++ library seems to work fine: that is StatsCLR links against
* (static library) StatsLib which 'houses' the required boost functionality.
*/

#include <boost/math/statistics/t_test.hpp>
#include <boost/math/distributions/fisher_f.hpp>

#include "StatisticalTests.h"
#include "DescriptiveStatistics.h"


namespace Stats
{
	//
	// Retrieve the results
	//
	std::unordered_map<std::string, double> StatisticalTest::Results() const
	{
		return m_results;
	}

	//
	// T-Test
	//

	//
	// Summary data: population mean, sample mean, sample standard deviation, sample size.
	//
	TTest::TTest(double mu0, double x_bar, double sx, double n)
		: m_mu0(mu0)
		, m_x_bar(x_bar)
		, m_sx(sx)
		, m_n(n)
		, m_test_type(TestType::NoSample)
	{}

	//
	// One-sample: population mean, sample.
	//
	TTest::TTest(double mu0, const std::vector<double>& x1)
		: m_mu0(mu0)
		, m_x1(x1)
		, m_test_type(TestType::OneSample)
	{}

	//
	// Two-sample: the underlying boost implementation assumes equal variances
	//
	TTest::TTest(const std::vector<double>& x1, const std::vector<double>& x2)
		: m_x1(x1)
		, m_x2(x2)
		, m_test_type(TestType::TwoSample)
	{}

	//
	// Perform the t-test
	//
	bool TTest::Perform()
	{
		bool result = false;

		if (m_test_type == TestType::NoSample || m_test_type == TestType::OneSample)
		{
			if (m_test_type == TestType::OneSample)
			{
				m_n = static_cast<double>(m_x1.size());
				m_x_bar = DescriptiveStatistics::Mean(m_x1);
				m_sx = DescriptiveStatistics::StandardDeviation(m_x1, DescriptiveStatistics::VarianceType::Sample);
			}

			const auto [t, p] = boost::math::statistics::one_sample_t_test(m_x_bar, m_sx * m_sx, m_n, m_mu0);

			m_results["t"]		= t;
			m_results["pval"]	= p;
			m_results["df"]		= m_n - 1.0;
			m_results["x1-bar"]	= m_x_bar;
			m_results["sx1"]	= m_sx;
			m_results["n1"]		= m_n;

			result = true;
		}
		else if (m_test_type == TestType::TwoSample)
		{
			const std::size_t n1 = m_x1.size();
			const std::size_t n2 = m_x2.size();
			const double df = (n1 + n2 - 2.0);

			const double mean1 = DescriptiveStatistics::Mean(m_x1);
			const double mean2 = DescriptiveStatistics::Mean(m_x2);
			const double sd1 = DescriptiveStatistics::StandardDeviation(m_x1, DescriptiveStatistics::VarianceType::Sample);
			const double  sd2 = DescriptiveStatistics::StandardDeviation(m_x2, DescriptiveStatistics::VarianceType::Sample);

			const auto [t, p] = boost::math::statistics::two_sample_t_test(m_x1, m_x2);

			m_results["t"]		= t;
			m_results["pval"]	= p;
			m_results["df"]		= df;
			m_results["x1-bar"]	= mean1;
			m_results["sx1"]	= sd1;
			m_results["n1"]		= static_cast<double>(n1);
			m_results["x2-bar"]	= mean2;
			m_results["sx2"]	= sd2;
			m_results["n2"]		= static_cast<double>(n2);

			result = true;
		}

		return result;
	}

	//
	// F-Test
	//

	//
	// Summary data
	//
	FTest::FTest(double sx1, double sx2, double n1, double n2)
		: m_sx1(sx1)
		, m_sx2(sx2)
		, m_n1(n1)
		, m_n2(n2)
		, m_test_type(TestType::FromData)
	{}

	//
	// Two-sample
	//
	FTest::FTest(const std::vector<double>& x1, const std::vector<double>& x2)
		: m_x1(x1)
		, m_x2(x2)
		, m_test_type(TestType::TwoSample)
	{}

	//
	// Perform the F-test
	//
	bool FTest::Perform()
	{
		bool result = false;
		if (m_test_type == TestType::Unknown)
			return result;

		if (m_test_type == TestType::TwoSample)
		{
			m_n1 = static_cast<double>(m_x1.size());
			m_n2 = static_cast<double>(m_x2.size());

			m_sx1 = DescriptiveStatistics::StandardDeviation(m_x1, DescriptiveStatistics::VarianceType::Sample);
			m_sx2 = DescriptiveStatistics::StandardDeviation(m_x2, DescriptiveStatistics::VarianceType::Sample);
		}

		// F-statistic:
		double F = (m_sx1 / m_sx2);
		F *= F;

		// Define our distribution, and get the probability:
		boost::math::fisher_f dist(m_n1 - 1, m_n2 - 1);

		const double cdf = boost::math::cdf(dist, F);
		// This is the area to the left of the F statistic in the F distribution (p(x<=F)).
		// We're interested in the area to the right of the F statistic, so in this case the p-value is 1 - cdf, and it is two-sided.
		const double p = (1 - cdf) * 2;

		const double alpha = 0.05;
		const double ucv = boost::math::quantile(boost::math::complement(dist, alpha));			// Upper Critical Value at alpha
		const double ucv2 = boost::math::quantile(boost::math::complement(dist, alpha / 2));	// Upper Critical Value at alpha/2
		const double lcv = boost::math::quantile(dist, alpha);									// Lower Critical Value at alpha
		const double lcv2 = boost::math::quantile(dist, alpha / 2);								// Lower Critical Value at alpha/2

		m_results["F"] = F;
		m_results["cdf"] = cdf;
		m_results["pval"] = p;
		m_results["df1"] = m_n1 - 1;
		m_results["sx1"] = m_sx1;
		m_results["n1"] = static_cast<double>(m_n1);
		m_results["df2"] = m_n2 - 1;
		m_results["sx2"] = m_sx2;
		m_results["n2"] = static_cast<double>(m_n2);
		m_results["alpha"] = alpha;
		m_results["ucv"] = ucv;
		m_results["ucv2"] = ucv2;
		m_results["lcv"] = lcv;
		m_results["lcv2"] = lcv2;
		result = true;

		return result;
	}
}
