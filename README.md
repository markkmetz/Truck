# Truck Repo
## Currently there are 3 components to this project.
### 1.) Transmission controller
####   Responsible for controlling the 4r75
#####     Uses CAN to get data (TPS) from Microsquirt Controller.
#####     Uses CAM to get data (button presses) from steering wheel controller
### 2.) Steering wheel component
####   Responsible for sending button presses on the steering wheel to the Transmission Controller
### 3.) Gauge Cluster - WIP
####   Responsible for recieving data over CAN-BUS and displaying them on the gauges.



# test build instructions

## Requirements
### https://github.com/emlearn/emlearn

## Build

### open up dev console and run 'code'
### cd .\Transmission_Controller\main\src\main\
### cl /D TEST /EHsc test.cpp main.cpp mock2515.cpp /link /out:test.exe
### or
### cl /D TEST /I C:\Users\markl\AppData\Local\Programs\Python\Python312\Lib\site-packages\emlearn /EHsc main.cpp test.cpp mock2515.cpp /link /out:test.exe

### test.exe