context("Descriptive Statistics")
library(moments)

test_that("Descriptive Statistics Values", {

  # 10 samples from a Normal dist with mean = 0, sd = 1
  data <- rnorm(n = 10, mean = 0, sd = 1)
  
  results <- StatsR::get_descriptive_statistics(data)
  
  expect_equal(mean(data), results[["Mean"]])
  expect_equal(max(data),results[["Maximum"]])
  expect_equal(min(data), results[["Minimum"]])
  expect_equal(max(data)-min(data), results[["Range"]])
  expect_equal(kurtosis(data), results[["Kurtosis"]])
  expect_equal(skewness(data), results[["Skew"]])
  expect_equal(median(data), results[["Median"]])
  expect_equal(sd(data), results[["StdDev.S"]])
  expect_equal(sum(data), results[["Sum"]])
  expect_equal(sqrt(var(data)/length(data)), results[["StdErr"]])
  expect_equal(var(data), results[["Variance.S"]])
})