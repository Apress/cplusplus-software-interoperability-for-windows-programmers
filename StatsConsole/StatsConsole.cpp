// StatsConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <vector>
#include <utility>

#include "MenuManager.h"

#include "Stats.h"
#include "DataManager.h"
#include "StatisticalTests.h"


namespace StatsConsole
{
    //
    // Utility class to manage named data sets
    //
    Stats::DataManager g_data_manager;

    //
    // Class to add a separator before and after some output
    //
    struct Output final
    {
        explicit Output(const std::string& description)
            : m_size(2 * m_separator.length() + description.length())
        { 
            std::cout << m_separator << description << m_separator << '\n'; 
        }

        ~Output()
        {  
            std::cout << std::string(m_size, '=') << '\n';  
        }

    private:
        std::string m_separator{ "====================" };
        std::size_t m_size{ 0 };
    };

    //
    // Get a name for the data set
    //
    std::string GetName()
    {
        std::cout << "Data set name> ";
        std::string name;
        std::getline(std::cin, name);
        return name;
    }

    //
    // Get a number
    // 
    double GetDouble(const std::string& prompt)
    {
        std::cout << prompt << "> ";
        std::string data;
        std::getline(std::cin, data);
        const double val = std::stod(data);
        return val;
    }

    //
    // Insert a named data set or default
    //
    void InsertDataSet(const std::vector<double>& data)
    {
        if (!data.empty())
        {
            std::string name = GetName();
            if (name.empty())
            {
                std::cout << "No name provided for this data set. Defaulting to 'test'.\n";
                name = "test";
            }
            g_data_manager.Add(name, data);
        }
        else
        {
            std::cout << "The data set is empty.\n";
        }
    }

    //
    // Display results key-value package
    //
    void OutputResults(const std::unordered_map<std::string, double>& results)
    {
        for (const auto& result : results)
        {
            std::cout << std::setw(15) << result.first << ":\t" << result.second << '\n';
        }
    }

    //
    // Menu functions
    //

    //
    // Input data via the console
    //
    bool OnEnterData(const std::string& prompt)
    {
        std::vector<double> data;
        std::cout << '\n' << prompt << ":(newline to stop)>\n";

        while (true)
        {
            std::string input;
            std::getline(std::cin, input);
            if (input.empty())
                break;
            try
            {
                const double val = std::stod(input);
                data.emplace_back(val);
            }
            catch (const std::exception& e)
            {
                std::cout << "Invalid input: " << e.what() << ". Please try again.\n";
            }

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please try again.\n";
            }
        }

        InsertDataSet(data);
        return true;
    }

    //
    // Read input from a file
    // 
    bool OnReadFile(const std::string& /* prompt */)
    {
        std::cout << "Full filename> ";
        std::string filename;
        std::getline(std::cin, filename);
        if (!filename.empty())
        {
            std::vector<double> data;
            std::ifstream inFile(filename);
            if (inFile.is_open())
            {
                std::string line;
                while (std::getline(inFile, line))
                {
                    std::stringstream ss(line);
                    data.emplace_back(std::stod(line));
                }
            }
            else
            {
                std::cout << "Could not open file: " << filename << ".\n";
            }

            InsertDataSet(data);
        }
        return true;
    }

    //
    // Output a list of data set names currently available
    //
    bool OnListDataSets(const std::string& prompt)
    {
        Output o(prompt);

        std::vector<Stats::DataSetInfo> data_sets = g_data_manager.ListDataSets();
        if (!data_sets.empty())
        {
            for (std::size_t i = 0; i < data_sets.size(); ++i)
            {
                const auto& data_set = data_sets.at(i);
                std::cout << " [" << i << "]\t" << data_set.first << " (count = " << data_set.second << ")\n";
            }
        }
        else
        {
            std::cout << "There are no data sets available.\n";
        }
        return true;
    }

    //
    // Output the data set
    //
    bool OnDisplayData(const std::string& prompt)
    {
        Output o(prompt);

        const std::string name = GetName();
        if (!name.empty())
        {
            std::vector<double> data = g_data_manager.GetDataSet(name);
            if(!data.empty())
            {
                for (std::size_t i = 0; i < data.size(); ++i)
                {
                    const auto& val = data.at(i);
                    std::cout << " [" << i << "]\t" << val << '\n';
                }
            }
            else
            {
                std::cout << "There is no data in the data set: " << name << ".\n";
            }
        }
        return true;
    }

    //
    // Retrieve descriptive statistics for the named data set
    //
    bool OnDescriptiveStats(const std::string& prompt)
    {
        Output o(prompt);

        const std::string name = GetName();
        if (!name.empty())
        {
            std::vector<double> data = g_data_manager.GetDataSet(name);
            if (!data.empty())
            {
                const auto results = Stats::GetDescriptiveStatistics(data);
                OutputResults(results);
            }
            else
            {
                std::cout << "There is no data in the data set: " << name << ".\n";
            }
        }
        return true;
    }

    //
    // Perform Linear regression
    //
    bool OnLinearRegression(const std::string& prompt)
    {
        Output o(prompt);

        const std::string indep_name = GetName();
        const std::string dep_name = GetName();

        if (!indep_name.empty() && !dep_name.empty())
        {
            std::vector<double> xs = g_data_manager.GetDataSet(indep_name);
            std::vector<double> ys = g_data_manager.GetDataSet(dep_name);

            if (xs.empty())
            {
                std::cout << "There is no data in the data set: " << indep_name << ".\n";
            }
            else if (ys.empty())
            {
                std::cout << "There is no data in the data set: " << dep_name << ".\n";
            }
            else
            {
                std::cout << "Estimated Coefficients:\n";
                const auto results = Stats::LinearRegression(xs, ys);
                OutputResults(results);
            }
        }
        return true;
    }

    //
    // Perform a summary data t-test
    //
    bool OnSummaryDataTtest(const std::string& prompt)
    {
        Output o(prompt);

        const double mu0 = GetDouble("Population mean: mu0");
        const double x_bar = GetDouble("Sample mean: x-bar");
        const double sx = GetDouble("Sample stdev: s");
        const double n = GetDouble("Sample size: n");

        Stats::TTest test(mu0, x_bar, sx, n);
        const bool success = test.Perform();
        if (success)
        {
            const auto results = test.Results();
            OutputResults(results);
        }
        else
        {
            std::cout << "An error occurred performing the t-test.\n";
        }
        return true;
    }

    //
    // Perform one-sample t-test
    //
    bool OnOneSampleTtest(const std::string& prompt)
    {
        Output o(prompt);

        const double mu0 = GetDouble("mu0");
        const std::string x1_name = GetName();

        if (!x1_name.empty())
        {
            std::vector<double> x1 = g_data_manager.GetDataSet(x1_name);
            if (x1.empty())
            {
                std::cout << "There is no data in the data set: " << x1_name << ".\n";
            }
            else
            {
                Stats::TTest test(mu0, x1);
                const bool success = test.Perform();
                if (success)
                {
                    const auto results = test.Results();
                    OutputResults(results);
                }
                else
                {
                    std::cout << "An error occurred performing the t-test.\n";
                }
            }
        }
        return true;
    }

    //
    // Perform two-sample t-test
    //
    bool OnTwoSampleTtest(const std::string& prompt)
    {
        Output o(prompt);

        const std::string x1_name = GetName();
        const std::string x2_name = GetName();

        if (!x1_name.empty() && !x2_name.empty())
        {
            std::vector<double> x1 = g_data_manager.GetDataSet(x1_name);
            std::vector<double> x2 = g_data_manager.GetDataSet(x2_name);

            if (x1.empty())
            {
                std::cout << "There is no data in the data set: " << x1_name << ".\n";
            }
            else if (x2.empty())
            {
                std::cout << "There is no data in the data set: " << x2_name << ".\n";
            }
            else
            {
                Stats::TTest test(x1, x2);
                const bool success = test.Perform();
                if (success)
                {
                    const auto results = test.Results();
                    OutputResults(results);
                }
                else
                {
                    std::cout << "An error occurred performing the t-test.\n";
                }
            }
        }
        return true;
    }

    //
    // Perform a summary data F-test
    //
    bool OnSummaryDataFtest(const std::string& prompt)
    {
        Output o(prompt);

        const double sx1 = GetDouble("Sample std dev 1: sx1");
        const double sx2 = GetDouble("Sample std dev 2: sx2");
        const double n1 = GetDouble("Sample size 1: n1");
        const double n2 = GetDouble("Sample size 2: n2");

        Stats::FTest test(sx1, sx2, n1, n2);
        const bool success = test.Perform();
        if (success)
        {
            const auto results = test.Results();
            OutputResults(results);
        }
        else
        {
            std::cout << "An error occurred performing the F-test.\n";
        }
        return true;
    }

    //
    // Perform two-sample F-test
    //
    bool OnTwoSampleFtest(const std::string& prompt)
    {
        Output o(prompt);

        const std::string x1_name = GetName();
        const std::string x2_name = GetName();

        if (!x1_name.empty() && !x2_name.empty())
        {
            std::vector<double> x1 = g_data_manager.GetDataSet(x1_name);
            std::vector<double> x2 = g_data_manager.GetDataSet(x2_name);

            if (x1.empty())
            {
                std::cout << "There is no data in the data set: " << x1_name << ".\n";
            }
            else if (x2.empty())
            {
                std::cout << "There is no data in the data set: " << x2_name << ".\n";
            }
            else
            {
                Stats::FTest test(x1, x2);
                const bool success = test.Perform();
                if (success)
                {
                    const auto results = test.Results();
                    OutputResults(results);
                }
                else
                {
                    std::cout << "An error occurred performing the F-test.\n";
                }
            }
        }
        return true;
    }

    //
    // Exit from the console application
    // 
    bool OnClose(const std::string& prompt)
    {
        std::cout << prompt << '\n';
        return false;
    }

    //
    // Initialise menu items
    //
    MenuItems mainMenu =
    {
        {"1", {"Enter Console Data",		OnEnterData } },
        {"2", {"Load Data from File",		OnReadFile } },
        {"3", {"List Data Sets",			OnListDataSets } },
        {"4", {"Display Data",				OnDisplayData } },
        {"5", {"Descriptive Statistics",	OnDescriptiveStats } },
        {"6", {"Linear Regression",	        OnLinearRegression } },
        {"7", {"Summary Data T-Test",	    OnSummaryDataTtest } },
        {"8", {"One-sample T-Test",	        OnOneSampleTtest } },
        {"9", {"Two-sample T-Test",	        OnTwoSampleTtest } },
        {"10", {"Summary Data F-Test",	    OnSummaryDataFtest } },
        {"11", {"Two-sample F-Test",	    OnTwoSampleFtest } },
        {"12", {"Quit",						OnClose } }
    };
}

//
// Main entry point
//
int main()
{
	using namespace StatsConsole;

    const MenuManager& theMenuManager = MenuManager::Instance(mainMenu);

    for (;;)
    {
        theMenuManager.PrintMenu();
        if (!theMenuManager.ProcessSelection())
            break;
    }

	return 0;
}
