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
    public static class DataModelling
    {
        public static double Predict(double b0, double b1, double x)
        {
            return b0 + b1 * x;
        }

        public static void Run()
        {
            Console.Clear();

            // 1. Import or create training data
            string filename = @"..\..\..\Data\HouseData.csv";
            Accord.IO.CsvReader reader = new Accord.IO.CsvReader(filename, true);

            System.Data.DataTable dt = reader.ToTable();
            double[] size = dt.AsEnumerable()
                        .Select(row => Convert.ToDouble(row.Field<string>("Size"), 
                        System.Globalization.CultureInfo.InvariantCulture)).ToArray();
            double[] price = dt.AsEnumerable()
                        .Select(row => Convert.ToDouble(row.Field<string>("Price"), 
                        System.Globalization.CultureInfo.InvariantCulture)).ToArray();

            // 2. Specify data preparation and model training pipeline
            List<double> ys = new List<double>(price);
            List<double> xs = new List<double>(size);

            // 3. Train model
            var results = Statistics.LinearRegression(xs, ys);
            double b0 = results["b0"];
            double b1 = results["b1"];

            // 4. Make a prediction
            double new_size = 2.5;
            var predicted_price = Predict(b0, b1, new_size);

            Console.WriteLine($"(StatsCLR):\tPredicted price for size: "
                              + $"{new_size * 1000} sq ft= {predicted_price * 100:C}k");

            // Compare the prediction with Accord.NET
            {
                Accord.Statistics.Models.Regression.Linear.OrdinaryLeastSquares ols = new OrdinaryLeastSquares();
                SimpleLinearRegression regression = ols.Learn(size, price);
                double y = regression.Transform(new_size);
                // We can also extract the slope and the intercept
                double s = regression.Slope;
                double c = regression.Intercept;
                Console.WriteLine($"(Accord.NET):\tPredicted price for size: {new_size * 1000} sq ft= {y * 100:C}k");
            }

            Console.WriteLine("Press any key to continue ...");
            Console.ReadKey();
        }
    }
}
