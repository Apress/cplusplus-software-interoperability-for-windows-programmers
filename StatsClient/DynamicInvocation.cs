using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

using StatsCLR;

namespace StatsClient
{
    public static class DynamicInvocation
    {
        public static void Run()
        {
            Console.Clear();

            string assemblyName = @"StatsCLR.dll";
            Console.WriteLine("Loading and enumerating the assembly: " + assemblyName);

            ModuleInfo.Enumerate(assemblyName);
            Console.WriteLine();

            {
                // Dynamic invocation
                Type type = typeof(StatsCLR.Statistics);
                MethodInfo method = type.GetMethod("LinearRegression");

                object[] parameters = new object[2];
                parameters[0] = new List<double> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
                parameters[1] = new List<double> { 1, 3, 2, 5, 7, 8, 8, 9, 10, 12 };

                object obj = new object();
                object retVal = method.Invoke(obj, parameters);
                Dictionary<string, double> results = (Dictionary<string, double>)retVal;
                StatisticalFunctions.OutputResults(results);
            }

            {
                // Dynamic object creation
                object[] parameters = new object[4];
                parameters[0] = 5;              // mu0
                parameters[1] = 9.261460;       // x_bar
                parameters[2] = 0.2278881e-01;  // sx;
                parameters[3] = 195;            // n

                Type type = typeof(StatsCLR.TTest);
                TTest ttest = Activator.CreateInstance(type, parameters) as TTest;
                ttest.Perform();
                Dictionary<string, double> results = ttest.Results();
                StatisticalFunctions.OutputResults(results);
            }

            Console.WriteLine("Press any key to continue ...");
            Console.ReadKey();
        }
    }
}
