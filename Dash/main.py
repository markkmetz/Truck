# scp C:\Users\markl\OneDrive\Documents\GitHub\Truck\Dash\main.py mark@192.168.1.253:/home/mark
# sudo apt install python3-ttkbootstrap
# start can:
# sudo ip link set can0 up type can bitrate 500000
# /.local/lib/python3.11/site-packages/ttkbootstrap/widgets.py

import time
import platform
from tkinter import Y
import can
from typing import cast, Any
import threading
from datetime import datetime

os_type = platform.system()
bus = None
count = 0

if os_type == "Linux":
    bus = can.interface.Bus(channel='can0', bustype='socketcan')

enableDisplay = True


if enableDisplay:
    import ttkbootstrap as ttk
    app = ttk.Window()
    style = ttk.Style(theme='darkly')
    #app.attributes('-fullscreen', True)
    frame = ttk.Frame(app, width=1920, height=515)
    frame.pack()
    large_font = ttk.font.Font(family='Helvetica', size=20, weight='bold')
    xl_font = ttk.font.Font(family='Helvetica', size=30, weight='bold')
    med_font = ttk.font.Font(size=15)
    small_font = ttk.font.Font(size=8)


values = {
'RPM' : 0,
'Bar': 0,
'MAP':0,
'Temp':0,
'TPS' : 0,
'Voltage':0,
'MPH' : 0,
'EPCPSI' : 0,
'LinePSI' : 0,
'EPCPWM':0,
'Gear' : 0,
'TCC' : 0
}

meters = {}
labels = {}
t1 = None
t2 = None

def receive_can_messages(values,bus):
    global count

    while True:
        if os_type == "Linux":
            canMsg = bus.recv(0.01)
            if canMsg is not None:  
                canMsg = cast(can.Message,canMsg)
                
                #microsquirt data------------------------
                if canMsg.arbitration_id == 1520:
                    values['RPM'] = canMsg.data[7] | (canMsg.data[6] << 8)
                elif canMsg.arbitration_id == 1522:
                    values['Bar'] = (canMsg.data[1] | (canMsg.data[0] << 8))/10
                    values['MAP'] = (canMsg.data[3] | (canMsg.data[2] << 8))/10
                    values['Temp'] = (canMsg.data[7] | (canMsg.data[6] << 8))/10
                elif canMsg.arbitration_id == 1523:
                    values['TPS'] = (canMsg.data[1] | (canMsg.data[0] << 8))/10
                    values['Voltage'] = (canMsg.data[3] | (canMsg.data[2] << 8))/10
                
                #Transmission controller data-------------
                elif canMsg.arbitration_id == 1702:
                    values['EPCPWM'] = canMsg.data[0]
                    #values['epcSetPointValue'] = canMsg.data[1]
                    values['TCC'] = canMsg.data[2]
                    values['Gear'] = canMsg.data[3]
                    #values['ISS'] = canMsg.data[4]
                    values['MPH'] = canMsg.data[5]
                    values['LinePSI'] = (canMsg.data[7] | (canMsg.data[6] << 8))/10
                    values['EPCPSI'] = (canMsg.data[9] | (canMsg.data[8] << 8))/10

                if not enableDisplay:
                    print("ID:" + str(canMsg.arbitration_id))
                    s = " Data: "
                    for x in range(canMsg.dlc):
                        s = s + str(canMsg.data[x]) + " "
                    print(s)
                    print("")

        else:
            print(count)
            count += 1
            time.sleep(.05)
            values['RPM'] = count

def update(meters,values):
    if meters['RPM'].amountusedvar.get() != values['RPM']:
        meters['RPM'].amountusedvar.set(values['RPM'])
    # if meters['Bar'].amountusedvar.get() != values['Bar']:
    #     meters['Bar'].amountusedvar.set(values['Bar'])
    # if meters['MAP'].amountusedvar.get() != values['MAP']:
    #     meters['MAP'].amountusedvar.set(values['MAP'])
    if meters['Temp'].amountusedvar.get() != values['Temp']:
        meters['Temp'].amountusedvar.set(values['Temp'])

    if meters['TPS']['value'] != values['TPS']:
        meters['TPS']['value'] = values['TPS']
    #    meters['TPS'].configure(value= values['RPM'])
    if meters['Voltage'].amountusedvar.get() != values['Voltage']:
        meters['Voltage'].amountusedvar.set(values['Voltage'])
    if meters['MPH'].amountusedvar.get() != values['MPH']:
        meters['MPH'].amountusedvar.set(values['MPH'])
    if meters['EPCPSI'].amountusedvar.get() != values['EPCPSI']:
        meters['EPCPSI'].amountusedvar.set(values['EPCPSI'])
    # if meters['LinePSI'].amountusedvar.get() != values['LinePSI']:
    #     meters['LinePSI'].amountusedvar.set(values['LinePSI'])
    if meters['EPCPWM']['value'] != values['EPCPWM']:
        meters['EPCPWM']['value'] = values['EPCPWM']
    if meters['Gear'].amountusedvar.get() != values['Gear']:
        meters['Gear'].amountusedvar.set(values['Gear'])
    meters['TCC'].variable = values['TCC']

    app.after(10,update,meters,values)  


if enableDisplay:
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
        amountused=0,
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
        subtext='Voltage',
        interactive=False,
        textright='V',
        meterthickness=30
    )
    meter.place(x=-80,y=210)
    meters['Voltage'] = meter


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
        amountused=0,
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
        amountused=0,
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
    meters['EPCPSI'] = meter

    label = ttk.Label(frame, text="120", font=large_font,foreground="#375a7f")
    label.place(x=1810, y=90)
    labels['EPCPSI'] = label

    label = ttk.Label(frame, text="Psi")
    label.place(x=1860, y=105)
    label = ttk.Label(frame, text="EPC", font=med_font)
    label.place(x=1830, y=140)

    progressbar = ttk.Progressbar(frame, value=75, orient='vertical',length=170)
    progressbar.place(x=1890,y=8,width=20)
    meters['EPCPWM'] = progressbar
        
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

    label = ttk.Label(frame, text="P", font=xl_font,foreground="#375a7f")
    label.place(x=1840, y=210 + 90)
    labels['Gear'] = label

    label = ttk.Label(frame, text="Gear", font=med_font)
    label.place(x=1830, y=210 + 140)

    progressbar = ttk.Progressbar(frame, value=0, orient='vertical',length=170)
    progressbar.place(x=1890,y=210 + 8,width=20)
    meters['TPS'] = progressbar

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


    recv_thread = threading.Thread(target=receive_can_messages,args=(values,bus))
    recv_thread.start()
    update(meters,values)
    app.mainloop()
else:
    recv_thread = threading.Thread(target=receive_can_messages,args=(values,bus))
    recv_thread.start()
    print("started!")
    while True:
        #print("this")
        time.sleep(.1)