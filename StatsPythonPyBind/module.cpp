#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <sstream>

#include "Stats.h"
#include "DescriptiveStatistics.h"
#include "StatisticalTests.h"
#include "DataManager.h"

namespace py = pybind11;

//
// APIs
//
std::unordered_map<std::string, double> SummaryDataTTest(double mu0, double mean, double sd, double n)
{
    Stats::TTest test(mu0, mean, sd, n);
    test.Perform();

    return test.Results();
}

std::unordered_map<std::string, double> OneSampleTTest(double mu0, const std::vector<double>& data)
{
    Stats::TTest test(mu0, data);
    test.Perform();

    return test.Results();
}

std::unordered_map<std::string, double> TwoSampleTTest(const std::vector<double>& x1, const std::vector<double>& x2)
{
    Stats::TTest test(x1, x2);
    test.Perform();

    return test.Results();
}

double SampleStandardDeviation(const std::vector<double>& data)
{
    using namespace Stats::DescriptiveStatistics;
    return StandardDeviation(data, VarianceType::Sample);
}

namespace {

    // Provide a string representation of this object
    std::string to_string(const Stats::DataManager& obj)
    {
        std::ostringstream out;
        std::vector<Stats::DataSetInfo> data_sets = obj.ListDataSets();
        if (!data_sets.empty())
        {
            for (std::size_t i = 0; i < data_sets.size(); ++i)
            {
                const auto& data_set = data_sets.at(i);
                out << "\n [" << i << "]\t" << data_set.first << " (count = " << data_set.second << ")";
            }
        }
        else
        {
            out << "There are no data sets available.";
        }
        return out.str();
    }
}

// Module definition
PYBIND11_MODULE(StatsPythonPyBind, m) 
{
    m.def(
        "DescriptiveStatistics",
        &Stats::GetDescriptiveStatistics, py::arg("data"), py::arg("keys") = std::vector<std::string>(),
        R"pbdoc(Retrieve a package of descriptive statistics for the input data.)pbdoc"
    )
    .def(
        "LinearRegression",
        &Stats::LinearRegression,
        R"pbdoc(Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1).)pbdoc"
    )
    .def(
        "SummaryDataTTest",
        &SummaryDataTTest,
        R"pbdoc(No-sample: TTest from summary data.)pbdoc"
    )
    .def(
        "OneSampleTTest",
        &OneSampleTTest,
        R"pbdoc(One-sample: single unknown population mean m; the population standard deviation s is unknown.)pbdoc"
    )
    .def(
        "TwoSampleTTest",
        &TwoSampleTTest,
        R"pbdoc(Two-sample: the underlying boost implementation assumes equal variances.)pbdoc"
    )
    .def(
        "Mean",
        &Stats::DescriptiveStatistics::Mean,
        R"pbdoc(Compute the mean of the data.)pbdoc"
    )
    .def(
        "StdDev",
        &Stats::DescriptiveStatistics::StandardDeviation,
        py::arg("data"), py::arg("VarianceType"),
        R"pbdoc(Compute the standard deviation of the data.)pbdoc"
    )
    .def(
        "StdDevS",
        &SampleStandardDeviation,
        R"pbdoc(Compute the standard deviation of the data.)pbdoc"
    )
    ;
    
    // This is the underlying TTest class; no wrapper required
    py::enum_<Stats::DescriptiveStatistics::VarianceType>(m, "VarianceType")
        .value("Sample", Stats::DescriptiveStatistics::VarianceType::Sample)
        .value("Population", Stats::DescriptiveStatistics::VarianceType::Population)
        ;

    py::class_<Stats::TTest>(m, "TTest")
        .def(py::init<double, double, double, double>(), 
            "Summary data: population mean, sample mean, sample standard deviation, sample size.")
        .def(py::init<double, const std::vector<double>& >(), "One-sample: population mean, sample.")
        .def(py::init<const std::vector<double>&, const std::vector<double>& >(), 
            "Two-sample: the underlying boost implementation assumes equal variances.")
        .def("Perform", &Stats::TTest::Perform, "Perform the t-test.")
        .def("Results", &Stats::TTest::Results, "Retrieve the results.")
        .def("__repr__",
            [](const Stats::TTest&) {
                return "<example.TTest>";
            }
    );

    // This is the underlying DataManager class; no wrapper required
    py::class_<Stats::DataManager>(m, "DataManager")
        .def(py::init<>(), "Default constructor.")
        .def("CountDataSets", &Stats::DataManager::CountDataSets, 
            "Retrieve the number of data sets currently available.")
        .def("Add", &Stats::DataManager::Add, "Add the named data set to the collection.")
        .def("GetDataSet", &Stats::DataManager::GetDataSet, 
            "Retrieve the named data set from the collection.")
        .def("ListDataSets", &Stats::DataManager::ListDataSets, 
            "Retrieve the names of the data sets in the current collection.")
        .def("ClearDataSets", &Stats::DataManager::ClearDataSets, 
            "Clear the data sets in the collection.")
        .def("__repr__",
            [](const Stats::DataManager& a) {
                return "<DataManager> containing: " + to_string(a);
            }
    );

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
