# SoftwareInteroperability
Companion projects to _C++ Software Interoperability for Windows Programmers._

_SoftwareInteroperability_ is a set of projects that form a companion to the book: _C++ Software Interoperability for Windows Programmers: Connecting C++ code to C#, R and Python clients._

## Introduction
The purpose of the projects is to demonstrate how to connect a simple C++ codebase to C# (and .NET), R and Python. The C++ codebase consists of a small library of statistics functions (descriptive statistics, simple linear regression, and hypothesis testing). The projects demonstrate building wrapper components that expose the C++ functionality to other client languages.

## Contents
A brief description of the contents of each directory is as follows:

* __Common__ contains two subdirectories: \include and \source. These contain the common header and source files that form the core of the C++ statistics library.
* __Data__ contains a number of small datasets that we use at various points for testing.
* __StatsATLCOM__ is a side-project that illustrates an alternative approach to connecting C++ to .NET, using COM.
* __StatsCLR.UnitTests__ is a C# unit test library that tests the basic statistics functionality from .NET.
* __StatsCLR__ is a C++/CLI wrapper. This component connects the C++ static library (StatsLib) to C# (and .NET).
* __StatsClient__ is a basic C# console application that exercises the functionality from the statistics library via the StatsCLR wrapper component with a minimal user interface.
* __StatsConsole__ is a Windows console application. This application demonstrates the basic functionality of the statistics library with a minimal user interface.
* __StatsConsoleCB__ is a Windows console application project using CodeBlocks. This is useful to debug C++ code using gdb on Windows.
* __StatsDll__ is a dynamic-link library version of the statistics library.
* __StatsExcel__ is a C# library project. This component connects Excel to the StatsCLR wrapper component and allows Excel to use the functionality available in the statistics library.
* __StatsLib__ is a static link library version of the statistics library. Both this and the previous component share the same C++ source code.
* __StatsLibCB__ is the CodeBlocks project that we use for building the R/RStudio ABI compatible static library. 
* __StatsLibCM__ is a CMake equivalent of the StatsLibCB project. It allows building the library from Visual Studio in place of CodeBlocks.
* __StatsLibTest__ is a Windows console application. We use this specifically as a unit-testing application based on GoogleTest.
* __StatsPython__ is a Visual Studio Code Python project containing a number of scripts that use the statistics library functionality.
* __StatsPythonBoost__ is a Boost.Python wrapper. This component connects C++ code to Python.
* __StatsPythonPyBind__ is a PyBind wrapper. This component connects C++ code to Python.
* __StatsPythonRaw__ is a CPython wrapper. This component connects C++ code to Python. The reason for having three components that do essentially the same thing is to cover different approaches to connecting C++ to Python.
* __StatsR__ is the Rcpp wrapper, built using Rtools via RStudio. 
* __StatsViewer__ is a Windows MFC application. This application is used to demonstrate using the functionality available in the statistics library in a GUI application.

## Features
The wrapper components make use of:
* C++/CLI for connecting to C# (.NET).
* Rcpp for connecting to R.
* Boost.Python and PyBind for connecting to Python.
