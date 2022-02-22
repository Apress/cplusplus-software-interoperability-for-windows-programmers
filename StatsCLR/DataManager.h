#pragma once

#include "..\include\DataManager.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;

namespace StatsCLR
{
	// The DataManager manages named data sets.
	public ref class DataManager
	{
	public:
		// Constructor
		DataManager();

		// Finalizer
		!DataManager();

		// Destruction
		~DataManager();

		// Count the number of data sets currently held by the DataManager
		unsigned long long CountDataSets();

		// Add a named data set to the DataManager collection
		bool Add(String^ name, List<double>^ vals);

		// Retrieve a named data set from the DataManager
		List<double>^ GetDataSet(String^ name);

		// Retrieve a list of all the data sets currently in the DataManager
		List<Tuple<String^, unsigned long long>^>^ ListDataSets();

		// Clear the data sets from the DataManager
		void ClearDataSets();

	private:
		// Native pointer to the underlying C++ class
		Stats::DataManager* m_manager;
	};
}
