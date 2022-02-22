#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;

namespace StatsCLR
{
	// Performs statistical operations
	public ref class Statistics abstract sealed
	{
	public:
		// Return descriptive statistics for the input data
		static Dictionary<String^, double>^ DescriptiveStatistics(List<double>^ data);

		// Return descriptive statistics for the input data
		static Dictionary<String^, double>^ DescriptiveStatistics(List<double>^ data, List<String^>^ keys);

		// Perform simple univariate linear regression: y ~ x, (y = B0 + xB1)
		static Dictionary<String^, double>^ LinearRegression(List<double>^ xs, List<double>^ ys);
	};
}
