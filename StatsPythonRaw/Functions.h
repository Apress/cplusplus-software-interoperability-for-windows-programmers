#pragma once

#define PY_SSIZE_T_CLEAN
//
// Prevent linking against pythonXY_d.lib
//
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

namespace API
{
    // Retrieve a package of descriptive statistics for the input data
    PyObject* DescriptiveStatistics(PyObject* /* unused module reference */, PyObject* args);

    // Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
    PyObject* LinearRegression(PyObject* /* unused module reference */, PyObject* args);

    // Wrapper function for a t-test with summary input data (no sample)
    PyObject* SummaryDataTTest(PyObject* /* unused module reference */, PyObject* args);

    // Wrapper function for a one-sample t-test with known population mean
    PyObject* OneSampleTTest(PyObject* /* unused module reference */, PyObject* args);

    // Wrapper function for a two-sample t-test
    PyObject* TwoSampleTTest(PyObject* /* unused module reference */, PyObject* args);
}