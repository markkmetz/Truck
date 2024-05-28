import os
from platform import node
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor,ExtraTreesRegressor
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



#data drops--------
#df.drop(df.index[df['Gear'] != 1], inplace=True)

df.drop(df.index[df['EPCPSI'] == 0], inplace=True)
df.drop(df.index[df['MPH'] < 5], inplace=True)
df.drop(df.index[df['Temp'] < 175], inplace=True)


df.drop(df.index[df['EPCPWM']  > 79], inplace=True)
df.drop(df.index[df['EPCPWM']  < 50], inplace=True)


df = df[df['RPM'].notna()]
df.drop(["controlslocked", "ShiftMode"], axis=1, inplace=True)
#df = df.drop_duplicates(subset=["EPCPWM","RPM","MPH","Gear","Temp","TPS","MAP","TCC"])
df = df[["TPS","EPCPWM","RPM","MPH","Gear","Temp","EPCPSI","MAP","TCC"]]
df.dropna(inplace=True)



df = df.astype(int)
#df.hist()


train, test = train_test_split(df, test_size=0.2)

test = test.drop_duplicates(subset=["EPCPWM","RPM","MPH","Gear","Temp","TPS","MAP","TCC"])

print(train.head())
print(train.tail())

train_dfx = train[["EPCPSI","RPM","MPH","Gear","Temp"]]
train_dfy = train["EPCPWM"]
test_dfx = test[["EPCPSI","RPM","MPH","Gear","Temp"]]
test_dfy = test["EPCPWM"]


print("Regressor--------------------------------------------------------------")
model = tree.DecisionTreeRegressor(random_state=0,max_depth=20,max_leaf_nodes=1000)
model.fit(train_dfx, train_dfy)
print(model.score(test_dfx, test_dfy))

y_pred_test_Forestreg = model.predict(test_dfx)

import matplotlib.pyplot as plt

# Assuming you have already made predictions and stored them in `y_pred_test_Forestreg`
plt.scatter(test_dfy, y_pred_test_Forestreg)
plt.xlabel('True Values')
plt.ylabel('Predictions')
plt.axis('equal')
plt.axis('square')
plt.xlim(40,80)
plt.ylim(40,80)
_ = plt.plot([-100, 100], [-100, 100], 'b-')  # A diagonal line for reference

#plt.show()

# import emlearn
# cmodel = emlearn.convert(model, method='inline')
# cmodel.save(file='epc.h', name='epc')

import m2cgen as m2c
code = m2c.export_to_c(model)
# f = open("epc.cpp", "a")
# print(model.feature_names_in_)
# f.write(code)
# f.close()

# print("Linear--------------------------------------------------------------")
# model = LinearRegression()
# model.fit(train_dfx, train_dfy)
# print(model.score(test_dfx, test_dfy))
# y_pred_test_LIN = model.predict(test_dfx)
# plt.scatter(test_dfy, y_pred_test_LIN)
# plt.xlabel('True Values')
# plt.ylabel('Predictions')
# plt.axis('equal')
# plt.axis('square')
# plt.xlim(40,100)
# plt.ylim(40,100)
# _ = plt.plot([-100, 100], [-100, 100], 'b-')  # A diagonal line for reference

# plt.show()




