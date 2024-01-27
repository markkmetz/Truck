
import time
from PIL import Image,ImageTk
import sys
import platform
import can

os_type = platform.system()


#reveived: Timestamp: 1703181730.242524    ID:      5f0    S Rx                DL:  8    00 72 00 00 00 00 00 00     Channel: can0
def testcanf():
    bus = can.interface.Bus(channel='can0', bustype='socketcan')
    while True:
        canMsg = bus.recv(.5)
        if canMsg is not None:  
           if canMsg.arbitration_id == "5f0":
                rpmValue = canMsg.data[7] | (canMsg.data[6] << 8)
           elif canMsg.arbitration_id == "5f3":
                loadValue = canMsg.data[1] | (canMsg.data[0] << 8)
            
        else:
            print("Timeout")

#testcan()

class testcan:
    def __init__(self):
        self.data = 0
        self.Timestamp = 0.00

tst = testcan()
print(tst)