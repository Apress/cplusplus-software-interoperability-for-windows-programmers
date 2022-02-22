#include "pch.h"

namespace StatsLibTest 
{
	namespace Utils 
	{
		// Default constructor
		TestSettings::TestSettings() {}

		// Retrieve a single instance of this class
		TestSettings& TestSettings::Instance() {
			static TestSettings single;
			return single;
		}

		// Simple function to read a text file with a single column of numbers into 
		// a std::vector
		std::vector<double> ReadData(const std::string& filename)
		{
			std::vector<double> data;
			if (!filename.empty())
			{
				std::ifstream in_file(filename);
				if (in_file.is_open())
				{
					std::string line;
					while (std::getline(in_file, line))
					{
						if (!line.empty())
						{
							std::stringstream ss(line);
							try
							{
								data.emplace_back(std::stod(line));
							}
							catch (const std::exception& e)
							{
								std::cout << "Could not convert: " << line << " to a double: " << e.what() << ".\n";
							}
						}
					}
				}
				else
				{
					std::cout << "Could not open file: " << filename << ".\n";
				}
			}
			return data;
		}
	}
}
