import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
import numpy as np
import datetime

FONTSIZE = 16
plt.rc('font', size=FONTSIZE)

# Read the CSV file
data = pd.read_csv("data.txt")

df = pd.DataFrame(data)
datetimes = pd.to_datetime(df[['year', 'month', 'day', 'hour', 'minute']])
df['date'] = datetimes
df.set_index('date', inplace=True)
last_day = datetimes.max() - pd.Timedelta(days=1)

plt.figure(figsize=(15, 10))
axes1 = df.loc[last_day:, "temperature"].plot(title="Temperature and humidity from the past 24h", ylabel="Temperature", color="Red", legend=True)
axes2 = df.loc[last_day:, "humidity"].plot(secondary_y=True, xlabel="Time", ylabel="Humidity", color="Blue", legend=True)

plt.axvline(datetimes.max().normalize(), color="Black", linewidth=2)
axes1.yaxis.set_major_formatter(FuncFormatter(lambda val, _: f"{val:.1f} °C"))
axes2.yaxis.set_major_formatter(FuncFormatter(lambda val, _: f"{val:.0f} %"))

plt.show()
