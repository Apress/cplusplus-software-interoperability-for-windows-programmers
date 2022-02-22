#pragma once

#include "..\include\StatisticalTests.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;

namespace StatsCLR 
{
	public ref class TTest 
	{
	public:
		// Constructors

		// Summary data: population mean, sample mean, sample standard deviation, sample size.
		TTest(double mu0, double x_bar, double sx, double n);

		// One-sample: population mean, sample.
		TTest(double mu0, List<double>^ x1);

		// Two-sample
		TTest(List<double>^ x1, List<double>^ x2);

		// Finalizer
		!TTest();
		
		// Destructor
		~TTest();

		// Perform the test
		bool Perform();

		// Retrieve the results
		Dictionary<String^, double>^ Results();

	private:
		// Native pointer to the underlying C++ class
		Stats::TTest* m_test;
	};
}
