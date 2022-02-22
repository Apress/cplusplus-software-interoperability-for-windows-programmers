// Conversion.cpp

#include "pch.h"

#include "Conversion.h"

namespace StatsCLR {

	namespace Conversion {

		//
		// Standard functions to marshal strings to and from managed environment
		//
		void MarshalString(String^ s, std::string& os)
		{
			using namespace Runtime::InteropServices;

			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		void MarshalString(String^ s, std::wstring& os)
		{
			using namespace Runtime::InteropServices;

			const wchar_t* chars = (const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		//
		// Convert a generic List<double> to a std::vector<double>
		//
		std::vector<double> ListToVector(List<double>^ input)
		{
			std::vector<double> output;
			if(input != nullptr)
			{
				const int count = input->Count;
				output.resize(count);
				for (int i = 0; i < count; ++i)
					output[i] = input[i];   // native double <--> system.double
			}
			return output;
		}

		//
		// Convert a generic List<String^> to a std::vector<std::string>
		//
		std::vector<std::string> ListToVector(List<String^>^ input)
		{
			std::vector<std::string> output;
			if (input != nullptr)
			{
				const int count = input->Count;
				output.resize(count);
				for (int i = 0; i < count; ++i)
				{
					std::string os;
					MarshalString(input[i], os);
					output[i] = os;
				}
			}
			return output;
		}

		std::vector<double> ArrayToVector(cli::array<double>^ input)
		{
			const std::size_t count = input->Length;
			std::vector<double> output(count);
			pin_ptr<double> pin(&input[0]);
			double* first(pin);
			double* last(pin + count);
			std::copy(first, last, output.begin());
			return output;
		}

		//
		// Convert a std::unordered_map to a Dictionary
		//
		Dictionary<String^, double>^ ResultsToDictionary(const std::unordered_map<std::string, double>& input)
		{
			Dictionary<String^, double>^ output = gcnew Dictionary<String^, double>();
			for (const auto& item : input)
				output->Add(gcnew String(item.first.c_str()), item.second);
			return output;
		}
	}
}
