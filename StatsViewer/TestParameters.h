#pragma once

namespace StatsViewer {

	// Determine if the input string is a valid number
	inline bool isValidNumber(const std::string& s)
	{
		std::stringstream _s(s);
		double val = 0.0;
		_s >> val;
		return !_s.fail();
	}

	//
	// Class to encapsulate parameters for the TTest.
	//
	struct TTestParams final
	{
		enum class TestType
		{
			Unknown = 0,
			SummaryData = 1,
			OneSample = 2,
			TwoSample = 3
		};

		// Construction
		TTestParams() = default;

		// Destruction
		~TTestParams() = default;

		// Copy constructor
		TTestParams(const TTestParams& other) = default;

		// Assignment operator
		TTestParams& operator=(const TTestParams& other) = default;

		// Population mean
		double mu0{ 0.0 };

		// Sample mean
		double xbar{ 0.0 };

		// Sample standard deviation
		double sx{ 0.0 };

		// Sample size
		double n{ 0.0 };

		// The type of test for which we are getting the parameters
		TestType test_type{ TestType::Unknown };
	};

	//
	// Class to encapsulate parameters for the FTest.
	//
	struct FTestParams final
	{
		enum class TestType
		{
			Unknown = 0,
			SummaryData = 1,
			TwoSample = 2
		};

		// Construction
		FTestParams() = default;

		// Destruction
		~FTestParams() = default;

		// Copy constructor
		FTestParams(const FTestParams& other) = default;

		// Assignment operator
		FTestParams& operator=(const FTestParams& other) = default;

		// Sample standard deviation 1
		double sx1{ 0.0 };

		// Sample standard deviation 2
		double sx2{ 0.0 };

		// Sample size 1
		double n1{ 0.0 };

		// Sample size 2
		double n2{ 0.0 };

		// The type of test for which we are getting the parameters
		TestType test_type{ TestType::Unknown };
	};
}


