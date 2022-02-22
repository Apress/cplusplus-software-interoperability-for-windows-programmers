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
#include <string>
#include <utility>
#include <unordered_map>


namespace Stats
{
    // Base class for statistical testing: tTest, zTest, fTest ...
    class STATSDLL_API StatisticalTest
    {
    public:
        // Construction
        StatisticalTest() = default;

        // Destructor
        virtual ~StatisticalTest() = default;

        // Perform the statistical test
        virtual bool Perform() = 0;

        // Retrieve the results
        std::unordered_map<std::string, double> Results() const;

        // Move constructor   
        StatisticalTest(StatisticalTest&& other) = default;

        // Move assignment operator   
        StatisticalTest& operator=(StatisticalTest&& other) = default;

        // Copy constructor   
        StatisticalTest(const StatisticalTest& other) = default;

        // Copy assignment operator   
        StatisticalTest& operator=(const StatisticalTest& other) = default;

    protected:
        // Collection of named results
        std::unordered_map<std::string, double> m_results;
    };

    // T-Test
    class STATSDLL_API TTest final : public StatisticalTest
    {
        enum class STATSDLL_API TestType { Unknown, OneSample, TwoSample, NoSample };

    public:
        // Summary data: population mean, sample mean, sample standard deviation, sample size.
        TTest(double mu0, double x_bar, double sx, double n);

        // One-sample: population mean, sample.
        TTest(double mu0, const std::vector<double>& x1);

        // Two-sample
        TTest(const std::vector<double>& x1, const std::vector<double>& x2);

        // Move constructor   
        TTest(TTest && other) = default;

        // Move assignment operator   
        TTest& operator=(TTest && other) = default;

        // Copy constructor   
        TTest(const TTest & other) = default;

        // Copy assignment operator   
        TTest& operator=(const TTest & other) = default;

        // Default destruction
        virtual ~TTest() = default;

        // Perform the statistical test
		bool Perform() override;

    private:
        // mu0 unknown population mean
        double m_mu0{ 0.0 };

        // sample mean
        double m_x_bar{ 0.0 };

        // sample standard deviation
        double m_sx{ 0.0 };

        // sample size
        double m_n{ 0.0 };

        // Sample 1
        std::vector<double> m_x1;

        // Sample 2
        std::vector<double> m_x2;

        // Test type
        TestType m_test_type{ TestType::Unknown };
    };

    // F-Test
    class STATSDLL_API FTest final : public StatisticalTest
    {
        enum class STATSDLL_API TestType { Unknown, FromData, TwoSample};

    public:
        // Summary data: sample std dev 1, sample std dev 2, sample size 1, sample size 2.
        FTest(double sx1, double sx2, double n1, double n2);

        // Two-sample
        FTest(const std::vector<double>& x1, const std::vector<double>& x2);

        // Move constructor   
        FTest(FTest&& other) = default;

        // Move assignment operator   
        FTest& operator=(FTest&& other) = default;

        // Copy constructor   
        FTest(const FTest& other) = default;

        // Copy assignment operator   
        FTest& operator=(const FTest & other) = default;

        // Default destruction
        virtual ~FTest() = default;

        // Perform the statistical test
        bool Perform() override;

    private:
        // sample standard deviation 1
        double m_sx1{ 0.0 };

        // sample standard deviation 2
        double m_sx2{ 0.0 };

        // sample size 1
        double m_n1{ 0.0 };

        // sample size 2
        double m_n2{ 0.0 };

        // Sample 1
        std::vector<double> m_x1;

        // Sample 2
        std::vector<double> m_x2;

        // Test type
        TestType m_test_type{ TestType::Unknown };
    };
}
