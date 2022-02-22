// StatisticalTests.cpp

#include "pch.h"

#include "Conversion.h"

#include "StatisticalTests.h"


namespace StatsCLR
{
	//
	// Summary data: population mean, sample mean, sample standard deviation, sample size.
	//
	TTest::TTest(double mu0, double x_bar, double sx, double n)
	{
		STATS_TRY

		m_test = new Stats::TTest(mu0, x_bar, sx, n);
		
		STATS_CATCH
	}

	//
	// One-sample: population mean, sample.
	//
	TTest::TTest(double mu0, List<double>^ x1)
	{
		STATS_TRY

		std::vector<double> _x1 = Conversion::ListToVector(x1);
		m_test = new Stats::TTest(mu0, _x1);

		STATS_CATCH
	}

	//
	// Two-sample
	//
	TTest::TTest(List<double>^ x1, List<double>^ x2)
	{
		STATS_TRY
			
		std::vector<double> _x1 = Conversion::ListToVector(x1);
		std::vector<double> _x2 = Conversion::ListToVector(x2);

		m_test = new Stats::TTest(_x1, _x2);

		STATS_CATCH
	}

	// Destructor
	TTest::!TTest()
	{
		delete m_test;
	}

	// Destructor
	TTest::~TTest()
	{
		this->!TTest();
	}

	//
	// Perform the test
	//
	bool TTest::Perform()
	{
		STATS_TRY
		return m_test->Perform();
		STATS_CATCH
	}

	//
	// Retrieve the results
	//
	Dictionary<String^, double>^ TTest::Results()
	{
		STATS_TRY
		const auto _results = m_test->Results();
		Dictionary<String^, double>^ results = Conversion::ResultsToDictionary(_results);
		return results;
		STATS_CATCH
	}
}
