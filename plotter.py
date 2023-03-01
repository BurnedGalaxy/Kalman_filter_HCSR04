import matplotlib.pyplot as plt
import pandas as pd

filename = 'sensor.dat'

# Reading the sampling rate
with open(filename) as f:
    sample_rate = int(f.readline())

# Storing the data in the dataframe
df = pd.read_csv(filename, names = ['True value', 'Measured value', 'Estimated value'], skiprows = 1)
col = df.shape[0]
time = [sample_rate *i for i in range(col)]
df['time (ms)'] = time

# Plotting the Dataframe
ax = plt.gca()
df.plot(kind = 'line', x = 'time (ms)', y = 'True value', color = 'black', ax = ax)
df.plot(kind = 'line', x = 'time (ms)', y = 'Measured value', color = 'blue', ax = ax)
df.plot(kind = 'line', x = 'time (ms)', y = 'Estimated value', color = 'red', ax = ax)

plt.title('Distance')
plt.show()
