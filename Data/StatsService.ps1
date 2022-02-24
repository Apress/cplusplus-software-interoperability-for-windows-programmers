$Stats = [Reflection.Assembly]::LoadFile("D:\Development\Projects\C++\SoftwareInteroperability\x64\Debug\StatsCLR.dll")
$Stats.ExportedTypes
$data = New-Object Collections.Generic.List[double]
$data = (Get-Counter -counter "\Memory\% Committed Bytes In Use" -MaxSamples 10 -SampleInterval 1).CounterSamples.CookedValue
$keys = @("Mean", "StdDev.S", "Minimum", "Maximum")
[StatsCLR.Statistics]::DescriptiveStatistics($data, $keys) | Format-Table
[StatsCLR.Statistics]::DescriptiveStatistics($data, $keys) | Out-GridView
