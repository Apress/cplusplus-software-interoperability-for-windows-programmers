###############################################################################
#
# Descriptive Statistics
#
###############################################################################

library(tidyverse)
library(tsibble)
library(lubridate)
library(ggplot2)
library(ggpubr)
library(plotly)
library(dplyr)
library(formattable)                             # https://rfortherestofus.com/2019/11/how-to-make-beautiful-tables-in-r/
library(summarytools)

library(moments)                                 # Kurtosis

library(StatsR)                                  # Native C++ stats library

n = 1000                                         # n samples
data <- rnorm(n = n, mean = 0, sd = 1)           # from a Normal distribution with mean = 0, sd = 1
#write(data, ncolumns= 1, sep="\n", "data.txt")
obs <- c(1:n)

data.df <- data.frame(obs, data)                 # create a data frame
colnames(data.df) <- c("Index", "Value")

# Plot the data
ggplotly(
  data.df %>% 
    ggplot(aes(x = obs, y = data)) +
    geom_point(color = "steelblue") +
    geom_line(color = "steelblue") +
    # geom_smooth() +
    labs(x = "Index", y = "Data", title = "Random Series") + 
    theme(axis.text.x = element_text(angle = 45, hjust = 1))
)

#
# Create two sets of data (one from StatsR and one using base R functions)
# and compare them side-by-side in a table
# 

# StatsR

rownames <- c("Count", "Maximum", "Minimum", "Range", 
              "Kurtosis", "Median", "Mean", "StdDev.S", 
              "Sum", "StdErr", "Variance.S", "Skew")

stats <- StatsR::get_descriptive_statistics(data, rownames)
stats

stats <- as.data.frame(stats)

# Add equivalent values from R
baseR <- c(skewness(data),
           var(data),
           sqrt(var(data)/length(data)),
           sum(data), 
           mean(data), 
           max(data), 
           n, 
           sd(data), 
           min(data), 
           max(data)-min(data), 
           kurtosis(data), 
           median(data)
           )

tolerance = 1e-5
values <- stats[[1]]
equal <- (values - baseR) >= (tolerance - 0.5)

# Reformat the columns
stats <- format(stats, scientific = FALSE, digits=4)
baseR <- format(baseR, scientific = FALSE, digits=4)


stats.table.df <- data.frame(stats, baseR, equal)      # Create a data frame
names(stats.table.df)[1] <- "StatsR"                   # Rename the columns
names(stats.table.df)[2] <- "BaseR"
names(stats.table.df)[3] <- "Equal"


formattable(stats.table.df, 
            list(StatsR = formatter("span", style = ~formattable::style(color = ifelse(Equal == TRUE, "green", "red"))),
                 BaseR = formatter("span", style = ~formattable::style(color = ifelse(Equal == TRUE, "green", "red"))),
                 Equal = formatter("span", style = ~formattable::style(color = ifelse(Equal == TRUE, "green", "red")))
                 )
            )                            # Display results

