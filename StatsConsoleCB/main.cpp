#include <iostream>

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

#include "..\Common\include\Stats.h"
#include "..\Common\include\DescriptiveStatistics.h"
#include "..\Common\include\DataManager.h"
#include "..\Common\include\StatisticalTests.h"


using namespace std;

int main()
{
	std::vector<double> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	const auto mean = Stats::DescriptiveStatistics::Mean(v);

    std::cout << "Mean: " << mean << std::endl;

    return 0;
}
