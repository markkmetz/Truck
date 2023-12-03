import pandas as pd
import matplotlib.pyplot as plt

current_gear = 1


bettercurves = {
    "FirstUP": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    "SecondDown": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    "SecondUp": [10, 10, 12, 15, 21, 27, 33, 40, 48, 58, 68],
    "ThirdDown": [8, 8, 9, 9, 9, 11, 13, 15, 20, 28, 47],
    "ThirdUp": [27, 28, 31, 41, 51, 60, 75, 85, 93, 100, 100],
    "FourthDown": [20, 20, 23, 30, 39, 47, 55, 60, 66, 74, 79]
}

def calc_curve_value(cname, load):
    l2 = int(load / 10)
    m2 = (bettercurves[cname][l2 + 1] - bettercurves[cname][l2])
    b = bettercurves[cname][l2] - l2 * m2
    return (m2 * l2) + bettercurves[cname][l2]

def CalculateGear(oss_avg_speed,load_avg,rpm_value):
    if current_gear == 1:
        if (rpm_value > 1700 or rpm_value == 0) or oss_avg_speed > 5:
            return 2
        else:
            return 1
    elif current_gear == 2:
        if oss_avg_speed > calc_curve_value('SecondUp', load_avg):
            return 3
        elif oss_avg_speed < 2 and rpm_value != 0 and rpm_value < 1400:
            return 1
        else:
            return 2
    elif current_gear == 3:
        if oss_avg_speed > calc_curve_value('ThirdUp', load_avg):
            return 4
        elif oss_avg_speed < calc_curve_value('ThirdDown', load_avg):
            return 2
        else:
            return 3
    elif current_gear == 4:
        if oss_avg_speed < calc_curve_value('FourthDown', load_avg):
            return 3
        else:
            return 4
    else:
        return 0

# Load the CSV file
df = pd.read_csv('Tools\\v12.02.23_successfultestdrive_2023-12-02_20-52-22.csv')
# Add the first three columns together to create a fourth column
#load,rpm,Speed,Gear

df['avgspeed'] = df['Speed'].rolling(window=5).mean()
gear = []        
for index, row in df.iterrows():
    current_gear = CalculateGear(row['Speed'],row['load'],row['rpm'])
    gear.append(current_gear*10)
    

df['Gear'] = gear


# # Plot all four columns
plt.figure(figsize=(10, 6))
plt.plot(df['Gear'], label='Gear')
plt.plot(df['Speed'], label='Speed')
plt.plot(df['load'], label='load')


plt.legend()
plt.show()
