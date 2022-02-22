from Utilities import report_exception, print_results

import numpy as np
import matplotlib.pyplot as plt

import StatsPythonRaw as Stats


def linear_regression(xs: np.ndarray, ys: np.ndarray) -> None:
    """ Run simple linear regression """
    try:
        x: list = xs.tolist()
        y: list = ys.tolist()
        lr: dict = Stats.LinearRegression(x, y)
        print_results(lr, "Linear regression")
    except Exception as inst:
        report_exception(inst)


def estimate_coef(x, y):
    # number of observations/points
    n = np.size(x)

    # mean of x and y vector
    m_x = np.mean(x)
    m_y = np.mean(y)

    # calculating cross-deviation and deviation about x
    SS_xy = np.sum(y*x) - n*m_y*m_x
    SS_xx = np.sum(x*x) - n*m_x*m_x

    # calculating regression coefficients
    b_1 = SS_xy / SS_xx
    b_0 = m_y - b_1*m_x

    return (b_0, b_1)

def plot_regression_line(x, y, b):
    # plotting the actual points as scatter plot
    plt.scatter(x, y, color = "m",
            marker = "o", s = 30)

    # predicted response vector
    y_pred = b[0] + b[1]*x

    # plotting the regression line
    plt.plot(x, y_pred, color = "g")

    # putting labels
    plt.xlabel('x')
    plt.ylabel('y')

    # function to show plot
    plt.show()


if __name__ == "__main__":
    """ Define standard data sets used elsewhere """
    x: np.ndarray = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
    y: np.ndarray = np.array([1, 3, 2, 5, 7, 8, 8, 9, 10, 12])

    linear_regression(x, y)

    # estimate coefficients
    b = estimate_coef(x, y)
    print("Estimated coefficients:\nb_0 = {} \
        \nb_1 = {}".format(b[0], b[1]))

    # plot regression line
    plot_regression_line(x, y, b)


