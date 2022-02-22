# Statistical T-tests

# No sample data
StatsR::t_test_summary_data(5, 9.261460, 0.2278881e-01, 195)

# Interactive version
# data <- read.table(file.choose())

#
# One-sample t-test
#
data <- read.table("../data/weight.txt")
weight = data$V1

t.test(weight, mu = 25)

StatsR::t_test_one_sample(25, weight)

#
# Two-sample t-test
#
us_mpg <- read.table("../data/us-mpg.txt")
jp_mpg <- read.table("../data/jp-mpg.txt")

us = us_mpg$V1
jp = jp_mpg$V1

StatsR::t_test_two_sample(us, jp)

#
# t-test using a class
#

library(Rcpp)
require(Rcpp)
library(formattable)

moduleStatsTests <- Module("StatsTests", PACKAGE="StatsR")
ttest0 <- new(moduleStatsTests$TTest, 5, 9.261460, 0.2278881e-01, 195)
if(ttest0$Perform()) {
  results <- ttest0$Results()
  print(results)
  results <- as.data.frame(results)
  formattable(results)
  
} else {
  print("T-test from summary data failed.")
}

ttest1 <- new(moduleStatsTests$TTest, 25, weight)
if(ttest1$Perform()) {
  print(ttest1$Results())
} else {
  print("One-sample t-test failed.")
}

cols <- list('x1'=us, 'x2'=jp)

ttest2 <- new(moduleStatsTests$TTest, cols)
if(ttest2$Perform()) {
  print(ttest2$Results())
} else {
  print("Two-sample t-test failed.")
}





