#include "pch.h"

#include "..\Common\include\DataManager.h"

using namespace Stats;

TEST(DataManagerTests, TestDataManagerCount)
{
	// Arrange
	DataManager manager;
	std::vector<double> xs{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<double> ys{ 1, 3, 2, 5, 7, 8, 8, 9, 10, 12 };

	manager.ClearDataSets();
	manager.Add("xs", xs);
	manager.Add("ys", ys);

	// Act
	std::size_t count = manager.CountDataSets();

	// Assert
	EXPECT_EQ(count, 2);
}

TEST(DataManagerTests, TestDataManagerAdd)
{
	// Arrange
	DataManager manager;
	std::vector<double> xs{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	manager.ClearDataSets();
	manager.Add("xs", xs);

	// Act
	std::size_t count = manager.CountDataSets();

	// Assert
	EXPECT_EQ(count, 1);
}

TEST(DataManagerTests, TestDataManagerAddEmptyName)
{
	// Arrange
	DataManager manager;
	std::vector<double> xs{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	manager.ClearDataSets();

	// Act
	EXPECT_THROW(manager.Add("", xs), std::invalid_argument);

	// Assert
}

TEST(DataManagerTests, TestDataManagerAddEmptyData)
{
	// Arrange
	DataManager manager;
	std::vector<double> xs{ };

	manager.ClearDataSets();

	// Act
	EXPECT_THROW(manager.Add("xs", xs), std::invalid_argument);

	// Assert
}

TEST(DataManagerTests, TestDataManagerList)
{
	// Arrange
	DataManager manager;
	std::vector<double> xs{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<double> ys{ 1, 3, 2, 5, 7, 8, 8, 9, 10, 12 };

	manager.ClearDataSets();
	manager.Add("xs", xs);
	manager.Add("ys", ys);

	// Act
	std::vector<DataSetInfo> dataSets = manager.ListDataSets();

	// Assert
	for (const auto& dataSet : dataSets)
	{
		std::vector<double> data = manager.GetDataSet(dataSet.first);
		EXPECT_EQ(data.size(), dataSet.second);
	}
}
