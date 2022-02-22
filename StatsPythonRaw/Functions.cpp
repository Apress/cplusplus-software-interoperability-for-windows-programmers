// Functions.cpp: api functions
//
#include "Conversion.h"
#include "Functions.h"

#undef _USRDLL
#include "Stats.h"
#include "DescriptiveStatistics.h"
#include "DataManager.h"
#include "StatisticalTests.h"
#define _USRDLL


//
// APIs
//
namespace API
{
    //
    // Retrieve a package of descriptive statistics for the input data
    //
    PyObject* DescriptiveStatistics(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY

        PyObject* data = nullptr;
        PyObject* keys = nullptr;

        if (!PyArg_ParseTuple(args, "O|O", &data, &keys)) {
            return nullptr;
        }

        std::vector<double> _data = Conversion::ObjectToVector(data);
        std::vector<std::string> _keys = Conversion::ObjectToStringVector(keys);

        std::unordered_map<std::string, double> results = Stats::GetDescriptiveStatistics(_data, _keys);
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
    //
    PyObject* LinearRegression(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        PyObject* xs = nullptr;
        PyObject* ys = nullptr;

        if (!PyArg_ParseTuple(args, "OO", &xs, &ys)) {
            return nullptr;
        }

        std::vector<double> _xs = Conversion::ObjectToVector(xs);
        std::vector<double> _ys = Conversion::ObjectToVector(ys);
        std::unordered_map<std::string, double> results = Stats::LinearRegression(_xs, _ys);
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Wrapper function for a t-test with summary data (no sample)
    //
    PyObject* SummaryDataTTest(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        double mu0{ 0.0 };
        double mean{ 0.0 };
        double sd{ 0.0 };
        double n{ 0.0 };

        if (!PyArg_ParseTuple(args, "dddd", &mu0, &mean, &sd, &n)) {
            return nullptr;
        }

        Stats::TTest test(mu0, mean, sd, n);
        test.Perform();

        const auto results = test.Results();
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Wrapper function for a one-sample t-test with population mean
    //
    PyObject* OneSampleTTest(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        double mu0{ 0.0 };
        PyObject* o = nullptr;

        if (!PyArg_ParseTuple(args, "dO", &mu0, &o)) {
            return nullptr;
        }

        std::vector<double> data = Conversion::ObjectToVector(o);

        Stats::TTest test(mu0, data);
        test.Perform();

        const auto results = test.Results();
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Wrapper function for a two-sample t-test
    //
    PyObject* TwoSampleTTest(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        PyObject* x1 = nullptr;
        PyObject* x2 = nullptr;

        if (!PyArg_ParseTuple(args, "OO", &x1, &x2)) {
            return nullptr;
        }

        std::vector<double> _x1 = Conversion::ObjectToVector(x1);
        std::vector<double> _x2 = Conversion::ObjectToVector(x2);

        Stats::TTest test(_x1, _x2);
        test.Perform();

        const auto results = test.Results();
        return Conversion::MapToObject(results);
        STATS_CATCH
    }
}
