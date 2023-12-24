#scp C:\Users\markl\OneDrive\Documents\GitHub\Truck\Dash\main.py mark@192.168.1.253:/home/mark
# sudo apt install python3-ttkbootstrap
#start can:
#sudo ip link set can0 up type can bitrate 500000


from cgitb import text
from socket import timeout
from turtle import bgcolor, color, width
from numpy import angle
import ttkbootstrap as ttk
from ttkbootstrap.constants import *
from tkinter import Frame, X, StringVar
import time
from PIL import Image,ImageTk
import sys
import platform
import can


app = ttk.Window()
style = ttk.Style(theme='darkly')
#app.attributes('-fullscreen', True)
frame = ttk.Frame(app, width=1920, height=515)
frame.pack()
os_type = platform.system()
timeout_counter = 0
large_font = ttk.font.Font(family='Helvetica', size=20, weight='bold')
xl_font = ttk.font.Font(family='Helvetica', size=30, weight='bold')
med_font = ttk.font.Font(size=15)
small_font = ttk.font.Font(size=8)
bus = None
if os_type == "Linux":
    bus = can.interface.Bus(channel='can0', bustype='socketcan')
enableDisplay = False

values = {
'rpmValue' : 0,
'tpsValue' : 0,
'tempValue' : 0,
'speedValue' : 0,
'epcPsiValue' : 0,
'epcPWMValue':0,
'gearValue' : 0,
'tccValue' : 0,
'tpsValue':0
}

meters = {}
labels = {}

def receive_can_messages():
    global timeout_counter
    global values
    global bus
    #bus = can.interface.Bus(channel=channel, bustype='socketcan')
    
    while True:
        canMsg = bus.recv(0.01)
        if canMsg is None:  
            break

        print(canMsg.arbitration_id)

        if canMsg.arbitration_id == 1520:
            values['rpmValue'] = canMsg.data[7] | (canMsg.data[6] << 8)
        elif canMsg.arbitration_id == 1523:
            values['tpsValue'] = canMsg.data[1] | (canMsg.data[0] << 8)
            
        elif canMsg.arbitration_id == 1702:
            values['epcPWMValue'] = canMsg.data[0]
            values['gearValue'] = canMsg.data[3]
            values['tccValue'] = canMsg.data[2]

        text_box.insert('1.0',str(canMsg.arbitration_id) + " ")


def update():

    global values
    
    if os_type == "Linux":
        receive_can_messages()

    meters['RPM'].configure(amountused=values['rpmValue'])
    meters['Load'].configure(value=values['tpsValue'])
    meters['Temp'].configure(amountused=values['tempValue'])
    meters['Gear'].configure(amountused=values['gearValue'])
    meters['EPC'].configure(amountused=values['epcPWMValue'])
    meters['MPH'].configure(amountused=values['speedValue'])


    #100ms = 10fps.. so maybe we can increase this later
    app.after(10, update)  


#region meters
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
    #subtext='EPC',
    interactive=False,
    #textleft='Psi',
    meterthickness=30,
    showtext=False
)
meter.place(x=1750,y=0)
meters['EPC'] = meter

label = ttk.Label(frame, text="120", font=large_font,foreground="#375a7f")
label.place(x=1810, y=90)
labels['epcPsi'] = label

label = ttk.Label(frame, text="Psi")
label.place(x=1860, y=105)
label = ttk.Label(frame, text="EPC", font=med_font)
label.place(x=1830, y=140)

progressbar = ttk.Progressbar(frame, value=75, orient='vertical',length=170)
progressbar.place(x=1890,y=8,width=20)
meters['epcPWM'] = progressbar
    
label = ttk.Label(frame, text="PWM", font=small_font)
label.place(x=1885, y=180)


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
    
    interactive=False,
    meterthickness=30,
    showtext=False
)
meter.place(x=1750,y=210)
meters['Gear'] = meter

label = ttk.Label(frame, text="1", font=xl_font,foreground="#375a7f")
label.place(x=1840, y=210 + 90)
labels['Gear'] = label

label = ttk.Label(frame, text="Gear", font=med_font)
label.place(x=1830, y=210 + 140)

progressbar = ttk.Progressbar(frame, value=75, orient='vertical',length=170)
progressbar.place(x=1890,y=210 + 8,width=20)
meters['Load'] = progressbar

label = ttk.Label(frame, text="Load", font=small_font)
label.place(x=1885, y=210+ 180)


#-----------------------------------------------------
#   TCC indicator

tcc = ttk.Radiobutton(style="info",text="TCC")
tcc.place(x=1830,y=265)
meters['TCC'] = tcc

checkengine = ttk.Radiobutton(style="warning",text="Check Engine")
checkengine.place(x=500,y=10)
meters['Check'] = checkengine


#-----------------------------------------------------
text_box = ttk.Text(frame, height=2)
text_box.place(x=0,y=460,relwidth=1)
text_box.insert('1.0',"Initialized.. Connecting to CAN...")

odo = ttk.Text(frame, height=1)
odo.place(x=650,y=390,width=100)
odo.tag_configure('right', justify='right')
odo.insert('0.0',"347,000")

#-----------------------------------------------------

#endregion

update()
app.mainloop()