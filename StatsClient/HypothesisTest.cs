using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;

using Accord.Statistics.Models.Regression.Linear;

using StatsCLR;

namespace StatsClient
{
    public static class HypothesisTest
    {
        public static void Report(Dictionary<string, double> results)
        {
            StringBuilder sb = new StringBuilder();

            sb.AppendLine("Student t-test for two samples (equal variances)");
            sb.AppendFormat($"Number of Observations(Sample 1) = {results["n1"]}\n");
            sb.AppendFormat($"Sample 1 Mean = {results["x1-bar"]}\n");
            sb.AppendFormat($"Sample 1 Standard Deviation = {results["sx1"]}\n");
            sb.AppendFormat($"Number of Observations(Sample 2) = {results["n2"]}\n");
            sb.AppendFormat($"Sample 2 Mean = {results["x2-bar"]}\n");
            sb.AppendFormat($"Sample 2 Standard Deviation = {results["sx2"]}\n");
            sb.AppendFormat($"Degrees of Freedom = {results["df"]}\n");
            sb.AppendFormat($"T Statistic = {results["t"]}\n");
            sb.AppendFormat($"Probability that difference is due to chance = {results["pval"]}\n");
            sb.AppendFormat("Results for Alternative Hypothesis and alpha = 0.0500\n");
            sb.AppendFormat("Alternative Hypothesis              Conclusion\n");
            sb.AppendFormat("Sample 1 Mean != Sample 2 Mean      NOT REJECTED\n");
            sb.AppendFormat("Sample 1 Mean < Sample 2 Mean       NOT REJECTED\n");
            sb.AppendFormat("Sample 1 Mean > Sample 2 Mean       REJECTED\n");

            Console.WriteLine(sb.ToString());
        }

        public static void Run()
        {
            Console.Clear();

            // 1. Import data
            Accord.IO.CsvReader reader_us = new Accord.IO.CsvReader(@"..\..\..\Data\us_mpg.csv", true);
            Accord.IO.CsvReader reader_jp = new Accord.IO.CsvReader(@"..\..\..\Data\jp_mpg.csv", true);

            System.Data.DataTable dt_us = reader_us.ToTable();
            double[] us_mpg = dt_us.AsEnumerable()
                        .Select(row => Convert.ToDouble(row.Field<string>("usmpg"), System.Globalization.CultureInfo.InvariantCulture)).ToArray();

            System.Data.DataTable dt_jp = reader_jp.ToTable();
            double[] jp_mpg = dt_jp.AsEnumerable()
                        .Select(row => Convert.ToDouble(row.Field<string>("jpmpg"), System.Globalization.CultureInfo.InvariantCulture)).ToArray();

            List<double> us = new List<double>(us_mpg);
            List<double> jp = new List<double>(jp_mpg);

            // 2. Perform test
            TTest test = new TTest(us, jp);
            test.Perform();
            var results = test.Results();

            Report(results);

            Console.WriteLine("Press any key to continue ...");
            Console.ReadKey();
        }
    }
}
