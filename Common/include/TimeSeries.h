#pragma once

#ifdef DYNAMIC
#   ifdef STATSDLL_EXPORTS
#       define STATSDLL_API __declspec(dllexport)
#   else
#       define STATSDLL_API __declspec(dllimport)
#   endif
#else
#   define STATSDLL_API
#endif

#ifdef _MSC_VER
#pragma warning( disable: 4251 ) // warning C4251: 'stl': class '...' needs to have dll-interface to be used by clients of class '...'
#endif

#include <vector>

namespace Stats
{
	using Date = long;

	class STATSDLL_API TimeSeries final
	{
    public:
        // Construction
        TimeSeries() = default;

        // Construction from vectors
        TimeSeries(const std::vector<Stats::Date>& dates, const std::vector<double>& observations);

        // Destructor
        ~TimeSeries() = default;

        // Move constructor   
        TimeSeries(TimeSeries && other) = default;

        // Move assignment operator   
        TimeSeries& operator=(TimeSeries&& other) = default;

        // Copy constructor   
        TimeSeries(const TimeSeries& other) = default;

        // Copy assignment operator   
        TimeSeries& operator=(const TimeSeries& other) = default;

        // Compute a simple moving average of size = window
        std::vector<double> MovingAverage(int window) const;

    private:
        // Time series
        std::vector<Stats::Date> m_dates;
        std::vector<double> m_observations;
	};
}
