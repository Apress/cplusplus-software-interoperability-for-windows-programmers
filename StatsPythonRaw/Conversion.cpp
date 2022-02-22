// Conversion.cpp: type conversion functions
//
#include "Conversion.h"

//
// Conversion functions
//
namespace Conversion
{
    //
    // Convert a PyObject into a vector of doubles
    //
    std::vector<double> ObjectToVector(PyObject* o)
    {
        std::size_t size = PyList_Size(o);
        std::vector<double> data;

        for (std::size_t i = 0; i < size; ++i)
        {
            double d = PyFloat_AsDouble(PyList_GetItem(o, i));
            data.emplace_back(d);
        }
        return data;
    }

    //
    // Convert a PyObject into a vector of strings
    //
    std::vector<std::string> ObjectToStringVector(PyObject* o)
    {
        std::vector<std::string> strings;
        if (o != nullptr)
        {
            std::size_t size = PyList_Size(o);
            for (std::size_t i = 0; i < size; ++i)
            {
                std::string s((char*)PyUnicode_1BYTE_DATA(PyList_GetItem(o, i)));
                strings.emplace_back(s);
            }
        }
        return strings;
    }

    //
    // Convert a map into a PyObject
    //
    PyObject* MapToObject(const std::unordered_map<std::string, double>& results)
    {
        PyObject* dict = PyDict_New();

        for (const auto& result : results)
        {
            PyObject* key = PyUnicode_FromString(result.first.c_str());
            PyObject* val = PyFloat_FromDouble(result.second);

            int success = PyDict_SetItem(dict, key, val);
            Py_XDECREF(key);
            Py_XDECREF(val);
            if (success < 0)
            {
                Py_XDECREF(dict);
                return nullptr;
            }
        }
        return dict;
    }
}
