#scp C:\Users\markl\OneDrive\Documents\GitHub\Truck\Dash\main.py mark@192.168.1.253:/home/mark
# sudo apt install python3-ttkbootstrap

import ttkbootstrap as ttk
from ttkbootstrap.constants import *
from tkinter import Frame, X, StringVar
import time
import sys

app = ttk.Window()

style = ttk.Style(theme='darkly')

#app.attributes('-fullscreen', True)
frame = Frame(app)
frame.pack()

dict_kvp = {'Temperature': 40, 'Pressure': 0, 'Speed': 0, 'RPM': 0, 'Gear': 0, 'Gas':0}

meters = {}

meter = ttk.Meter(
    frame,
    metersize=180,
    padding=5,
    amountused=40,
    metertype="semi",
    arcrange=120,
    arcoffset=270,
    amounttotal=100,
    subtext='Fuel',
    interactive=False,
    textright='%'
)
meter.pack(side='left')
meter.step(10)
meter.step(-15)
meter.configure(subtext='Fuel')
meters['Fuel'] = meter
#-----------------------------------------------------
meter = ttk.Meter(
    frame,
    metersize=180,
    padding=5,
    amountused=40,
    metertype="semi",
    arcrange=120,
    arcoffset=270,
    amounttotal=100,
    subtext='Temp',
    interactive=False,
    textright='F'
)
meter.pack(side='left')
meter.step(10)
meter.step(-15)
meter.configure(subtext='Temp')
meters['Temp'] = meter
#-----------------------------------------------------
meter = ttk.Meter(
    frame,
    metersize=180,
    padding=5,
    amountused=40,
    metertype="semi",
    arcrange=180,
    arcoffset=180,
    amounttotal=100,
    subtext='MPH',
    interactive=False
)
meter.pack(side='left')
meter.step(10)
meter.step(-15)
meter.configure(subtext='MPH')
meters['MPH'] = meter
#-----------------------------------------------------
meter = ttk.Meter(
    frame,
    metersize=180,
    padding=5,
    amountused=2200,
    metertype="semi",
    arcrange=180,
    arcoffset=180,
    amounttotal=6000,
    subtext='RPM',
    interactive=False
)
meter.pack(side='left')
meter.step(10)
meter.step(-15)
meter.configure(subtext='RPM')
meters['RPM'] = meter
#-----------------------------------------------------
meter = ttk.Meter(
    frame,
    metersize=180,
    padding=5,
    amountused=40,
    metertype="semi",
    arcrange=120,
    arcoffset=150,
    amounttotal=100,
    subtext='EPC Pressure',
    interactive=False,
    textright='Psi'
)
meter.pack(side='left')
meter.step(10)
meter.step(-15)
meter.configure(subtext='EPC')
meters['EPC'] = meter
#-----------------------------------------------------
meter = ttk.Meter(
    frame,
    metersize=180,
    padding=5,
    amountused=40,
    metertype="semi",
    arcrange=120,
    arcoffset=150,
    amounttotal=100,
    subtext='OI Pressure',
    interactive=False,
    textright='Psi'
)
meter.pack(side='left')
meter.step(10)
meter.step(-15)
meter.configure(subtext='Oil')
meters['Oil'] = meter
#-----------------------------------------------------


def update_meters(new_dict):
    for key, value in new_dict.items():
        if key in meters:
            meters[key].configure(amountused=value)
    app.after(100, update_meters, new_dict)  # 100 milliseconds = 0.1 seconds

def stop_script():
    sys.exit()

#update_meters(dict_kvp)

stop_button = ttk.Button(app, text="Stop", command=stop_script)
stop_button.pack()

text_box = ttk.Text(app, height=4)
text_box.pack(fill=X)

app.mainloop()