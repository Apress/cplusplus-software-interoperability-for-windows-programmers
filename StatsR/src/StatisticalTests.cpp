#include <Rcpp.h>

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

#include "../../Common/include/StatisticalTests.h"

//' Perform a t-test from summary input data
//' 
//' @param mu0 Population mean.
//' @param mean Sample mean.
//' @param sd Sample standard deviation.
//' @param n Sample size.
//' @export
// [[Rcpp::export]]
std::unordered_map<std::string, double> t_test_summary_data(double mu0, double mean, double sd, double n) {
  
  Stats::TTest test(mu0, mean, sd, n);
  
  test.Perform();
  std::unordered_map<std::string, double> results = test.Results();
  return results;
}

//' Perform a one-sample t-test
//' 
//' @param mu0 Population mean.
//' @param x1 A vector of doubles.
//' @export
// [[Rcpp::export]]
std::unordered_map<std::string, double> t_test_one_sample(double mu0, Rcpp::NumericVector x1) {
  
  std::vector<double> _x1 = Rcpp::as<std::vector<double> >(x1);
  
  Stats::TTest test(mu0, _x1);
  
  test.Perform();
  std::unordered_map<std::string, double> results = test.Results();
  return results;
}

//' Perform a two-sample t-test
//' 
//' @param x1 A vector of doubles.
//' @param x2 A vector of doubles.
//' @export
// [[Rcpp::export]]
std::unordered_map<std::string, double> t_test_two_sample(Rcpp::NumericVector x1, Rcpp::NumericVector x2) {
  
  std::vector<double> _x1 = Rcpp::as<std::vector<double> >(x1);
  std::vector<double> _x2 = Rcpp::as<std::vector<double> >(x2);
  
  Stats::TTest test(_x1, _x2);
  
  test.Perform();
  std::unordered_map<std::string, double> results = test.Results();
  return results;
}

// A wrapper class for t-tests
class TTest
{
public:
  ~TTest() = default;
  
  TTest(double mu0, double mean, double sd, double n)
    : _ttest(mu0, mean, sd, n)
  {}

  TTest(double mu0, Rcpp::NumericVector x1)
    : _ttest(mu0, Rcpp::as<std::vector<double> >(x1))
  {}
  
  TTest(Rcpp::List data)
    : _ttest(Rcpp::as<std::vector<double> >(data["x1"]), Rcpp::as<std::vector<double> >(data["x2"]))
  {}

  bool Perform()
  {
    return _ttest.Perform();
  }
  
  std::unordered_map<std::string, double> Results() const
  {
    std::unordered_map<std::string, double> results = _ttest.Results();
    return results;
  }

private:
  Stats::TTest _ttest;
};


RCPP_MODULE(StatsTests) {

  Rcpp::class_<TTest>("TTest")
    .constructor<double, double, double, double>("Perform a t-test from summary input data")
    .constructor<double, Rcpp::NumericVector >("Perform a one-sample t-test with known population mean")
    .constructor<Rcpp::List>("Perform a two-sample t-test: args 'x1' and 'x2'")
    .method("Perform", &TTest::Perform, "Perform the required test")
    .method("Results", &TTest::Results, "Retrieve the test results")
  ;

}











