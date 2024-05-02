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
import numpy as np
import os
from queue import Queue
import csv


os_type = platform.system()
bus = None
count = 0

if os_type == "Linux":
    bus = can.interface.Bus(channel='can0', bustype='socketcan')

enableDisplay = True


#if enableDisplay:
import ttkbootstrap as ttk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure

app = ttk.Window()
style = ttk.Style(theme='darkly')

if os_type == "Linux":
    app.attributes('-fullscreen', True)

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
'ShiftMode' : 0,
'EPCPWM':0,
'Gear' : 0,
'TCC' : 0,
'Fuel': 0,
'Oil' : 0,
'Odometer' : 0.0000,
'Tripometer' : 0.00000
}

meters = {}
labels = {}
t1 = None
t2 = None
LastMessageTime = datetime.now()
logfilename = datetime.now().strftime("%m%d%y_%H%M")
logfilename = logfilename + ".csv"
odofilename = 'miles.odo'

def toggle_led(led):
    if led.cget("bg") == "gray":
        led.config(bg="green")
    else:
        led.config(bg="gray")

def power_off(filepath,values):
    try:
        with open(filepath, 'w') as file:
            file.write(str(int(values['Odometer'])) + ',' + str(int(values['Tripometer'])))
        replace_text(meters['Log'], f"Data saved to {filepath}")
    except FileNotFoundError:
        replace_text(meters['Log'], f"Error: File '{filepath}' not found.")
    except Exception as e:
        replace_text(meters['Log'], f"Error: {e}")

    #TODO upload csv files
    upload_csv()
    os.system('sudo shutdown -h now')
    quit()

def power_on(filepath,values):
    try:
        with open(filepath, 'r') as file:
            content = file.read()
            integers = content.split(',')
            values['Odometer'], values['Tripometer'] = map(int, integers)
    except FileNotFoundError:
        replace_text(meters['Log'], f"File '{filepath}' not found. Please check the file path.")
    except ValueError:
        replace_text(meters['Log'], "Error: The file does not contain valid integers separated by a comma.")

    #TODO upload csv files
    upload_csv()

def upload_csv():
    #TODO upload csv files
    print("TODO...")

def screen_on():
    os.system('echo 0 | sudo tee /sys/class/backlight/rpi_backlight/bl_power')

def screen_off():
    os.system('echo 1 | sudo tee /sys/class/backlight/rpi_backlight/bl_power')

def replace_text(text_widget, new_text):
    text_widget.delete('1.0', ttk.END)
    text_widget.insert('1.0', new_text)

def calculate_distance(speed_mph,time_ms):
    mpms = speed_mph / 3600000  # 1 hour = 3600000 milliseconds
    distance = mpms * time_ms
    return distance

def receive_can_messages(values,bus,LastMessageTime,out_q):
    global count

    while True:
        if os_type == "Linux":
            canMsg = bus.recv(0.01)

            if canMsg is not None:  
                canMsg = cast(can.Message,canMsg)

                if (LastMessageTime - datetime.now()).total_seconds() >3:
                    print("CAN Comms detected!")
                    screen_on()

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
                    values['TCC'] = canMsg.data[0]
                    values['Gear'] = canMsg.data[1]
                    values['MPH'] = canMsg.data[2]
                    values['Oil'] = canMsg.data[3]
                    values['Odometer'] = values['Odometer'] + calculate_distance(canMsg.data[2],200)
                    values['Tripometer'] = values['Tripometer'] +  calculate_distance(canMsg.data[2],200)

                elif canMsg.arbitration_id == 1802:
                    values['ShiftMode'] = canMsg.data[0]
                    values['EPCPSI'] = round(canMsg.data[3] | (canMsg.data[2] << 8))
                    values['EPCPWM'] = canMsg.data[4]
                    #values['epcSetPointValue'] = canMsg.data[1]    5 
                    #values['ISS'] = canMsg.data[6 ]                6
                    values['Fuel'] = round(canMsg.data[7]/2.55)
                    #update the chart?
                    #meters['cnv'].draw()

                #steeringwheel
                elif canMsg.arbitration_id == 1601:
                    txt = "Manual shift detected: "                    
                    for x in range(5):
                        txt = txt + str(canMsg.data[x]) + ", "
                    replace_text(meters['Log'], txt)

                    if canMsg.data[0]:
                        replace_text(meters['Log'], "powering off!")
                        power_off(odofilename,values)


                LastMessageTime = datetime.now()        
                    
                if not enableDisplay:
                    print("ID:" + str(canMsg.arbitration_id))
                    s = " Data: "
                    for x in range(canMsg.dlc):
                        s = s + str(canMsg.data[x]) + " "
                    print(s)
                    print("")

                out_q.put(values)

            else:
                if (LastMessageTime - datetime.now()).total_seconds() >3:
                    replace_text(meters['Log'], "Timeout")
                    screen_off()
                    time.sleep(15)

        else:
            count += 1
            time.sleep(.05)
            values['RPM'] = count
            if values['TCC'] == 1:
                values['TCC'] = 0
            else:
                values['TCC'] = 1

            values['Fuel'] =11             
            values['Voltage'] =10
            values['Oil'] =50
            values['Temp'] =221
            values['Odometer'] = values['Odometer'] + calculate_distance(values['RPM'],200)
            values['Tripometer'] = values['Tripometer'] +  calculate_distance(values['RPM'],200)

            meters['cnv'].draw()
            out_q.put(values)
            

def update(meters,values):
    if meters['RPM'].amountusedvar.get() != values['RPM']:
        meters['RPM'].amountusedvar.set(values['RPM'])
        if values['RPM'] < 500 or values['RPM'] > 5000:
            meters['RPM'].configure(bootstyle='danger')
        else:
            meters['RPM'].configure(bootstyle='default')
    # if meters['Bar'].amountusedvar.get() != values['Bar']:
    #     meters['Bar'].amountusedvar.set(values['Bar'])
    # if meters['MAP'].amountusedvar.get() != values['MAP']:
    #     meters['MAP'].amountusedvar.set(values['MAP'])
    if meters['Temp'].amountusedvar.get() != values['Temp']:
        meters['Temp'].amountusedvar.set(values['Temp'])
        if values['Temp'] > 220:
            meters['Temp'].configure(bootstyle='danger')
        else:
            meters['Temp'].configure(bootstyle='default')

    if meters['TPS']['value'] != values['TPS']:
        meters['TPS']['value'] = values['TPS']
    #    meters['TPS'].configure(value= values['RPM'])
    if meters['Voltage'].amountusedvar.get() != values['Voltage']:
        meters['Voltage'].amountusedvar.set(values['Voltage'])
        if values['Voltage'] < 11 or values['Voltage'] > 15:
            meters['Voltage'].configure(bootstyle='danger')
        else:
            meters['Voltage'].configure(bootstyle='default')
        
    if meters['MPH'].amountusedvar.get() != values['MPH']:
        meters['MPH'].amountusedvar.set(values['MPH'])
    replace_text(meters['Trip'], "{:.2f}".format(values['Tripometer']))
    replace_text(meters['Odo'], "{:.2f}".format(values['Odometer']))

    if meters['EPCPSI'].amountusedvar.get() != values['EPCPSI']:
        meters['EPCPSI'].amountusedvar.set(values['EPCPSI'])
        labels['EPCPSI'].config(text = values['EPCPSI'])
        #meters['epc_plt'].set_ydata(values['EPCPSI'])
    # if meters['LinePSI'].amountusedvar.get() != values['LinePSI']:
    #     meters['LinePSI'].amountusedvar.set(values['LinePSI'])
    if meters['EPCPWM']['value'] != values['EPCPWM']:
        meters['EPCPWM']['value'] = values['EPCPWM']
    if meters['Gear'].amountusedvar.get() != values['Gear']:
        meters['Gear'].amountusedvar.set(values['Gear'])
        labels['Gear'].config(text = values['Gear'])
    
    if values['TCC'] == 1:
        meters['TCC'].config(bg="green")
    else:
        meters['TCC'].config(bg="gray")

    if meters['Fuel'].amountusedvar.get() != values['Fuel']:
        meters['Fuel'].amountusedvar.set(values['Fuel'])
        if values['Fuel'] < 5:
            meters['Fuel'].configure(bootstyle='danger')
        elif values['Fuel'] < 15:
            meters['Fuel'].configure(bootstyle='warning')
        else:
            meters['Fuel'].configure(bootstyle='default')
        

    if meters['Oil'].amountusedvar.get() != values['Oil']:
        meters['Oil'].amountusedvar.set(values['Oil'])
        if values['Oil'] < 20:
            meters['Oil'].configure(bootstyle='danger')
        else:
            meters['Oil'].configure(bootstyle='default')


    app.after(10,update,meters,values)  

def logdata(in_q):
    fieldnames = values.keys()
    with open(logfilename, 'a', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        if csvfile.tell() == 0:
            writer.writeheader()
        while True:
            time.sleep(0.05)
            if in_q.qsize() > 0:
                data = in_q.get()
                fieldnames = data.keys()
                writer.writerow(data)
                csvfile.flush()
                q.task_done()

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
    #graph area
    fig = Figure(figsize=(6, 2), dpi=100)
    t = np.arange(0, 3, .01)
    ax = fig.add_subplot(111)
    ax.set_ylim(0,200)

    # line, = ax.plot(values[''])    
    # meters['epc_plt'] = line

    line, = ax.plot(values['EPCPSI'])    
    meters['epc_plt'] = line
    

    # Add the second line
    #y2 = np.cos(4 * np.pi * t)  # Example second data
    #ax.plot(t, y2)
        
    fig.patch.set_facecolor('#222222')
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.spines['bottom'].set_visible(False)
    ax.spines['left'].set_visible(False)
    ax.tick_params(bottom=False,labelbottom=False,left=False,labelleft=False)
    ax.set_facecolor('#222222')

    canvas = FigureCanvasTkAgg(fig, master=frame)  # A tk.DrawingArea.
    canvas.draw()
    canvas.get_tk_widget().place(x=700,y=-5)
    meters['cnv'] = canvas

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

    label = ttk.Label(frame, text="0", font=large_font,foreground="#375a7f")
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
    #   Acceleration and deceleration indicator
    # decel doesn't work yet since ttk doesn't natively support right to left bars.

    decelx = 585
    decely = 420

    progressbar = ttk.Progressbar(frame, value=0, orient='horizontal',length=170)
    progressbar.place(x=decelx,y=decely,width=100)
    meters['deceleration'] = progressbar

    progressbar = ttk.Progressbar(frame, value=0, orient='horizontal',length=170)
    progressbar.place(x=decelx+105,y=decely,width=100)
    meters['deceleration'] = progressbar


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

    label2 = ttk.Label(frame, text="Gear", font=med_font)
    label2.place(x=1830, y=210 + 140)

    progressbar = ttk.Progressbar(frame, value=0, orient='vertical',length=170)
    progressbar.place(x=1890,y=210 + 8,width=20)
    meters['TPS'] = progressbar

    label3 = ttk.Label(frame, text="Load", font=small_font)
    label3.place(x=1885, y=210+ 180)


    #-----------------------------------------------------
    #   TCC indicator

    
    tcc = ttk.Canvas(app, width=15, height=15, bg="gray", highlightthickness=0)
    tcc.place(x=1830,y=265)
    meters['TCC'] = tcc

    # tcc = ttk.Radiobutton(frame, style="info",text="TCC")
    # tcc
    # meters['TCC'] = tcc

    # checkengine = ttk.Radiobutton(frame, style="warning",text="Check Engine")
    # checkengine.place(x=500,y=10)
    # meters['Check'] = checkengine


    #-----------------------------------------------------
    text_box = ttk.Text(frame, height=2)
    text_box.place(x=0,y=460,relwidth=1)
    text_box.insert('1.0',"Initialized.. Connecting to CAN...")
    meters['Log'] = text_box


    label = ttk.Label(frame, text="Odometer", font=small_font)
    label.place(x=750, y=350)
    odo = ttk.Text(frame, height=1)
    odo.place(x=750,y=370,width=100)
    odo.tag_configure('right', justify='right')
    odo.insert('0.0',"347,349")
    meters['Odo'] = odo

    label = ttk.Label(frame, text="Tripometer", font=small_font)
    label.place(x=550, y=350)
    trip = ttk.Text(frame, height=1)
    trip.place(x=550,y=370,width=100)
    trip.tag_configure('right', justify='right')
    trip.insert('0.0',"0.0010")
    meters['Trip'] = trip

    #-----------------------------------------------------

    my_button = ttk.Button(frame, text="Power Off", command=lambda: power_off(odofilename,values))
    my_button.place(x=1810,y=425,width=100)
    #my_button.pack()


    #-----------------------------------------------------

    #endregion

    power_on(odofilename,values)

    q = Queue()
    recv_thread = threading.Thread(target=receive_can_messages,args=(values,bus,LastMessageTime,q))
    recv_thread.start()

    log_thread = threading.Thread(target=logdata, args=(q,))
    log_thread.start()

    update(meters,values)
    app.mainloop()
else:
    q = Queue()
    print("started!")
    recv_thread = threading.Thread(target=receive_can_messages,args=(values,bus,LastMessageTime,q))
    recv_thread.start()
    
    while True:
        #print("this")
        time.sleep(.1)
