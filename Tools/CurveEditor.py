import enum
import matplotlib.pyplot as plt
from matplotlib.widgets import Button
import numpy as np
filename = 'Transmission_Controller/main/main.ino'
line_number =108
fig, ax = plt.subplots()
l = 0
index = 0
hindex=0

def enumcurve(i):
    match i:
        case 0:
            return "FirstUP"    
        case 1:
            return "SecondDown"    
        case 2:
            return "SecondUp"    
        case 3:
            return "ThirdDown"    
        case 4:
            return "ThirdUp"    
        case 5:
            return "FourthDown"    


# Open the .ino file and read from line 108
with open(filename, 'r') as file:
    lines = file.readlines()[line_number:line_number+6]

# Parse the data
data = {}
datalines = []
for line in lines:
    parts = line.split("{")
    name = parts[1].replace(",","")
    values = parts[2].split("}")[0].split(",")

    for i,txt in enumerate(values):
        values[i] = int(txt.replace(" ", "")) # type: ignore
    
        
    values = list(map(int, values))
    data[name.strip()] = values

# Plot the data
for name, values in data.items():
    l, = ax.plot(values, label=name)
    datalines.append(l)

def update_data(event):
    values[0] = 80
    l.set_ydata(values)
    fig.canvas.draw()
    for x in values:
        print(x)

def printnewstuff():
    print()
    arr = []
    for i in range(6):
        cname = enumcurve(i)
        str1 = "{" + str(cname) + "," + "     {"
        str2 = ""
        for x in data[cname]:
            str2 += str(x) + ", "
        str2 = str2[0:-2]
        str3 = "}, 0, 1}"
        if i !=5:
            str3 += ","

        print(str1 + str2 + str3)
        arr.append(str1 + str2 + str3)
    print()
    return arr

def up(event):
    global index
    index += 1
    if index > 5:
        index = 5
    print(enumcurve(index))
    print()

def down(event):
    global index
    index -= 1
    if index < 0:
        index = 0
    print(enumcurve(index))
    print()

def left(event):
    global hindex
    hindex -= 1
    if hindex <0:
        hindex = 0
    print(enumcurve(index))
    print("Load: "+ str(hindex))
    print("speed: " + str(data[enumcurve(index)][hindex]) + "mph")
    print()

def right(event):
    global hindex
    hindex += 1
    if hindex >10:
        hindex = 10
    print(enumcurve(index))
    print("Load: "+ str(hindex))
    print("speed: " + str(data[enumcurve(index)][hindex]) + "mph")
    print()

def increase(event):
    global index
    data[enumcurve(index)][hindex] += 1
    printnewstuff()
    datalines[index].set_ydata(data[enumcurve(index)])
    fig.canvas.draw()

def decrease(event):
    global index
    data[enumcurve(index)][hindex] -= 1
    printnewstuff()
    datalines[index].set_ydata(data[enumcurve(index)])
    fig.canvas.draw()

def save(event):
    arr = printnewstuff()
    with open(filename, 'r') as file:
        lines = file.readlines()
        for i in range(6):
            lines[line_number + i] = arr[i] + "\n"
        lines[line_number + 6] = "};\n"

    with open(filename, 'w') as file:
        file.writelines(lines)


up_ax = plt.axes([0.3, 0.00, 0.075, 0.075])
down_ax = plt.axes([0.4, 0.00, 0.075, 0.075])
left_ax = plt.axes([0.5, 0.00, 0.075, 0.075])
right_ax = plt.axes([0.6, 0.00, 0.075, 0.075])
inc_ax = plt.axes([0.7, 0.00, 0.075, 0.075])
dec_ax = plt.axes([0.8, 0.00, 0.075, 0.075])
save_ax = plt.axes([0.2, 0.00, 0.075, 0.075])

upbutton = Button(up_ax, 'Up')
downbutton = Button(down_ax, 'Down')
leftbutton = Button(left_ax, 'Left')
rightbutton = Button(right_ax, 'Right')
incbutton = Button(inc_ax, 'increase')
decbutton = Button(dec_ax, 'decrease')
savebutton = Button(save_ax, 'save')

upbutton.on_clicked(up)
downbutton.on_clicked(down)
leftbutton.on_clicked(left)
rightbutton.on_clicked(right)
incbutton.on_clicked(increase)
decbutton.on_clicked(decrease)
savebutton.on_clicked(save)

ax.legend()
ax.grid(True)
plt.legend()
plt.show()
