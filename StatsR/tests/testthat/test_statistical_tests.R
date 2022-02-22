context("Statistical Tests")

test_that("T-test from data", {
  
  results = StatsR::t_test_summary_data(5, 9.261460, 0.2278881e-01, 195)
  
  expect_equal(2611.28380, results[["t"]])
  expect_equal(0.000e+000, results[["pval"]])
  expect_equal(194.0, results[["df"]])
  expect_equal(9.26146, results[["x1-bar"]])
  expect_equal(0.02278881, results[["sx1"]])
  expect_equal(195.0, results[["n1"]])

})

test_that("One-sample t-test", {
  
  data <- read.table(file.path(getwd(),'../../../data/weight.txt'))
  weight = data$V1
  
  results = StatsR::t_test_one_sample(25, weight)

  expect_equal(results[["t"]], -9.0783, tolerance = 1e-4)
  expect_equal(results[["pval"]], 7.9531e-06)
  expect_equal(results[["df"]], 9.0)
  expect_equal(results[["x1-bar"]], 19.25)
  expect_equal(results[["sx1"]], 2.002915, tolerance = 1e-6)
  expect_equal(results[["n1"]], 10)

})

test_that("Two-sample t-test", {
  
  us_mpg <- read.table(file.path(getwd(),'../../../data/us-mpg.txt'))
  jp_mpg <- read.table(file.path(getwd(),'../../../data/jp-mpg.txt'))

  us = us_mpg$V1
  jp = jp_mpg$V1
  
  results = StatsR::t_test_two_sample(us, jp)

  expect_equal(results[["t"]], -12.62059, tolerance=1e-5)
  expect_equal(results[["pval"]], 0.0, tolerance=1e-5)
  expect_equal(results[["df"]], 326.0)
  expect_equal(results[["x1-bar"]], 20.14458, tolerance=1e-5)
  expect_equal(results[["sx1"]], 6.41470, tolerance=1e-5)
  expect_equal(results[["n1"]], 249)
  expect_equal(results[["x2-bar"]], 30.48101, tolerance=1e-5)
  expect_equal(results[["sx2"]], 6.10771, tolerance=1e-5)
  expect_equal(results[["n2"]], 79)
  
})
