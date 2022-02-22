#!/usr/bin/env python

from random import random
from time import perf_counter

import math
import statistics
import StatsPythonPyBind as Stats


COUNT: int = 500000  # Change this value depending on the speed of your computer
DATA: list = [(random() - 0.5) * 3 for _ in range(COUNT)]


def mean(data: list) -> float:
    return sum(data) / len(data)


def variance(data: list, ddof=0) -> float:
    n: int = len(data)
    mean: float = sum(data) / n
    return sum((x - mean) ** 2 for x in data) / (n - ddof)


def stdev(data: list) -> float:
    var = variance(data)
    return math.sqrt(var)


#def mean(x: list) -> float:
#    return statistics.fmean(x)


#def stdev(x: list) -> float:
#    return statistics.stdev(x)


def test(fn, name) -> None:
    start: float = perf_counter()
    result: float = fn(DATA)
    duration: float = perf_counter() - start
    print('{} took {:.3f} seconds'.format(name, duration))


if __name__ == "__main__":
    print('Running benchmarks with COUNT = {}'.format(COUNT))

    test(mean, '[mean(x)] (Python implementation)')
    test(stdev, '[stdev(x)] (Python implementation)')

    test(Stats.Mean, '[Mean(x)] (C++ implementation)')
    test(Stats.StdDevS, '[StdDevS(x)] (C++ implementation)')

