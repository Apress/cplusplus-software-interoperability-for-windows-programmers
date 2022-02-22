from Utilities import report_exception, print_results

import numpy as np
import pandas as pd

import matplotlib.pyplot as plt

import StatsPythonRaw as Stats


def run_descriptive_statistics(data: list) -> None:
    """ Run descriptive statistics """
    try:
        summary: dict = Stats.DescriptiveStatistics(data)
        print_results(summary, "Summary statistics.")
    except Exception as inst:
        report_exception(inst)


def run_linear_regression(xs: list, ys: list) -> None:
    """ Run simple linear regression """
    try:
        lr: dict = Stats.LinearRegression(xs, ys)
        print_results(lr, "Linear regression.")
    except Exception as inst:
        report_exception(inst)


def ttest_summary_data() -> None:
    """ Perform a t-test from summary data """
    try:
        results: dict = Stats.SummaryDataTTest(5, 9.26146, 0.22788e-01, 195)
        print_results(results, "Summary data t-test.")
    except Exception as inst:
        report_exception(inst)


def one_sample_ttest(df: pd.DataFrame) -> None:
    """ Perform a one-sample t-test """
    try:
        weight: list = df.iloc[:, 0].tolist()
        results = Stats.OneSampleTTest(25, weight)
        print_results(results, "One-sample t-test.")
    except Exception as inst:
        report_exception(inst)


def two_sample_ttest(df_x1: pd.DataFrame, df_x2: pd.DataFrame) -> None:
    """ Run more statistical tests """
    try:
        x1: list = df_x1.iloc[:, 0].tolist()
        x2: list = df_x2.iloc[:, 0].tolist()

        results: dict = Stats.TwoSampleTTest(x1, x2)
        print_results(results, "Two-sample t-test.")
    except Exception as inst:
        report_exception(inst)


def plot_data(df_x1: pd.DataFrame, df_x2: pd.DataFrame) -> None:
    """ Plot the data """
    x1: list = df_x1.iloc[:, 0].tolist()
    x2: list = df_x2.iloc[:, 0].tolist()
    data: list = [x1, x2]
    
    green_diamond = dict(markerfacecolor='g', marker='D')
    fig1, ax = plt.subplots()
    ax.set_title('US versus Japan Petrol Consumption (mpg)')
    ax.set_xticklabels(['US', 'Japan'])
    ax.boxplot(data, flierprops=green_diamond)
    plt.show()


if __name__ == "__main__":
    """ Define standard data sets used elsewhere """
    xs: list = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    ys: list = [1, 3, 2, 5, 7, 8, 8, 9, 10, 12]

    run_descriptive_statistics(xs)
    run_linear_regression(xs, ys)

    ttest_summary_data()

    filename: str = "../Data/weight.txt"

    # Read in data frame
    df: pd.DataFrame = pd.read_csv(filename, header=None)

    one_sample_ttest(df)

    us_df: pd.DataFrame = pd.read_csv("../Data/us-mpg.txt", header=None)
    jp_df: pd.DataFrame = pd.read_csv("../Data/jp-mpg.txt", header=None)

    plot_data(us_df, jp_df)

    two_sample_ttest(us_df, jp_df)
