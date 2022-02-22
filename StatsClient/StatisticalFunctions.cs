using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using StatsCLR;

namespace StatsClient
{
    public class StatisticalFunctions
    {
        public static void DisplayDataSets(List<Tuple<string, ulong>> dataSets)
        {
            Console.WriteLine("The data sets are:");
            foreach (var dataSet in dataSets)
            {
                Console.WriteLine(string.Format("Name: {0}\tElements: {1}", dataSet.Item1, dataSet.Item2));
            }
            Console.WriteLine("");
        }

        public static void OutputResults(Dictionary<string, double> results)
        {
            foreach (var result in results)
            {
                Console.WriteLine(string.Format("{0}\t{1}", result.Key.ToString(), result.Value.ToString()));
            }
            Console.WriteLine("");
        }

        // Example session
        public static void Run()
        {
            Console.Clear();

            StatsCLR.DataManager dataManager = new DataManager();

            List<double> xs = new List<double> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            List<double> ys = new List<double> { 1, 3, 2, 5, 7, 8, 8, 9, 10, 12 };

            try
            {
                if (dataManager.Add("xs", xs))
                {
                    Console.WriteLine("Added data set \'{0}\' to the DataManager.", "xs");
                }

                if (dataManager.Add("ys", ys))
                {
                    Console.WriteLine("Added data set \'{0}\' to the DataManager.", "ys");
                }

                ulong count = dataManager.CountDataSets();
                Console.WriteLine(string.Format("There are: {0} data sets in the DataManager", count));

                List<Tuple<string, ulong>> dataSets = dataManager.ListDataSets();
                DisplayDataSets(dataSets);

                {
                    Console.WriteLine("Descriptive Statistics for data set: xs");
                    List<double> _xs = dataManager.GetDataSet("xs");
                    List<string> keys = new List<string>();
                    keys.Add("Mean");
                    keys.Add("StdDev.S");

                    Dictionary<string, double> results = Statistics.DescriptiveStatistics(_xs, keys);
                    //OutputResults(results);

                    results = Statistics.DescriptiveStatistics(_xs);
                    OutputResults(results);
                }

                {
                    Console.WriteLine("Perform simple linear regression: y ~ x.");
                    List<double> _xs = dataManager.GetDataSet("xs");
                    List<double> _ys = dataManager.GetDataSet("ys");

                    Dictionary<string, double> results = Statistics.LinearRegression(_xs, _ys);
                    OutputResults(results);

                    Console.WriteLine("Estimated Coefficients:");
                    Console.WriteLine(string.Format("b0 = {0:0.00}\nb1 = {1:0.00}", results["b0"], results["b1"]));
                    Console.WriteLine(string.Format("The formula is: y = {0:0.00} + {1:0.00}x", results["b0"], results["b1"]));
                }

                {
                    Console.WriteLine("Perform a t-test using summary data.");
                    TTest test = new TTest(5, 9.261460, 0.2278881e-01, 195);
                    bool succeeded = test.Perform();
                    if (succeeded)
                    {
                        Dictionary<string, double> results = test.Results();
                        OutputResults(results);
                    }
                }

                {
                    Console.WriteLine("Perform a two-sample t-test.");

                    List<double> _x1 = dataManager.GetDataSet("xs");
                    List<double> _x2 = dataManager.GetDataSet("ys");

                    TTest test = new TTest(_x1, _x2);
                    bool succeeded = test.Perform();
                    if (succeeded)
                    {
                        Dictionary<string, double> results = test.Results();
                        OutputResults(results);
                    }
                }
            }
            catch (System.Exception e)
            {
                Console.WriteLine(e.ToString());
            }

            Console.WriteLine("Press any key to continue ...");
            Console.ReadKey();
        }
    }
}
