// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#define BOOST_DISABLE_PRAGMA_MESSAGE	// D:\Development\Libraries\boost_1_76_0\boost\bind.hpp(41): message : 
										// The practice of declaring the Bind placeholders (_1, _2, ...) in the global namespace
										// is deprecated. Please use <boost/bind/bind.hpp> + using namespace boost::placeholders, 
										// or define BOOST_BIND_GLOBAL_PLACEHOLDERS to retain the current behavior. 
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>


#endif //PCH_H
