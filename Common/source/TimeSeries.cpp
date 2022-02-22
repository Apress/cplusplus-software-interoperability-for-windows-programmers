// TimeSeries.cpp : Defines the functions for the entity.
//

#include <stdexcept>
#include <cmath>

#include "TimeSeries.h"

namespace Stats
{
	//
	// Construction from vectors
	//
	TimeSeries::TimeSeries(const std::vector<Stats::Date>& dates, const std::vector<double>& observations)
	{
		const std::size_t num_dates = dates.size();
		const std::size_t num_observations = observations.size();

		if (num_dates != num_observations)
		{
			throw std::length_error("There must be the same number of dates and observations.");
		}

		m_dates = dates;
		m_observations = observations;
	}

	//
	// Compute a simple moving average of size = window
	//
	std::vector<double> TimeSeries::MovingAverage(int window) const
	{
		const int size = static_cast<int>(m_observations.size());
		if (window <= 1 || window > size)
		{
			throw std::logic_error("The window size must be greater than 1 and less than the number of observations.");
		}

		std::vector<double> result(size, 0.0);
		double sum = 0;
		for (int i = 0; i < size; ++i)
		{
			sum += m_observations[i];
			if (i >= window)
			{
				sum -= m_observations[i - window];
			}

			if (i < window - 1)
			{
				result[i] = NAN;
			}
			else
			{
				result[i] = sum / std::min(i + 1, window);
			}
		}
		return result;
	}
}
