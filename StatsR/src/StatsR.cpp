#include <Rcpp.h>

using namespace Rcpp;

//' Display the library name and version number.
//' 
//' @param 
//' @export
// [[Rcpp::export]]
String library_version() {
  
  return String("StatsR, version 1.0");
}

