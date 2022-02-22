#pragma once

#include <any>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;


namespace StatsCLR {

	namespace Conversion
	{
		// Standard functions to marshal strings to and from a managed environment
		void MarshalString(String^ s, std::string& os);
		void MarshalString(String^ s, std::wstring& os);

		// Convert a generic List<double> to a std::vector<double>
		std::vector<double> ListToVector(List<double>^ input);

		// Convert a generic List<String^> to a std::vector<std::string>
		std::vector<std::string> ListToVector(List<String^>^ input);

		// Convert a std::unordered_map to a Dictionary
		Dictionary<String^, double>^ ResultsToDictionary(const std::unordered_map<std::string, double>& input);
	}
}
