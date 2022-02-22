// DataManager.cpp

#include "pch.h"

#include "Conversion.h"

#include "DataManager.h"


namespace StatsCLR
{
	//
	// Construction
	//
	DataManager::DataManager()
	{
		STATS_TRY
		m_manager = new Stats::DataManager();
		STATS_CATCH
	}
	//
	// Destructor
	//
	DataManager::~DataManager()
	{
		this->!DataManager();
	}

	//
	// Finalizer
	//
	DataManager::!DataManager()
	{
		delete m_manager;
	}

	//
	// Count the number of data sets currently held by the DataManager
	//
	unsigned long long DataManager::CountDataSets()
	{
		STATS_TRY
		return m_manager->CountDataSets();
		STATS_CATCH
	}

	//
	// Add a named data set to the DataManager collection
	//
	bool DataManager::Add(String^ name, List<double>^ vals)
	{
		STATS_TRY

		std::string _name;
		Conversion::MarshalString(name, _name);

		std::vector<double> _data;
		for each (double d in vals)
		{
			_data.emplace_back(d);
		}

		return m_manager->Add(_name, _data);

		STATS_CATCH
	}

	//
	// Retrieve a named data set from the DataManager
	//
	List<double>^ DataManager::GetDataSet(String^ name)
	{
		STATS_TRY

		std::string _name;
		Conversion::MarshalString(name, _name);

		std::vector<double> _data = m_manager->GetDataSet(_name);

		List<double>^ data = gcnew List<double>();
		for (const double d : _data)
			data->Add(d);
		return data;

		STATS_CATCH
	}

	//
	// Retrieve a list of all the data sets currently in the DataManager
	//
	List<Tuple<String^, unsigned long long>^>^ DataManager::ListDataSets()
	{
		STATS_TRY

		List<Tuple<String^, unsigned long long>^>^ results = gcnew List<Tuple<String^, unsigned long long>^>();

		std::vector<Stats::DataSetInfo> dataSets = m_manager->ListDataSets();
		if (!dataSets.empty())
		{
			for (std::size_t i = 0; i < dataSets.size(); ++i)
			{
				const auto& dataSet = dataSets.at(i);

				Tuple<String^, unsigned long long>^ item = gcnew Tuple<String^, unsigned long long>(
					gcnew String(dataSet.first.c_str()), dataSet.second
					);

				results->Add(item);
			}
		}

		return results;

		STATS_CATCH
	}

	//
	// Clear the data sets from the DataManager
	//
	void DataManager::ClearDataSets()
	{
		STATS_TRY
		m_manager->ClearDataSets();
		STATS_CATCH
	}
}
