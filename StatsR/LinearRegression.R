# Linear Regression
library(StatsR)
library(ggplot2)

predict <- function(b0, b1, x){
  return (b0 + b1 * x)
}

data <- read.table(file.path(getwd(),'../data/HouseData.csv'), 
                   header=TRUE, sep=",", 
                   fileEncoding = "UTF-8-BOM")
ggplot(data, aes(x=Size, y=Price)) + 
  geom_point()+
  geom_smooth(method=lm, se=FALSE)

results <- StatsR::linear_regression(data$Size, data$Price)
results
b0 <- results["b0"]
b1 <- results["b1"]

size = 2.5
predicted_price <- predict(b0, b1, size);
sprintf("Predicted price for size: %.2f sq ft= %.2fk", 
        size * 1000, predicted_price * 100)
fm <- lm(Price ~ Size, data=data) 

# Fit a simple linear regression and look at the analysis.
summary(fm)                                      
