#include "pch.h"

int main(int argc, char* argv[])
{
    if (argc < 2) { 
        // We expect 2 arguments: the program name, the data path
        std::cerr << "Usage: " << argv[0] << " <DataPath>" << '\n';
        return 1;
    }

    if (argc == 4)
    {
        // Test is being run from test explorer and we are passed:
        //      +argv[0]	0x0000029daf35f888 "D:\\Development\\Projects\\C++\\SoftwareInteroperability\\x64\\Debug\\StatsLibTest.exe"	char*
        //      +argv[1]	0x0000029daf35f8d8 "--gtest_output=xml:C:\\Users\\adam_\\AppData\\Local\\Temp\\tmp7BDA.tmp"	char*
        //      +argv[2]	0x0000029daf35f919 "--gtest_catch_exceptions=1"	char*
        //      +argv[3]	0x0000029daf35f934 "--gtest_break_on_failure=0"	char*

        std::filesystem::path p("D:\\Development\\Projects\\C++\\SoftwareInteroperability\\Data");
        testSettings.SetDataDirectory(p.string());
    }
    else
    {
        std::filesystem::path p(argv[1]);
        if (p.empty()) {
            std::cerr << "The <DataPath> argument is empty." << '\n';
            return 1;
        }

        testSettings.SetDataDirectory(p.string());
    }

    // Pass any arguments on to the test framework
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}