import seaborn
import numpy as np
import pandas as pd

from matplotlib import pyplot as plt

data = pd.read_csv("IceCreamDataSet.csv")
flavours = data["Flavor"]
unique_flavours = np.unique(flavours)

customers = data["Customer"]
unique_customers = np.unique(customers)

dates = data["Date"]
unique_dates = np.unique(dates)

barchart = dict(zip(unique_flavours, np.zeros(len(unique_flavours))))
cust_bar = dict(zip(unique_customers, np.zeros(len(unique_customers))))
date_bar = dict(zip(unique_dates, np.zeros(len(unique_dates))))
# print(float(data["Profit"][0][1:]))
for j in unique_flavours:
    for i in range(len(flavours)):
        if(data["Flavor"][i] == j):
            barchart[j] += float(data["Profit"][i][1:]);
for j in unique_customers:
    for i in range(len(customers)):
        if(data["Customer"][i] == j):
            cust_bar[j] += float(data["Profit"][i][1:]);

for j in unique_dates:
    for i in range(len(customers)):
        if(data["Date"][i] == j):
            date_bar[j] += float(data["Profit"][i][1:])

print(sorted(date_bar.items(), key = lambda x: (x[1],x[0])))
# print(barchart)
