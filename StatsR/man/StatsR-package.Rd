\name{StatsR-package}
\alias{StatsR-package}
\alias{StatsR}
\docType{package}
\title{
  Package to demonstrate wrapping a native C++ library (libStatsLib.a) and exposing the functionality to R/RStudio.
}
\description{
  The package wraps a C++ static library component called libStatsLib.a. This is an ABI compliant library built with gcc using CodeBlocks. This component offers basic descriptive statistics, univariate linear regression and t-tests (from data, one-sample and two-sample). The purpose of the wrapper is to demonstrate using the Rcpp framework.
}
\details{
The following R functions wrap their C++ counterparts:
\itemize{
\item get_descriptive_statistics
\item linear_regression
\item t_test_summary_data
\item t_test_one_sample
\item t_test_two_sample
}
}
\author{
Adam Gladstone, my_email@mailserver.com

Maintainer: Adam Gladstone <my_email@mailserver.com>
}
\references{
  https://r-pkgs.org/src.html
}
\keyword{ package }
\seealso{
  Optional links to other man pages
}
\examples{
  \dontrun{
     ## Simple example of usage of get_descriptive_statistics(...)
     # 10 samples from a Normal dist with mean = 0, sd = 1
     data <- rnorm(n = 10, mean = 0, sd = 1)
     results <- StatsR::get_descriptive_statistics(data)
     results
     
     ## Example that returns only the requested statistics
     stats <- c("Mean", "StdDev.S")
     results <- StatsR::get_descriptive_statistics(data, stats)
     results
  }
}
