#pragma once

#undef _USRDLL
#include "..\Common\include\DataManager.h"
#define _USRDLL

#include "Conversion.h"


namespace API
{
    namespace Data
    {
        // DataManager wrapper class
        class DataManager final
        {
        public:
            // Destructor
            ~DataManager() = default;

            // Constructor
            DataManager() = default;

            // Copy constructor
            DataManager(const DataManager& other) = default;

            // Copy assignment
            DataManager& operator=(const DataManager& other) = default;

            // Retrieve the number of data sets currently available
            std::size_t CountDataSets() const;

            // Add the named data set to the collection
            bool Add(const boost::python::object& name, const boost::python::list& vals);

            // Retrieve the named data set from the collection
            boost::python::list GetDataSet(const boost::python::object& name) const;

            // Retrieve the names of the data sets in the current collection
            boost::python::list ListDataSets() const;

            // Clear the data sets in the collection
            void ClearDataSets();

        private:
            Stats::DataManager m_manager;
        };
    }
}
