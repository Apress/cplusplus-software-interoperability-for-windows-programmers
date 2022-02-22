#include <Rcpp.h>

#include <string>
#include <vector>
#include <unordered_map>

#include "../../Common/include/Stats.h"
#include "../../Common/include/DescriptiveStatistics.h"

//' Compute excess kurtosis
//' 
//' @param data A vector of doubles.
//' @export
// [[Rcpp::export]]
double excess_kurtosis(Rcpp::NumericVector data) {
  
  std::vector<double> _data = Rcpp::as<std::vector<double> >(data);

  double result = Stats::DescriptiveStatistics::ExcessKurtosis(_data);
  return result;
}

//' Retrieve descriptive statistics for a vector of values
//' 
//' @param data A vector of doubles.
//' @param keys An optional vector of keys.
//' @export
// [[Rcpp::export]]
std::unordered_map<std::string, double> 
 get_descriptive_statistics(Rcpp::NumericVector data, Rcpp::CharacterVector keys = Rcpp::CharacterVector::create()) {
  
  std::vector<double> _data = Rcpp::as<std::vector<double> >(data);
  std::vector<std::string> _keys = Rcpp::as<std::vector<std::string> >(keys);
   
  std::unordered_map<std::string, double> results = Stats::GetDescriptiveStatistics(_data, _keys);
  return results;
}

