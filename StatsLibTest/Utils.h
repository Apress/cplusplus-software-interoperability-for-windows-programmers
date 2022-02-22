#pragma once

namespace StatsLibTest
{
	namespace Utils
	{
		// Singleton class to manage any test settings
		class TestSettings
		{
		public:
			~TestSettings() = default;
			TestSettings(TestSettings const&) = delete;
			TestSettings& operator=(TestSettings const&) = delete;

			static TestSettings& Instance();

			void SetDataDirectory(const std::string& path) { m_data_directory = path; }
			const std::string& GetDataDirectory() const { return m_data_directory; }

		private:
			explicit TestSettings();

			std::string m_data_directory;
		};

		// Simple function to read a text file with a single column of numbers into 
		// a std::vector
		std::vector<double> ReadData(const std::string& filename);
	}
}

// Alias
#define testSettings StatsLibTest::Utils::TestSettings::Instance()
