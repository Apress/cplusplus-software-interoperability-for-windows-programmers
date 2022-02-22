// DataManager.cpp: defines the functions and class that we wrap
#include "pch.h"

#include "DataManager.h"

namespace API
{
	namespace Data
	{
        //
        // Retrieve the number of data sets currently available
        //
        std::size_t DataManager::CountDataSets() const
        {
            return m_manager.CountDataSets();
        }

        //
        // Add the named data set to the collection
        //
        bool DataManager::Add(const boost::python::object& name, const boost::python::list& vals)
        {
            const std::string _name = boost::python::extract<std::string>(name);
            std::vector<double> _vals = Conversion::to_std_vector<double>(vals);

            return m_manager.Add(_name, _vals);
        }

        //
        // Retrieve the named data set from the collection
        //
        boost::python::list DataManager::GetDataSet(const boost::python::object& name) const
        {
            const std::string _name = boost::python::extract<std::string>(name);
            std::vector<double> _data = m_manager.GetDataSet(_name);
            boost::python::list results;
            Conversion::to_list(_data, results);
            return results;
        }

        //
        // Retrieve the names of the data sets in the current collection
        //
        boost::python::list DataManager::ListDataSets() const
        {
            std::vector<Stats::DataSetInfo> datasets = m_manager.ListDataSets();
            boost::python::list results;

            for (std::size_t i = 0; i < datasets.size(); ++i)
            {
                // Dataset name and count of elements
                const auto& dataset = datasets.at(i);
                results.append(boost::python::make_tuple(dataset.first, dataset.second));
            }
            return results;
        }

        //
        // Clear the data sets in the collection
        //
        void DataManager::ClearDataSets()
        {
            m_manager.ClearDataSets();
        }

	}
}