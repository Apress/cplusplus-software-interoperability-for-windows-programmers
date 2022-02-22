using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;


namespace StatsClient
{
    public class ModuleInfo
    {
        //
        // https://docs.microsoft.com/en-us/dotnet/framework/reflection-and-codedom/how-to-define-a-generic-method-with-reflection-emit
        // https://docs.microsoft.com/en-us/dotnet/api/system.reflection.emit.methodbuilder?view=net-5.0
        //
        public static void Enumerate(string assemblyName = "")
        {
            Console.Clear();

            try
            {
                Assembly assembly = null;
                if (assemblyName.Length == 0)
                {
                    assembly = Assembly.GetExecutingAssembly();
                }
                else 
                {
                    assembly = Assembly.LoadFrom(assemblyName);
                }

                Console.WriteLine("Assembly Name: " + assembly.FullName);
                Console.WriteLine("Assembly Location: " + assembly.Location);

                Module[] modules = assembly.GetModules();
                foreach (Module module in modules)
                {
                    Console.WriteLine("Module Name: " + module.FullyQualifiedName);
                    Type[] types = module.GetTypes();
                    foreach (Type type in types)
                    {
                        Console.WriteLine("\nType Name: " + type.FullName);
                        Console.WriteLine("Methods");
                        MethodInfo[] methods = type.GetMethods();
                        string functionString;
                        foreach (MethodInfo method in methods)
                        {
                            StringBuilder sbParams = new StringBuilder();
                            ParameterInfo[] parameters = method.GetParameters();
                            int paramCount = 0;
                            foreach (ParameterInfo parameter in parameters)
                            {
                                if (paramCount > 0 && paramCount < parameters.Length)
                                    sbParams.Append(", ");
                                sbParams.AppendFormat($"{parameter.ParameterType} {parameter.Name}");
                                paramCount++;
                            }

                            functionString = string.Format($"\t{method.Name}({sbParams.ToString()})");
                            Console.WriteLine(functionString);
                        }
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }

            Console.WriteLine("Press any key to continue ...");
            Console.ReadKey();
        }
    }
}
