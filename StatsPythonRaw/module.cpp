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

#include <iostream>
#include <iomanip>

#include "Functions.h"

//
// Python module definition and exported functions
//
static PyMethodDef StatsPythonRaw_methods[] =
{
    // The first property is the name exposed to Python, 
    // The second is the C++ function with the implementation
    // METH_O means it takes a single PyObject argument
    {   
        "DescriptiveStatistics", 
        (PyCFunction)API::DescriptiveStatistics, 
        METH_VARARGS,
        "Retrieve a package of descriptive statistics for the input data." 
    },

    {   
        "LinearRegression", 
        (PyCFunction)API::LinearRegression,
        METH_VARARGS, 
        "Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)." 
    },

    {   
        "SummaryDataTTest", 
        (PyCFunction)API::SummaryDataTTest,
        METH_VARARGS, 
        "Summary data: population mean, sample mean, sample standard deviation, sample size." 
    },

    {   
        "OneSampleTTest", 
        (PyCFunction)API::OneSampleTTest,
        METH_VARARGS, 
        "One-sample: population mean, sample." 
    },

    {
        "TwoSampleTTest",
        (PyCFunction)API::TwoSampleTTest,
        METH_VARARGS,
        "Two-sample: the underlying boost implementation assumes equal variances."
    },

    // Terminate the array with an object containing nulls.
    { nullptr, nullptr, 0, nullptr }
};

static PyModuleDef StatsPythonRaw_module = {
    PyModuleDef_HEAD_INIT,
    "StatsPythonRaw",                       // Module name to use with Python import statements
    "Python C++ StatsLib wrapper",          // Module description
    0,
    StatsPythonRaw_methods                  // Structure that defines the methods of the module
};

PyMODINIT_FUNC PyInit_StatsPythonRaw() 
{
    return PyModule_Create(&StatsPythonRaw_module);
}
