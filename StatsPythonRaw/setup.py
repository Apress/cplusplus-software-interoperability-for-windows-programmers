#
# https://docs.python.org/3/distutils/setupscript.html
#
from setuptools import setup, Extension

sfc_module = Extension(
    'StatsPythonRaw', 
    sources = ['module.cpp'],
    library_dirs=['../x64/Debug'],
    libraries=['StatsLib']
    )

setup(
    name='StatsPythonRaw',
    version='1.0',
    description='Python Package with StatsLib C++ extension',
    ext_modules=[sfc_module]
)
