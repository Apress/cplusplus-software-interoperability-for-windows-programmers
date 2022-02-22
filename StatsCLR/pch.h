// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H


#define STATS_TRY try{

#define STATS_CATCH \
    }catch(const std::exception& e){  \
        System::String^ s = gcnew System::String(e.what());\
        System::InvalidOperationException^ se = gcnew System::InvalidOperationException(s);\
        throw se;  \
    }


#endif //PCH_H
