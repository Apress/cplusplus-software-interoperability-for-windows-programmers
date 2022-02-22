###############################################################################
#
# Benchmarking StatsR
#
###############################################################################

library(tidyverse)
library(bench)
library(rbenchmark)
library(ggplot2)
library(StatsR)                                  # Native C++ stats library

# Preliminaries
# Get the data
attach(mtcars)

mtcars <- as.data.frame(mtcars)
ggplot(mtcars, aes(x=wt, y=mpg)) + 
  ggtitle("Regression of MPG on Weight") + 
  geom_point() +
  geom_smooth(method=lm)

ggplot(mtcars, aes(x=wt)) + 
  geom_density() + 
  geom_vline(aes(xintercept=get_descriptive_statistics(wt, "Mean")),
              color="blue", linetype="dashed", size=1)

ggplot(mtcars, aes(x=mpg)) + 
  geom_density() + 
  geom_vline(aes(xintercept=get_descriptive_statistics(mpg, "Mean")),
             color="blue", linetype="dashed", size=1)

# StatsR
StatsR <- function(x, y){
  results = StatsR::linear_regression(x, y)
  return
}

# R
R_LM <- function(df){
  model <- lm(mpg ~ wt, data=df) 
  return
}

result <- bench::mark( StatsR(mtcars$wt, mtcars$mpg), R_LM(mtcars) )
result
plot(result)













