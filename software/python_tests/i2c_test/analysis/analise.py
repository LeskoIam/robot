__author__ = 'Lesko'
# Documentation is like sex.
# When it's good, it's very good.
# When it's bad, it's better than nothing.
# When it lies to you, it may be a while before you realize something's wrong.
import matplotlib.pyplot as plt
import numpy as np
import csv
from collections import OrderedDict

def median(lst):
    return np.median(np.array(lst))

def load_data(file_name):
    with open(file_name, "rb") as f:
        data = csv.reader(f, delimiter=";")
        x = []
        y = []
        for row in data:
            x.append(float(row[0]))
            y.append(float(row[1]))
    return x, y

def remove_clusters(x, y):
    # len(x) == len(y)
    x_in = x[:]
    y_in = y[:]
    d = OrderedDict()
    for x, y in zip(x_in, y_in):
        if d.get(x) is None:
            d[x] = []
        d[x].append(y)

    x_out = []
    y_out = []
    for ran in d.keys():
        x_out.append(ran)
        y_out.append(median(d[ran]))
    return x_out, y_out

if __name__ == '__main__':

    x1, y1 = remove_clusters(*load_data("results_10us_sleep_step.csv"))
    x2, y2 = remove_clusters(*load_data("results_50us_sleep_step.csv"))

    plt.plot(x1, y1, color="red")
    plt.hold(True)
    plt.plot(x2, y2)
    plt.grid(True)
    plt.show()
