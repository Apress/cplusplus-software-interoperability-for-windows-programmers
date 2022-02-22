#pragma once

#ifdef DYNAMIC
#   ifdef STATSDLL_EXPORTS
#       define STATSDLL_API __declspec(dllexport)
#   else
#       define STATSDLL_API __declspec(dllimport)
#   endif
#else
#   define STATSDLL_API
#endif

#ifdef _MSC_VER
	#pragma warning( disable: 4251 ) // warning C4251: 'stl': class '...' needs to have dll-interface to be used by clients of class '...'
#endif

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>



namespace Stats
{
	// Type for reporting name and size of the data set
	using DataSetInfo = std::pair<std::string, std::size_t>;

	//
	// Class to manage a collection of named data sets
	//
	class STATSDLL_API DataManager final
	{
	public:
		// Constructor
		DataManager() = default;

		// Destructor
		~DataManager() = default;

		// Move constructor
		DataManager(DataManager&& other) = default;

		// Move assignment
		DataManager& operator=(DataManager&& other) = default;

		// Copy constructor
		DataManager(const DataManager& other) = default;

		// Copy assignment
		DataManager& operator=(const DataManager& other) = default;

		// Retrieve the number of data sets currently available
		std::size_t CountDataSets() const;

		// Add the named data set to the collection
		bool Add(const std::string& name, const std::vector<double>& vals);

		// Retrieve the named data set from the collection
		std::vector<double> GetDataSet(const std::string& name) const;

		// Retrieve the names of the data sets in the current collection
		std::vector<DataSetInfo> ListDataSets() const;

		// Clear the data sets in the collection
		void ClearDataSets();

	private:
		// Collection of named data sets
		std::unordered_map<std::string, std::vector<double>> m_data_sets;
	};
}
