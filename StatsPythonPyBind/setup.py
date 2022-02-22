from setuptools import setup, Extension
import pybind11


pyb_module = Extension(
    'StatsPythonPyBind',
    sources=['module.cpp'],
    include_dirs=['D:/Development/Projects/C++/SoftwareInteroperability/Common/include', pybind11.get_include()],
    library_dirs=['D:/Development/Projects/C++/SoftwareInteroperability/x64/Release'],
    libraries=['StatsLib'],
    language='c++',
    extra_compile_args=['-std=c++17','-Wall'],
    )

setup(
    name='StatsPythonPyBind',
    version='1.0',
    description='Python package with StatsLib C++ extension (PyBind11)',
    ext_modules=[pyb_module],
)
