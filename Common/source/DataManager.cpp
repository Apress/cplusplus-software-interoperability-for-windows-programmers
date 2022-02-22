// DataManager.cpp : Defines the functions for the entity.
//

#include <stdexcept>

#include "DataManager.h"

namespace Stats
{
	//
	// Retrieve the number of data sets currently available
	//
	std::size_t DataManager::CountDataSets() const
	{
		return m_data_sets.size();
	}

	//
	// Clear the data sets in the collection
	//
	void DataManager::ClearDataSets()
	{
		m_data_sets.clear();
	}

	//
	// Add the named data set to the collection
	//
	bool DataManager::Add(const std::string& name, const std::vector<double>& vals)
	{
		if (name.empty())
		{
			throw std::invalid_argument("A non-empty data set name is required.");
		}

		if (vals.empty())
		{
			throw std::invalid_argument("A non-empty set of values is required.");
		}

		const auto result = m_data_sets.insert_or_assign(name, vals);
		// The bool component is true if the insertion took place and false if the assignment took place.
		return result.second;
	}

	//
	// Retrieve the named data set from the collection
	//
	std::vector<double> DataManager::GetDataSet(const std::string& name) const
	{
		if (name.empty())
		{
			throw std::invalid_argument("A non-empty data set name is required.");
		}

		const auto result = m_data_sets.find(name);
		if (result != m_data_sets.end())
		{
			return result->second;
		}
		return std::vector<double>();
	}

	//
	// Retrieve the names of the data sets in the current collection
	//
	std::vector<DataSetInfo> DataManager::ListDataSets() const
	{
		std::vector<DataSetInfo> dataSets;
		for (const auto& item : m_data_sets)
		{ 
			dataSets.emplace_back(DataSetInfo(item.first, item.second.size()));
		}
		return dataSets;
	}
}
