using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace StatsExcel
{
    public static class Conversion
    {
        //
        // Report an exception
        //
        public static object[,] ReportException(Exception e)
        {
            object[,] obj = new object[1, 2];
            obj[0, 0] = "Exception: ";
            obj[0, 1] = e.Message;
            return obj;
        }

        //
        // Convert results package to a two-column object array
        // 
        public static object[,] ResultsToObject(Dictionary<string, double> results)
        {
            object[,] o = new object[results.Keys.Count, 2 /* columns */];
            for (int i = 0; i < results.Keys.Count; ++i)
            {
                var element = results.ElementAt(i);
                o[i, 0] = element.Key;
                o[i, 1] = element.Value;
            }
            return o;
        }

        //
        // Convert keys to a list of strings
        // 
        public static List<string> ConvertKeys(object[] keys)
        {
            List<string> _keys = new List<string>();
            if (keys != null)
            {
                for (int i = 0; i < keys.Length; ++i)
                {
                    var key = keys[i].ToString();
                    if (key != "ExcelDna.Integration.ExcelEmpty" && key != "ExcelDna.Integration.ExcelMissing")
                    {
                        _keys.Add(key);
                    }
                }
            }
            return _keys;
        }
    }
}
