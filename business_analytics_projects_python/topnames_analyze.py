# Emma Pakarinen, 13.12.2022

# object: generate a list of most popular (top 5) male and female names in 2019
# and 2020 respectively from subsetted and sorted Dataframe

import pandas as pd

# downloading csv file to dataframe
df = pd.read_csv("20221107_topbabynames.csv")

# including only years 2019-2020
df_19_20 = df.loc[(df['Year'] >= 2019) & (df['Year'] <= 2020)]

# selecting the rank to be from 1 to 5
df_19_20_ranked = df_19_20.loc[(df_19_20['Rank'] >= 1) & (df_19_20['Rank'] <= 5)]

# grouping names by gender
df_19_20_gr = df_19_20_ranked.groupby('Sex')

# Selecting the first 10 to print so that we get top 5 from boys and girls from 2019 (10) and the same from 2020 (10)
df_19_20_sorted = df_19_20_gr.head(10)

# top female and male names from 2019 respectively
print(df_19_20_sorted.head(10), "\n")

# top female and male names from 2020 respectively
print(df_19_20_sorted.tail(10))
