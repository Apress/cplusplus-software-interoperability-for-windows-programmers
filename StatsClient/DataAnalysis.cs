using System;
using System.Globalization;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;

using Accord.Controls;

using StatsCLR;

namespace StatsClient
{
    public static class DataAnalysis
    {
        public static void Run()
        {
            Console.Clear();

            // Read in the OHLC dataset
            string filename = @"..\..\..\Data\eurusd-daily-ohlc.csv";
            Accord.IO.CsvReader reader = new Accord.IO.CsvReader(filename, true);

            System.Data.DataTable dt = reader.ToTable();
            System.DateTime[] date = dt.AsEnumerable()
                        .Select(row => Convert.ToDateTime(row.Field<string>("Date"), System.Globalization.CultureInfo.InvariantCulture)).ToArray();
            double[] close = dt.AsEnumerable()
                        .Select(row => Convert.ToDouble(row.Field<string>("Close"), System.Globalization.CultureInfo.InvariantCulture)).ToArray();
            double[] returns = dt.AsEnumerable()
                        .Select(row => Convert.ToDouble(row.Field<string>("DailyReturn"), System.Globalization.CultureInfo.InvariantCulture)).ToArray();

            var closePriceLineChart = DataSeriesBox.Show(date, close).SetTitle("EUR/USD Exchange Rate");

            // Check the distribution of daily returns
            List<double> _returns = new List<double>(returns);
            List<string> stats = new List<string>() { "Maximum", "Mean", "Median", "Minimum", "StdDev.S", "Q1", "Q3" };
            var results = Statistics.DescriptiveStatistics(_returns, stats);
            double returnMax = results["Maximum"];
            double returnMean = results["Mean"];
            double returnMedian = results["Median"];
            double returnMin = results["Minimum"];
            double returnStdDev = results["StdDev.S"];
            double returnQ1 = results["Q1"];
            double returnQ3 = results["Q3"];

            /*
            // Compare to Accord.Net
            double[] quantiles = Accord.Statistics.Measures.Quantiles(returns, new double[] { 0.25, 0.5, 0.75 } );

            Console.WriteLine("-- DailyReturn Distribution -- ");
            Console.WriteLine("Mean: \t\t\t{0:0.00}\nStdDev: \t\t{1:0.00}\n", returnMean, returnStdDev);
            Console.WriteLine(
                "Min: \t\t\t{0:0.00}\nQ1 (25% Percentile): \t{1:0.00}\nQ2 (Median): \t\t{2:0.00}\nQ3 (75% Percentile): \t{3:0.00}\nMax: \t\t\t{4:0.00}",
                returnMin, quantiles[0], quantiles[1], quantiles[2], returnMax
            );
            */

            Console.WriteLine(
                "Min: \t\t\t{0:0.00}\nQ1 (25% Percentile): \t{1:0.00}\nQ2 (Median): \t\t{2:0.00}\nQ3 (75% Percentile): \t{3:0.00}\nMax: \t\t\t{4:0.00}",
                returnMin, returnQ1, returnMedian, returnQ3, returnMax
            );

            Console.WriteLine("Press any key to continue ...");
            Console.ReadKey();
        }
    }
}
