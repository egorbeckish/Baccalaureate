!pip install pandas

from turtle import *
import numpy as np
import matplotlib.pyplot as plt
from math import *
from time import *

a = 0
b = 1
n = 10000

def integral_rectangle(a, b, n):    # Метод прямоугольников

                                    # На вход принимаем диапозон
                                    # который мы зададим и кол-во точек
    
    x = np.linspace(a, b, n)    # Функция, которая принимает наш
                                # диапозон и делит его на кол-во точек
    
    y = np.log1p(x)   # задаем ln(x + 1)

    plt.subplot(111)  # Рисуем один график
    plt.grid()  # Рисуем сетку
    plt.plot(x, y, color = 'red', linewidth = 2)    # Создаем график с 
                                                    # доп. параметрами
    # plt.show()  # Выводим диаграмму
    xx = x[1:] - x[:-1]
    
    return abs(y[:-1] * xx).sum()


def integral_trapezoid_generator(a, b, n):    # Метод прямоугольников

                                    # На вход принимаем диапозон
                                    # который мы зададим и кол-во точек

    x = np.linspace(a, b, n)    # Функция, которая принимает наш
                                # диапозон и делит его на кол-во точек

    y = np.log1p(x) # задаем ln(x + 1)

    plt.subplot(111)  # Рисуем один график
    plt.grid()  # Рисуем сетку
    plt.plot(x, y, color = 'red', linewidth = 2)    # Создаем график с 
                                                    # доп. параметрами
    # plt.show()  # Выводим диаграмму

    # [sum((y[i + 1] + y[i]) * .5 * (x[i + 1] - x[i])) for i in range(len(y) - 1)]
    return sum([((y[i + 1] + y[i]) * .5 * (x[i + 1] - x[i])) for i in range(len(y) - 1)])


def integral_trapezoid_cutoff(a, b, n):    # Метод прямоугольников

                                    # На вход принимаем диапозон
                                    # который мы зададим и кол-во точек

    x = np.linspace(a, b, n)    # Функция, которая принимает наш
                                # диапозон и делит его на кол-во точек

    y = np.log1p(x) # задаем ln(x + 1)

    plt.subplot(111)  # Рисуем один график
    plt.grid()  # Рисуем сетку
    plt.plot(x, y, color = 'red', linewidth = 2)    # Создаем график с 
                                                    # доп. параметрами
    # plt.show()  # Выводим диаграмму

    return ((y[1:] + y[0:-1]) * .5 * (x[1:] - x[0:-1])).sum()



t = time()
s1 = integral_rectangle(a, b, n)
print(f"Integral with the help rectangle method {s1}")
print(f"time = {time() - t}\n")


t = time()
s2 = integral_trapezoid_generator(a, b, n)
print(f"Integral with the help trapezoid method {s2}")
print(f"time = {time() - t}\n")


t = time()
s3 = integral_trapezoid_cutoff(a, b, n)
print(f"Integral with the help trapezoid method {s3}")
print(f"time = {time() - t}\n")



from google.colab import drive
drive.mount('/mntDrive')

from sys import path
from os import listdir
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt


path.append('/mntDrive/My Drive/python')

def read_image(maxim_files, dir_name):
  files = listdir(dir_name)   # return list names files road dir_name

  if (maxim_files > len(files)):  # checking for the number of images
    counter_files = len(files)
  else:
    counter_files = maxim_files

  image = [[]] * counter_files # create list for files
  for i in range(counter_files):  # save image in list
    image[i] = Image.open(dir_name + '/' + files[i])  # open image to full road and save in list
  return  counter_files, image  # return counter image and picture



counter_files, image = read_image(10, '/mntDrive/My Drive/laba1/image')
picture_first = plt.figure(figsize = (10, 7)) # size image

# create coordinate OX and OY
plot_counter_x, plot_counter_y = int(counter_files**0.5)+counter_files%2, int(counter_files**0.5)+1
view_first = [[]] * counter_files # list image

for i in range(counter_files):
  view_first[i] = picture_first.add_subplot(plot_counter_x, plot_counter_y, i + 1) # draw coordinate
  view_first[i].imshow(np.array(image[i]))  # append image in list
picture_first.show() #show image



import random

transparency_coefficient = random.random()  # transparency coefficient of one to another
# random.random() return number type of float in range [0, 1]

picture_second = plt.figure(figsize = (10, 15)) # size image
view_second = [[]] * counter_files  #list image

for i in range(counter_files - 1):  # let's go through to the penultimate picture
  view_second[i] = picture_second.add_subplot(plot_counter_x, plot_counter_y, i + 1)  # draw coordinate
  height = min(image[i].size[0], image[i + 1].size[0]) # height gluing image
  width = min(image[i].size[1], image[i + 1].size[1]) # width gluing image

  # save two image equal size
  image_gluing = np.array([np.array(image[i + j].resize(size = (height, width)))/255.0 for j in range(2)])

  # gluing second image to first image multiplication transparency coefficient
  view_second[i].imshow(image_gluing[1] * (1 - transparency_coefficient) + image_gluing[0] * transparency_coefficient)

picture_second.show()


picture_third = plt.figure(figsize = (10, 15))
view_third = [[[]] * 2] * counter_files

for i in range(counter_files):
  # add color components of a three-dimensional tensor's
  # sum - r, g, b division 3
  
  image_first = (np.array(image[i]) / 255.0).sum(axis = 2) / 3.0 # thermal image
  image_second = np.expand_dims(image_first, axis = 2) # increasing the array 2 -> 3
  image_third = np.repeat(image_second, repeats = 3, axis = 2) # repeat 3 times

  view_third[i] = [picture_third.add_subplot(counter_files, 2, i * 2 + j) for j in range(1, 3)]
  view_third[i][0].imshow(image_first)
  view_third[i][1].imshow(image_third)

picture_third.show()



picture_fourth = plt.figure(figsize=(10, 15))
view_fourth = [[]] * 4
for i in range(counter_files):
    height = image[i].size[1]
    width = image[i].size[0]

    image_temp = [[]] * 4
    image_temp[0] = np.array(image[i])
    
    image_temp[1] = image_temp[0].copy()  # create copy
    image_temp[2] = image_temp[0][:, :(width // 2)] # create left half array image

    image_temp[2][:, :(width // 6), 1:3] = 1.0   # change image_temp[0]
    image_temp[3] = np.array(image[i])[:, (width // 2):] # create right half array image

    # create four graphics
    view_fourth = [picture_fourth.add_subplot(counter_files, 4, i * 4 + j) for j in range(1, 5)]
    [view_fourth[i].imshow(image_temp[i]) for i in range(4)] # view graphics

picture_fourth.show()



picture_fifth = plt.figure(figsize = (10, 15))
columns = 9
image_fifth = np.array([[np.array(image[i]) / 255.0 for j in range(columns)] for i in range(counter_files)])
view_fifth = [[[]] * columns for i in range(counter_files)]



def gradient(image, height, width):
  r, g, b = 1.0, 0.0, 1.0

  for j in range(width // 2, width):
    image[:height // 2, j:j + 1, :] += (r, g, b)
    r1, g1, b1 = j / (1868 ** 2), j / (1392 ** 2), j / (1112 ** 2)
  
  return image

def fill_clear_place(picture):
  picture[y1:y2, x1:x2] = np.array(image[i].resize(size = (x2 - x1, y2 - y1))) / 255.0
  picture[:y1] = picture[y1:y1 + 1][:, np.newaxis, np.newaxis]
  picture[y2:] = picture[y2 - 1:y2][:, np.newaxis, np.newaxis]
  picture[y1:y2, :x1] = picture[y1:y2, x1:x1 + 1].repeat(repeats = x1, axis = 1)
  picture[y1:y2,x2:] = picture[y1:y2, x2 - 1:x2].repeat(repeats = x1, axis = 1)

  return picture




for i in range(counter_files):
  height = image[i].size[1]  
  width = image[i].size[0]

  y1,y2,x1,x2 = height // 4, height - height // 4 - height % 4, width // 4, width - width // 4

  # make a noise the lower part
  image_fifth[i][0][height // 2:] = np.random.rand(height // 2 + height % 2)[:, np.newaxis, np.newaxis]

  # transpose image on 90 degrees
  image_fifth[i][1] = image_fifth[i][1].transpose(1,0,2)
  
  view_fifth[i] = [picture_fifth.add_subplot(counter_files, 2, i * 2 + j) for j in range(1, 3)]
  [view_fifth[i][j].imshow(image_fifth[i][j]) for j in range(2)]

picture_fifth.show()



import scipy.ndimage.filters as filt

picture_sixth = plt.figure(figsize = (10, 15))
image_sixth = np.array([[ np.array(image[i]) / 255.0 for j in range(5)]  for i in range(counter_files)])
view_sixth = [[[]]*5 for i in range(counter_files)]
graf = plt.figure(figsize = (7, 10))
x = np.arange(counter_files)
axis = graf.subplots()
y = np.empty(counter_files)

for i in range(4):
  width, height = image[i].size
  
  # making noise image
  image_sixth[i][1] += (np.random.rand(*image_sixth[i][0].shape)- .5) * .3

  # normalize noisy images in the range from 0 to 1
  image_sixth[i][2] = (image_sixth[i][1] - image_sixth[i][1].min()) / (image_sixth[i][1].max() - image_sixth[i][1].min())

  # transpose, bringing the dimension of color maps to the first place
  image_sixth_trans = image_sixth[i][2].transpose(2,0,1)

  # we filter each map with a Gaussian filter
  image_sixth_gaus = np.array([filt.gaussian_filter(image_sixth_trans[j],1) for j in range(3)])

  # return original format 
  image_sixth[i][3] = image_sixth_gaus.transpose(1, 2, 0)

  np.save('/mntDrive/My Drive/laba1/image',image_sixth[i][3]) 

  image_sixth[i][4] = image_sixth_trans.transpose(1, 2, 0)
    
  s = np.abs(image_sixth[i][3] - image_sixth[i][4]) 
  y[i]  = s.mean()
    
  print("разница в шумах : ", s.sum() / (s.shape[0] * s.shape[1]  *s.shape[2])) 
  print("разница в шумах : ", s.mean()) 
  print("разница в шумах : ", s.sum() / np.array(s.shape).prod())
  
  # creat graphs
  view_sixth[i] = [picture_sixth.add_subplot(counter_files, 5, i*5+j) for j in range(1,6)]

  # displaying graphs
  [view_sixth[i][j].imshow(image_sixth[i][j]) for j in range(5)]

axis.plot(x,y)
graf.show()  
picture_sixth.show()



import scipy.ndimage.interpolation as interp

picture_seventh = plt.figure(figsize = (10, 15))
image_seventh = np.array([[np.array(image[i]) / 255.0 for j in range(4)]  for i in range(counter_files)])
view_seventh = [[[]]*4 for i in range(counter_files)]


for i in range(1):

    # change scale image
    image_seventh[i][1] = interp.zoom(image_seventh[i][0], (2, 2, 1))

    # turn image on 10 degrees, turn axis 0,1
    image_seventh[i][2] = interp.rotate(input = image_seventh[i][0], angle = 10, axes = (0, 1), reshape = False)

    # with change original size array
    image_seventh[i][3] = interp.rotate(input = image_seventh[i][0], angle = 10, axes = (0, 1), reshape = True)
    
    view_seventh[i] = [picture_seventh.add_subplot(counter_files, 4, i * 4 + j) for j in range(1, 5)]
    [view_seventh[i][j].imshow(image_seventh[i][j]) for j in range(4)]

picture_seventh.show()




import scipy.ndimage.interpolation as interp

picture_eighth = plt.figure(figsize = (10, 15))
image_eighth = np.array([[ np.array(image[i]) / 255.0 for j in range(2)]  for i in range(counter_files)])
view_eighth = [[]] * counter_files

def water_mark(image):

    # the mask is the color that blue
    mask = np.bitwise_not(image[:,:,1] > 0.8) 

    # water turn image on 10 degrees, turn axis 0,1
    image_water = interp.rotate(input=image, angle = 10, axes = (0, 1), reshape = False)

    # intersection mask on original image and on water 
    image[:, :, 2] += (1 - mask) * image[:, :, 2] + mask * image_water[:, :, 2]
    return image

plot_countx, plot_county = int(counter_files ** .5) + counter_files % 2, int(counter_files ** .5) + 1
for i in range(1):
    image_eighth[i][0] = water_mark(image_eighth[i][0])
    view_eighth[i] = picture_eighth.add_subplot(plot_countx,plot_county, i+1) 
    view_eighth[i].imshow(image_eighth[i][0])
picture_eighth.show()
