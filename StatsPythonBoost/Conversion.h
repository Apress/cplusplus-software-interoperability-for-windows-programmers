#pragma once

namespace Conversion
{
    // Convert a Python list to a std::vector<T>
    template< typename T >
    inline std::vector< T > to_std_vector(const boost::python::object& list)
    {
        std::vector<T> results;
        for (boost::python::ssize_t i = 0; i < boost::python::len(list); ++i)
            results.push_back(boost::python::extract<T>(list[i]));
        return results;
    }

    // Convert results set to a Python dictionary
    inline void to_dict(const std::unordered_map<std::string, double>& _results, boost::python::dict& results)
    {
        for (const auto& result : _results)
        {
            results[result.first] = result.second;
        }
    }

    // Convert data to a Python list
    inline void to_list(const std::vector<double>& data, boost::python::list& results)
    {
        for (const auto& d : data)
        {
            results.append(d);
        }
    }

}
