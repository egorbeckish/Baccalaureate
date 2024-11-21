# This Python 3 environment comes with many helpful analytics libraries installed
# It is defined by the kaggle/python Docker image: https://github.com/kaggle/docker-python
# For example, here's several helpful packages to load

import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)

# Input data files are available in the read-only "../input/" directory
# For example, running this (by clicking run or pressing Shift+Enter) will list all files under the input directory

import os
for dirname, _, filenames in os.walk('/kaggle/input'):
    for filename in filenames:
        print(os.path.join(dirname, filename))

# You can write up to 20GB to the current directory (/kaggle/working/) that gets preserved as output when you create a version using "Save & Run All" 
# You can also write temporary files to /kaggle/temp/, but they won't be saved outside of the current session


GlobalLandTemperaturesByCity = pd.read_csv("/kaggle/input/climate-change-earth-surface-\
temperature-data/GlobalLandTemperaturesByCity.csv")

GlobalLandTemperaturesByCountry = pd.read_csv("/kaggle/input/climate-change-earth-surface-\
temperature-data/GlobalLandTemperaturesByCountry.csv")

GlobalLandTemperaturesByMajorCity = pd.read_csv("/kaggle/input/climate-change-earth-surface-\
temperature-data/GlobalLandTemperaturesByMajorCity.csv")

GlobalLandTemperaturesByState = pd.read_csv("/kaggle/input/climate-change-earth-surface-\
temperature-data/GlobalLandTemperaturesByState.csv")

GlobalTemperatures = pd.read_csv("/kaggle/input/climate-change-earth-surface-\
temperature-data/GlobalTemperatures.csv")


df = GlobalLandTemperaturesByCity # получаем данные по России with_russia = df[ (df['Country'] == 'Russia')] 
# преобразуем строку в тип данных дата-время 
df['dt'] = df['dt'].astype('datetime64[ns]') # группируем по стране и по году в дате, Country и dt становятся column
df_by_dt = df.groupby([df['Country'],df['dt'].dt.year]).mean() # восстанавливаем индексы 
df_by_dt = df_by_dt.reset_index() 
df = df_by_dt


# запишем более коротко условие по выбору стран 
df_by_country = df[df['Country'].isin(['Russia', 'Italy', 'Kazakhstan'])] # преобразуем таблицу так, 
                                                                            #чтобы столбцы опять стали индексами 
df_by_country = df_by_country.set_index(['Country','dt']) 
dfun = df_by_country.unstack('Country') # выбираем только те столбцы где есть столбец AverageTemperature 
newcols = [item for item in dfun if item[0]=='AverageTemperature'] # строим новую таблицу из столбцов 
dpop = dfun[newcols] # выводим наш график 
dpop.plot() # выбираем только те столбцы, где есть столбец AverageTemperatureUncertainty 
newcols = [item for item in dfun if item[0]=='AverageTemperatureUncertainty'] # строим новую таблицу из столбцов
dpop = dfun[newcols] # выводим наш график 
dpop.plot()



df = GlobalLandTemperaturesByCity 
df['dt'] = df['dt'].astype('datetime64[ns]')
df_by_dt = df.groupby([df['City']== 'Tomsk', df['dt'].dt.year]).mean()
df_by_dt = df_by_dt.reset_index()
df_by_dt[df_by_dt['City'] == True].plot(x = 'dt', y = 'AverageTemperature') 
df_by_dt[df_by_dt['City'] == False].plot(x = 'dt', y = 'AverageTemperature') 
dfTomsk = df[df['City'] == 'Tomsk']


import seaborn 
# Нарисует среднее среди всех c максимальными и минимальными отклонениями 
seaborn.lineplot(x = 'dt', y = 'AverageTemperature', data = df_by_country)

df_by_country = df_by_country.reset_index() 

import matplotlib.pyplot as plt # создаем два подграфика расположенные по вертикали. 
# axv - осевая система для отображения одного графика 
# здесь две осевых системы, axv[0] и axv[1] для # двух подграфиков 

fig, axv = plt.subplots(nrows = 2,ncols = 1,figsize=(6, 7)) 
countries = pd.unique(df_by_country['Country']).tolist() 

for country in countries:

    # выбираем страну для отображения графиков на одной системе axv[0] 
    df_by_country[df_by_country['Country'] == country].plot(x = 'dt', y = 'AverageTemperature', 
                                                          ax = axv[0], label = country)
    
    # выбираем страну для отображения графиков на другой системе axv[1] 
    df_by_country[df_by_country['Country'] == country].plot(x = 'dt', y = 'AverageTemperatureUncertainty', 
                                                          ax = axv[1], label = country) 
fig.show()


df = GlobalLandTemperaturesByCity 
df['dt'] = df['dt'].astype('datetime64[ns]') 
df = df[df['City']=='Tomsk'] 
df_by_dt = df.groupby([df['dt'].dt.year]).mean() 
df_Tomsk = df_by_dt.reset_index() 

import seaborn 
seaborn.pairplot(df_Tomsk)



import numpy as np # linear algebra 
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv) 
df = pd.read_csv("/kaggle/input/suicide-rates-overview-1985-to-2016/master.csv") 

# получить данные с повторениями по группированному полю в стиле SQL 
dfcy = df.groupby(['country','year'], as_index = False).sum() 

# выбираем страны из сгруппированной таблицы 
dfj = dfcy[dfcy['country'].isin(['Japan','Kazakhstan', 'Russian Federation'])] 

# устанавливаем в качестве индекса (первичного ключа) страну и год 
# чтобы можно было преобразовать таблицу со столбцами по Казахстану, Японии и России отдельно 
dfj = dfj.set_index(['country','year']) 

# преобразуем таблицу так, чтобы были отдельные столбцы по странам 
dfun = dfj.unstack('country') 

# получаем список имен столбцов таблицы 
newdf = list(dfun) 

# выбираем только те столбцы где есть столбец население 
newcols = [item for item in newdf if item[0]=='population'] 

# строим новую таблицу из столбцов с населением Казахстана, Японии и России 
dpop = dfun[newcols] 

# выводим наш график 
#%matplotlib inline 
import matplotlib.pyplot as plt 
# как будут расположены графики на панно, в ячейках 2*2 # размер графиков

fig, axv = plt.subplots(nrows = 2, ncols = 2, figsize = (10, 10)) 

# пространство между графиками 
plt.subplots_adjust(hspace = 0.5) 
plt.subplots_adjust(wspace = 0.5) 

# способ определения соотношения сторон 
axv[0][0].set_aspect(aspect = 'auto') 
axv[1][0].set_aspect(aspect = 'equal') 
axv[1][1].set_aspect(aspect = 'equal') 

# график по населению 
dpop.plot(ax = axv[0][0]) 

import seaborn as sns 
print(list(df)) 
corr = df.corr() 
corr1 = dfcy.corr() 
# цветовая карта корреляций 
sns.heatmap(corr,ax = axv[1][0]) 
sns.heatmap(corr1,ax = axv[1][1])

# пары соотношений данных по полу 
sns.pairplot(data = df,hue = 'sex')
# пары соотношений данных по возрастам 
sns.pairplot(data = df, hue = 'age')


#%matplotlib inline 
import matplotlib.pyplot as plt 

# как будут расположены графики на панно, в ячейках 2*2 # размер графиков 
fig, axv = plt.subplots(nrows = 3, ncols = 1,figsize = (20, 20)) 

# пространство между графиками 
plt.subplots_adjust(hspace = 0.7) 
plt.subplots_adjust(wspace = 0.5) 
# способ определения соотношения сторон


axv[0].set_aspect(aspect = 'auto') 
axv[1].set_aspect(aspect = 'auto') 
axv[2].set_aspect(aspect = 'auto') 

# график по населению 
dpop.plot(ax = axv[0]) 
import seaborn as sns 
print(list(df)) 

# определяем несколько DataFrame c усреднением по годам в десять лет 
dfcl = [] 
dfcl.append(dfcy[(dfcy['year'] >= 1980) & (dfcy['year'] < 1990)]) 
dfcl.append(dfcy[(dfcy['year'] >= 1990) & (dfcy['year'] < 2000)]) 
dfcl.append(dfcy[(dfcy['year'] >= 2000) & (dfcy['year'] < 2010)]) 
dfcl.append(dfcy[(dfcy['year'] >= 2010) & (dfcy['year'] < 2020)]) 
dfall = [] 


# цикл, в котором создаем группированные по странам выборки 
for i in range(4): 

    dfcymean = dfcl[i].groupby('country', as_index = False).mean() 

    # делим количество случаев на население 
    dfcymean['suon1'] = \
    dfcymean['suicides_no'].divide(dfcymean['population'], fill_value = 0.0) 

    # умножаем на 100000, чтобы получить количество # случаев на 100 тыс. 
    dfcymean['suon1'] = dfcymean['suon1'] * 1e+5 

    # добавляем в список фреймов 
    dfall.append(dfcymean) 

# объединяем фреймы между собой 
res = pd.concat(dfall,keys=['if1', 'if2', 'if3', 'if4']) 
# поворачиваем таблицу, чтобы условия были в столбцах
    
resv = res.unstack(level=0) 
# сортируем по последнему десятку лет и по количеству 
# cлучаев за год 
resv = resv.sort_values(by=[('suon1','if4')], ascending=False) 
# создаем скаттер графики на которых будут 
# отображены случаи по убыванию по странам 
ax1 = sns.scatterplot(x = ('country','if4'), y = ('suon1','if4'), 
        data=resv, ax = axv[1],label="2010-2020") 

sns.scatterplot(x = ('country','if3'), y = ('suon1','if3'), 
        data=resv, ax = axv[1],label="2000-2010") 

sns.scatterplot(x = ('country','if2'), y = ('suon1','if2'), 
        data=resv, ax = axv[1],label="1990-2000") 

sns.scatterplot(x = ('country','if1'), y = ('suon1','if1'), 
        data=resv, ax = axv[1],label="1980-1990") 

# вращаем подписи к графику 
for item in ax1.get_xticklabels(): 
    item.set_rotation(90) 
    # попробуем сделать примерно то же самое парой строчек кода 
    # сортируем по количеству случаев DataFrame 
    # c количеством случаев на 100 тыс населения 
    res = res.sort_values(by = 'suon1', ascending=False) 
    # строим график с отклонениями от среднего 
    ax2 = sns.lineplot(x='country',y='suon1', data = res, sort = False, ax = axv[2]) 

for item in ax2.get_xticklabels(): 
    item.set_rotation(90)

    
    

    
    
import http.client as cl
import ssl
import json
import pandas
conn = cl.HTTPSConnection('data.gov.ru', timeout=100,
                          context=ssl._create_unverified_context())
conn.request("GET", "https://data.gov.ru/api/json/dataset/?access_token=af5c23e400ef656d0c291c0cbe7238a4&search=2019")
resp = conn.getresponse()
print(resp.status, resp.reason)
print(resp.getheaders())
data = resp.read().decode()
dt = pandas.read_json(data, typ='frame')
print(dt)
# Выводим первые 1024 байта скачанного датасета.
print(data[0:1024])



path_file = '/content/drive/MyDrive/python/dataset.hdf5'
dt.to_hdf(path_file, key='datasets_2019', mode='w', format='table')
fname = '/content/drive/MyDrive/python/dataset.hdf5'
dt = pandas.read_hdf(fname, key = 'datasets_2019')
print(dt) 
dt_filt = dt[dt['title'].str.contains(r'студент')]
print(dt_filt['title'])
print(dt_filt[['title','identifier']]) 
conn = cl.HTTPSConnection('data.gov.ru', timeout = 100, context=ssl._create_unverified_context())
conn.request("GET", \
"https://data.gov.ru/api/json/dataset/?access_token=af5c23e400ef656d0c291c0cbe7238a43&search=2019")
resp = conn.getresponse()
data = resp.read().decode()
print(data[0:1024])



import http.client as cl
import ssl
import json
import pandas
import xml.etree.ElementTree as et
import xml.dom.minidom

def Dt():
    return pandas.read_hdf('/content/drive/MyDrive/python/dataset.hdf5', key='datasets_2019')

def GetRequest(name, i):
    return "https://data.gov.ru/api/json/dataset/" + Dt()['identifier'].iloc[i] + name


def StrXml(js_data, i, ident_v, conn):
    if js_data:
        print(js_data)
        request = "https://data.gov.ru/api/xml/dataset/"
        request = request + Dt()['identifier'].iloc[i] + "/version/"
        request = request + ident_v + "/content?access_token=af5c23e400ef656d0c291c0cbe7238a4"
        conn.request("GET", request)
        data_content = conn.getresponse().read().decode()
        print(data_content[0:1024])

        ParsXml(data_content)

def ParsXml(data_content):
    try:
        parser = et.XMLParser(encoding="utf-8")
        xroot = et.fromstring(data_content, parser=parser)
        print(xroot.tag)
        Out(xroot)
    except BaseException:
        print("programm error")

def Out(xroot):
    for rows in xroot.findall('rows'):
        print("rows")
        for row in rows.findall('row'):
            print("row")
            for value in row.findall('value'):
                print(value.text)

def main():
    conn = cl.HTTPSConnection('data.gov.ru', timeout=100, context=ssl._create_unverified_context())
    for i in range(20, 100):
        print("identifier", Dt()['identifier'].iloc[i])
        print("title", Dt()['title'].iloc[i])
        conn.request("GET", GetRequest("/version/?access_token=af5c23e400ef656d0c291c0cbe7238a4", i))
        try:
            js_data = json.load(conn.getresponse())
            print("version ", js_data[0]['created'])
            ident_v = js_data[0]['created']
            request = GetRequest("/version/", i) + ident_v + "/structure?access_token=af5c23e400ef656d0c291c0cbe7238a4"
            conn.request("GET", request)
            js_data = json.load(conn.getresponse())
        except BaseException:
            print("programm error")
        StrXml(js_data, i, ident_v, conn)
    conn.close()

main()    
