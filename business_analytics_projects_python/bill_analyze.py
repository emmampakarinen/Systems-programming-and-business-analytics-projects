# Emma Pakarinen, 13.12.2022

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# reading the csv file to dataframe
df = pd.read_csv("bill.csv", sep=';')
print(df)

# 1st object: Draw a boxplot using only one axis on total_bill and with whitegrid background.

sns.set_style("whitegrid")

sns.boxplot(x="total_bill", data=df)
plt.show()

# 2nd object: Draw a boxplot using day on y_axis and tip on x_axis and with whitegrid background.
sns.set_style("whitegrid")
sns.boxplot(x="tip", y="day", data=df)
plt.show()

# 3rd object: Draw a boxplot using day on x_axis and total_bill on y_axis and using hue on
# time using whitegrid background.
sns.set_style("whitegrid")
sns.boxplot(x="day", y="total_bill", data=df, hue="time")
plt.show()
