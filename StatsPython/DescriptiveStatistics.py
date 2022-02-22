from Utilities import report_exception

import pandas as pd

import StatsPythonRaw as Stats


def descriptive_statistics(data: list, name: str) -> None:
    """ Run descriptive statistics """
    try:
        # Labels
        stats: list = ["Count",
                       "Mean",
                       "StdDev.S",
                       "Minimum",
                       "Q1",
                       "Median",
                       "Q3",
                       "Maximum"]

        # Summary statistics
        summary: dict = Stats.DescriptiveStatistics(data, stats)

        # Compare results to Pandas
        df: pd.DataFrame = pd.DataFrame(data, columns=[name])

        res = {
            'Statistics': ["Count",
                           "Mean",
                           "StdDev.S",
                           "Minimum",
                           "Q1",
                           "Median",
                           "Q3",
                           "Maximum"],
            'Pandas': [df[name].count(),
                       df[name].mean(),
                       df[name].std(),
                       df[name].min(),
                       df[name].quantile(0.25),
                       df[name].quantile(0.50),
                       df[name].quantile(0.75),
                       df[name].max()],
            'StatsLib': [summary["Count"],
                         summary["Mean"],
                         summary["StdDev.S"],
                         summary["Minimum"],
                         summary["Q1"],
                         summary["Median"],
                         summary["Q3"],
                         summary["Maximum"]]
        }
        results: pd.DataFrame = pd.DataFrame(res)
        print(results)

    except Exception as inst:
        report_exception(inst)


if __name__ == "__main__":
    """ Define standard data sets used elsewhere """
    xs: list = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    ys: list = [1, 3, 2, 5, 7, 8, 8, 9, 10, 12]

    descriptive_statistics(xs, 'xs')
    descriptive_statistics(ys, 'ys')
