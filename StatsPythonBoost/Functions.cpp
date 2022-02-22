// Functions.cpp: defines the functions that we are wrapping

#include "pch.h"

#undef _USRDLL
#include "Stats.h"
#define _USRDLL

#include "Conversion.h"

namespace API
{
    //
    // Retrieve a package of descriptive statistics for the input data
    //
    boost::python::dict DescriptiveStatistics(const boost::python::list& data, 
        const boost::python::list& keys /* = boost::python::list() */)
    {
        std::vector<double> _data = Conversion::to_std_vector<double>(data);
        std::vector<std::string> _keys = Conversion::to_std_vector<std::string>(keys);

        const auto _results = Stats::GetDescriptiveStatistics(_data, _keys);
        boost::python::dict results;
        Conversion::to_dict(_results, results);
        return results;
    }

    //
    // Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
    //
    boost::python::dict LinearRegression(const boost::python::list& xs, const boost::python::list& ys)
    {
        std::vector<double> _xs = Conversion::to_std_vector<double>(xs);
        std::vector<double> _ys = Conversion::to_std_vector<double>(ys);

        const auto _results = Stats::LinearRegression(_xs, _ys);
        boost::python::dict results;
        Conversion::to_dict(_results, results);
        return results;
    }

}
