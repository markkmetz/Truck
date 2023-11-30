import serial
import csv
import matplotlib.pyplot as plt
import time
from datetime import datetime

# Get the current date and time
now = datetime.now()

# Format the date and time
formatted_date = now.strftime('%Y-%m-%d_%H-%M-%S')

# Create a filename using the formatted date and time
filename = f'arduino_data_{formatted_date}.csv'


# Open the serial port.
ser = serial.Serial('COM9', 9600)

ser.reset_input_buffer()

# Initialize an empty dictionary to hold the data.
data = {}

# Initialize a figure for plotting.
plt.figure()

# Open the CSV file for writing.
with open(filename, 'a', newline='\n') as csvfile:
    # Initialize the CSV writer.
    writer = csv.writer(csvfile)

    # This loop runs forever, continuously reading data and updating the plot.
    while True:
        # Read a line of data from the Arduino.
        line = ser.readline().decode('utf-8').strip()

        # Split the line into key-value pairs.
        pairs = line.split(',')

        # Process each key-value pair.
        row = []
        for pair in pairs:
            if line[0] != "," and pair.count(":") ==1 :
                key, value = pair.split(':')

                # Add the value to the list of values for this key.
                if key not in data:
                    data[key] = []
                data[key].append(float(value))

                # Add the value to the row.
                row.append(value)

        # Write the row to the CSV file.
        writer.writerow(row)

        # Clear the figure.
        plt.clf()

        # Plot the data.
        for key, values in data.items():
            plt.plot(values, label=key)

        # Add a legend.
        plt.legend()

        # Redraw the figure.
        plt.pause(0.01)

# Close the serial port.
ser.close()
