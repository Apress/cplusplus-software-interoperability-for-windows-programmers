#include <Rcpp.h>

#include <string>
#include <vector>
#include <unordered_map>

#include "../../Common/include/Stats.h"

//' Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
//' 
//' @param xs A vector of doubles.
//' @param ys A vector of doubles.
//' @export
// [[Rcpp::export]]
std::unordered_map<std::string, double> linear_regression(Rcpp::NumericVector xs, Rcpp::NumericVector ys) {
  
  std::vector<double> _xs = Rcpp::as<std::vector<double> >(xs);
  std::vector<double> _ys = Rcpp::as<std::vector<double> >(ys);
  
  std::unordered_map<std::string, double> results = Stats::LinearRegression(_xs, _ys);
  return results;
}

/*
//' Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
//' 
//' @param data A data frame containing columns named 'x' and 'y'.
//' @export
// [[Rcpp::export]]
std::unordered_map<std::string, double> linear_regression(Rcpp::DataFrame data) {

  Rcpp::DataFrame D(data);    
  std::vector<double> _xs = Rcpp::as<std::vector<double> >(D["x"]);
  std::vector<double> _ys = Rcpp::as<std::vector<double> >(D["y"]);
  
  std::unordered_map<std::string, double> results = Stats::LinearRegression(_xs, _ys);
  return results;
}
*/


















