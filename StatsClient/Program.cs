using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

// Change the platform target to x64 (consistent with the other entities: StatsLib, StatsCLR) to avoid the warning:
// warning MSB3270: There was a mismatch between the processor architecture of the project being build "MSIL" and the 
// processor architecture of the reference "[internal C# dll]", "x86".

namespace StatsClient
{
    class Program
    {
        static void Main(string[] args)
        {
            StatisticalFunctions.Run();
            DataAnalysis.Run();
            DataModelling.Run();
            HypothesisTest.Run();
            ModuleInfo.Enumerate();
            DynamicInvocation.Run();
        }
    }
}
