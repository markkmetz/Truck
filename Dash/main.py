#scp C:\Users\markl\OneDrive\Documents\GitHub\Truck\Dash\main.py mark@192.168.1.253:/home/mark
# sudo apt install python3-ttkbootstrap

from cgitb import text
from turtle import bgcolor, width
import ttkbootstrap as ttk
from ttkbootstrap.constants import *
from tkinter import Frame, X, StringVar
import time
from PIL import Image,ImageTk
import sys

app = ttk.Window()
#app.minsize(1920,515)

style = ttk.Style(theme='darkly')

#app.attributes('-fullscreen', True)
frame = ttk.Frame(app, width=1920, height=515)
#frame.pack_propagate(0)  # Don't shrink or expand the frame
frame.pack()

def toggle_led():
    if led_indicator['style'] == 'Green.TLabel':
        led_indicator['style'] = 'Red.TLabel'
    else:
        led_indicator['style'] = 'Green.TLabel'


meters = {}
#-----------------------------------------------------
#    TEMPERATURE
meter = ttk.Meter(
    frame,
    metersize=250,
    padding=5,
    amountused=200,
    metertype="semi",
    arcrange=120,
    arcoffset=270,
    amounttotal=260,
    subtext='Temp',
    interactive=False,
    textright='F',
    meterthickness=30
)
meter.place(x=110,y=0)
meters['Temp'] = meter

#-----------------------------------------------------
#    FUEL
meter = ttk.Meter(
    frame,
    metersize=250,
    padding=5,
    amountused=40,
    metertype="semi",
    arcrange=120,
    arcoffset=270,
    amounttotal=100,
    subtext='Fuel',
    interactive=False,
    textright='%',
    meterthickness=30
)
meter.place(x=-80,y=0)
meters['Fuel'] = meter


#-----------------------------------------------------
#   VOLTAGE
meter = ttk.Meter(
    frame,
    metersize=250,
    padding=5,
    amountused=12,
    metertype="semi",
    arcrange=120,
    arcoffset=270,
    amounttotal=18,
    subtext='Volt',
    interactive=False,
    textright='V',
    meterthickness=30
)
meter.place(x=-80,y=210)
meters['Volt'] = meter


#-----------------------------------------------------
#   SPEEDOMETER MPH
meter = ttk.Meter(
    frame,
    metersize=600,
    padding=5,
    amountused=40,
    metertype="semi",
    arcrange=180,
    arcoffset=180,
    amounttotal=100,
    textright='MPH',
    interactive=False,
    meterthickness=30
)
meter.place(x=390,y=140)
meters['MPH'] = meter


#-----------------------------------------------------
#   TACH    RPM
meter = ttk.Meter(
    frame,
    metersize=600,
    padding=5,
    amountused=2200,
    metertype="semi",
    arcrange=180,
    arcoffset=180,
    amounttotal=6000,
    textright='RPM',
    interactive=False,
    meterthickness=30
)
meter.place(x=1000,y=140)
meters['RPM'] = meter

#-----------------------------------------------------
#       OIL PRESSURE
meter = ttk.Meter(
    frame,
    metersize=250,
    padding=5,
    amountused=65,
    metertype="semi",
    arcrange=120,
    arcoffset=150,
    amounttotal=100,
    subtext='Oil',
    interactive=False,
    textright='Psi',
    meterthickness=30
)
meter.place(x=1560,y=0)
meters['Oil'] = meter

#-----------------------------------------------------
#   EPC PRESSURE
meter = ttk.Meter(
    frame,
    metersize=250,
    padding=5,
    amountused=120,
    metertype="semi",
    arcrange=120,
    arcoffset=150,
    amounttotal=250,
    subtext='EPC',
    interactive=False,
    textright='Psi',
    meterthickness=30
)
meter.place(x=1750,y=0)
meters['EPC'] = meter


#-----------------------------------------------------
#   GEAR indicator
meter = ttk.Meter(
    frame,
    metersize=250,
    padding=5,
    amountused=1,
    metertype="semi",
    arcrange=120,
    arcoffset=150,
    amounttotal=4,
    subtext='Gear',
    interactive=False,
    meterthickness=30
)
meter.place(x=1750,y=210)
meters['Gear'] = meter

#-----------------------------------------------------
#   TCC indicator

style.configure('Green.TLabel', background='green', foreground='green', borderwidth=1, relief="solid",width=3)
style.configure('Red.TLabel', background='red', foreground='red', borderwidth=1, relief="solid")

led_indicator = ttk.Label(app, style='Red.TLabel',text="sdf",width=3)
led_indicator.place(x=1840,y=300)
toggle_led()


#-----------------------------------------------------

def update_meters(new_dict):
    for key, value in new_dict.items():
        if key in meters:
            meters[key].configure(amountused=value)
    app.after(100, update_meters, new_dict)  # 100 milliseconds = 0.1 seconds

def stop_script():
    sys.exit()

text_box = ttk.Text(frame, height=2)
text_box.place(x=0,y=460,relwidth=1)

#-----------------------------------------------------
app.mainloop()