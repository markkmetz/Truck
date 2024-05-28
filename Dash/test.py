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
import dropbox



APP_TOKEN = ""

with open("token.txt", 'r') as file:
    APP_TOKEN = file.read()


def find_csv_filenames(path_to_dir, suffix=".csv"):
    
    if len(path_to_dir) > 0:
        filenames = os.listdir(path_to_dir)
    else:
        filenames = os.listdir()

    return [filename for filename in filenames if filename.endswith(suffix)]


def checkforupdates():
    # https://raw.githubusercontent.com/markkmetz/Truck/main/Dash/main.py
    os.system('curl -O https://raw.githubusercontent.com/markkmetz/Truck/cpp_ino_seperation/Dash/main.py')

    
def upload_csv():
    try:
        with dropbox.Dropbox(APP_TOKEN) as dbx:
            dbx.users_get_current_account()

            csv_files = find_csv_filenames("",".csv")
            for name in csv_files:
                with open(name, 'rb') as f:
                    print(name)
                    dbx.files_upload(f.read(),"/Truck_Logs/"+name)
                dbx.files_get_metadata("/Truck_Logs/"+name)
                os.remove(name)
    except:
        print("dropbox upload failed")


upload_csv()