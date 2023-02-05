# Emma Pakarinen, 13.12.2022
# In this code data is read from a csv-file and visualized with seaborn -library.

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# loading the csv-file into Dataframe
df = pd.read_csv('bmi.csv')

# creating a scatter plot of the data using relplot-function with height on x-axis and weight on y-axis 
# coloring the plot points based on Gender and varying the size of the points by the BMI index

sns.relplot(data=df, x = "Height", y = "Weight", hue="Gender", size="Index")

plt.show()
