// Conversion.h
// Central location for simple type conversion facilities
//
#pragma once

namespace Conversion
{
	// Convert a VARIANT to a std::vector<double>
	HRESULT VariantToVector(VARIANT vIn, std::vector<double>& out);

	// Convert a VARIANT to a std::vector<std::string>
	HRESULT VariantToVector(VARIANT vIn, std::vector<std::string>& out);

	// Convert std::unordered_map to a 2d variant array
	HRESULT ResultsToVariant(const std::unordered_map<std::string, double>& results, VARIANT* pvResults);
}
