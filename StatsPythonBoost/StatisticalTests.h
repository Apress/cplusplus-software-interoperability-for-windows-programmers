#pragma once

#undef _USRDLL
#include "..\Common\include\StatisticalTests.h"
#define _USRDLL

#include "Conversion.h"


namespace API
{
	namespace StatisticalTests
	{
        // Summary data: population mean, sample mean, sample standard deviation, sample size.
        boost::python::dict SummaryDataTTest(
            const boost::python::object& mu0,
            const boost::python::object& mean,
            const boost::python::object& sd,
            const boost::python::object& n
        );

        // One-sample: population mean, sample.
        boost::python::dict OneSampleTTest(const boost::python::object& mu0, const boost::python::list& x1);

        // Two-sample
        boost::python::dict TwoSampleTTest(const boost::python::list& x1, const boost::python::list& x2);

        // StudentTTest wrapper class
        class StudentTTest
        {
        public:
            ~StudentTTest() = default;

            StudentTTest(
                const boost::python::object& mu0,
                const boost::python::object& mean,
                const boost::python::object& sd,
                const boost::python::object& n
            )
                : _test(boost::python::extract<double>(mu0),
                    boost::python::extract<double>(mean),
                    boost::python::extract<double>(sd),
                    boost::python::extract<double>(n))
            {
            }

            StudentTTest(const boost::python::object& mu0, const boost::python::list& x1)
                : _test(boost::python::extract<double>(mu0), Conversion::to_std_vector<double>(x1))
            {
            }

            StudentTTest(const boost::python::list& x1, const boost::python::list& x2)
                : _test(Conversion::to_std_vector<double>(x1), Conversion::to_std_vector<double>(x2))
            {
            }

            bool Perform()
            {
                return _test.Perform();
            }

            boost::python::dict Results() const
            {
                boost::python::dict results;
                const auto _results = _test.Results();
                Conversion::to_dict(_results, results);
                return results;
            }

        private:
            Stats::TTest _test;
        };
	}
}
