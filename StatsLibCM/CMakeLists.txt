cmake_minimum_required(VERSION 3.15)
project(StatsLibCM)

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -std=c++17 -g -std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -std=c++17 -std=c++17")

set(BOOST_ROOT "D:/Development/Libraries/boost_1_76_0/")
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.76.0 ) 

if(Boost_FOUND)
    #target_link_libraries(progname Boost::filesystem Boost::regex)
endif()

# Define GNU standard installation directories
include( GNUInstallDirs )

# Bring in the Boost headers and headers from the project
include_directories(${BOOST_ROOT} "D:/Development/Projects/C++/SoftwareInteroperability/Common/include/")
# 
# Manually add the sources using the set command as follows:
# set(SOURCES src/wxy.cpp src/xyz.cpp)

# Wildcard additions:
file(GLOB SOURCES "D:/Development/Projects/C++/SoftwareInteroperability/Common/source/*.cpp")
file(GLOB HEADERS "D:/Development/Projects/C++/SoftwareInteroperability/Common/include/*.h")

# Generate the static library from the sources
add_library(StatsLibCM STATIC ${SOURCES} ${HEADERS})

target_include_directories(StatsLibCM PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

