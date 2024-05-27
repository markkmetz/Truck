import os
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor
from sklearn import tree
from sklearn.model_selection import train_test_split


path = "c:\\Users\\markl\\OneDrive\\Documents\\GitHub\\Truck\\Logs"
dfs = []

def find_csv_filenames(path_to_dir, suffix=".csv"):
    
    if len(path_to_dir) > 0:
        filenames = os.listdir(path_to_dir)
    else:
        filenames = os.listdir()

    return [filename for filename in filenames if filename.endswith(suffix)]


for filename in find_csv_filenames(path):
    file_path = path + "\\" + filename
    #print(filename)
    if os.path.getsize(file_path) != 0:
        df = pd.read_csv(file_path)
        dfs.append(df)

df = pd.concat(dfs, ignore_index=True)
df.drop(df.index[df['RPM'] == 0], inplace=True)
df.drop(df.index[df['RPM'] > 4000], inplace=True)

#df.drop(df.index[df['Gear'] == 4], inplace=True)
df.drop(df.index[df['MPH'] < 5], inplace=True)

df = df[df['RPM'].notna()]
df.drop(["controlslocked", "ShiftMode"], axis=1, inplace=True)
#print(df.tail())

train, test = train_test_split(df, test_size=0.2)



#model = sklearn.linear_model.LinearRegression()


train = train[["EPCPWM","RPM","MPH","Gear","Temp","EPCPSI"]]
print(len(train.index))
train = train.drop_duplicates(subset=["EPCPWM","RPM","MPH","Gear","Temp"])
print(len(train.index))
dfx = train[["EPCPWM","RPM","MPH","Gear","Temp"]]
dfy = train["EPCPSI"]

dfx.dropna(inplace=True)
dfx.drop_duplicates()
dfy.dropna(inplace=True)


model = RandomForestRegressor(n_estimators=1,max_depth=10)
model.fit(dfx, dfy)
print(model.score(dfx, dfy))

import emlearn
cmodel = emlearn.convert(model, method='loadable')
cmodel.save(file='epc.h', name='epc')


# with open("combined.csv", "w") as fout:
#     for fil in find_csv_filenames(path):
#         with open(path + "\\" + fil, "r") as f:
#             fout.writelines(f)

# fout.close()




