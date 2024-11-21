import re
from pprint import *
import numpy as np
from data import *

def norm(a: list):
    for i in range(value_alternatives):
        tmp = 0
        for j in range(value_experts):
            tmp += kof[j] * a[i][j]
        a[i] += [tmp]
    return a

def previosly(a: list):
    norma = []
    for i in range(value_alternatives):
        norma += [round(a[i][-1], 0)]
    return norma

def print_(a, b):
    print(f'{"":60}{"  ".join(b)}')
    for i in range(value_alternatives):
        # print(list_alternatives[i], '\t\t','\t'.join(list(map(str, a[i]))))
        print(f"""{list_alternatives[i]:70}{'                '.join(list(map(str, a[i])))}""")
        
    print('\n\n')


# кол-во экспертов
value_experts = input('Введите кол-во экспертов: ')
while not re.fullmatch('[0-9]+', value_experts):
    print('\nВведенное вами значение не верно!\nЗначение должно содержать цифры!!!')
    value_experts = input('\nВведите кол-во: ')
value_experts = int(value_experts)

# кол-во альтернатив
value_alternatives = input('Введите кол-во альтернатив: ')
while not re.fullmatch('[0-9]+', value_alternatives):
    print('\nВведенное вами значение не верно!\nЗначение должно содержать цифры!!!')
    value_alternatives = input('\nВведите кол-во: ')
value_alternatives = int(value_alternatives)

print('\n')
# заполняем экспертов
list_experts = []
for i in range(value_experts):
    # expert = input(f'Введите эксперта {i + 1}: ')
    list_experts += [input(f'Введите эксперта №{i + 1}: ')]
    
print('\n')
# заполняем альтернативы
list_alternatives = []
for i in range(value_alternatives):
    # alternative = input(f'Введите эксперта {i + 1}: ')
    list_alternatives += [input(f'Введите альтернативу №{i + 1}: ')]

# определяем шкалу
print('\nВведите интервал шкалы')
left = input('Левая граница: ')
right = input('Правая граница: ')
while left > right:
    print('\nЛевая граница не может быть больше правой! Введите границе интервала снова!!!')
    left = input('Левая граница: ')
    right = input('Правая граница: ')
    

# dict_alternative = {}
# for i in range(value_alternatives):
#     tmp = []
#     print('\n')
#     for j in range(value_experts):
#         tmp += [input(f'Альтернатива {list_alternatives[i]} Эксперт {list_experts[j]} оценка: ')]
#     dict_alternative[list_alternatives[i]] = tmp
    
# pprint(dict_alternative)

# Компетентность специалистов
kof = list(map(float, 
               input(
                   'Введите коэффициенты компитентности экспертов\nP.S. Значение одного эксперта принимает значение от 0 до 1\nне включительно и сумма должа быть равна 1\n\nКоэффициенты: '
                    ).split()
               )
           )
while sum(kof) > 1:
    print('Введенные вами коэффициенты дают в сумме больше 1! Введите корректные значения!!!')
    kof = list(map(float, input('Коэффициенты: ').split()))
   
# Оценивание на каждом этапе  
evaluation1 = []
print('\n\nОценивание при плохих условиях\n\n')
for i in range(value_alternatives):
    print(f'Альтернатива: {list_alternatives[i]:70}Эксперты: {"   ".join(list_experts)}')
    evaluation1 += [list(map(float, input(f'Оценка:{"":92}').split()))]
print('\n')

evaluation2 = []
print('\n\nОценивание при обычных условиях\n\n')
for i in range(value_alternatives):
    print(f'Альтернатива: {list_alternatives[i]:70}Эксперты: {"   ".join(list_experts)}')
    evaluation2 += [list(map(float, input(f'Оценка:{"":92}').split()))]
print('\n')

evaluation3 = []
print('\n\nОценивание при наилучших условиях\n\n')
for i in range(value_alternatives):
    print(f'Альтернатива: {list_alternatives[i]:70}Эксперты: {"   ".join(list_experts)}')
    evaluation3 += [list(map(float, input(f'Оценка:{"":92}').split()))]
print('\n')

evaluation1 = norm(evaluation1)
evaluation2 = norm(evaluation2)
evaluation3 = norm(evaluation3)

print(f'{"":92}Обобщенная оценка')
for i in range(value_alternatives):
    print(f'{list_alternatives[i]:95}{evaluation1[i][-1]}')
print('\n\n')
print(f'{"":92}Обобщенная оценка')
for i in range(value_alternatives):
    print(f'{list_alternatives[i]:95}{evaluation2[i][-1]}')
print('\n\n')    
print(f'{"":92}Обобщенная оценка')
for i in range(value_alternatives):
    print(f'{list_alternatives[i]:95}{evaluation3[i][-1]}')
print('\n\n') 

previosly_calculate = []
money = input('Введите бюджет, который вы планирутете выделить: ')
while not re.fullmatch('[0-9]+', money):
    print('\nВведенное вами значение не верно!\nЗначение должно содержать цифры!!!')
    money = input('\nВведите бюджет снова: ')
money = int(money)

previosly_calculate = np.transpose([
    previosly(evaluation1),
    previosly(evaluation2),
    previosly(evaluation3)
])


for i in range(len(previosly_calculate)):
    for j in range(len(previosly_calculate[i])):
        previosly_calculate[i][j] = money - previosly_calculate[i][j]



print_(previosly_calculate, FEEL)

minim = []
for i in range(len(previosly_calculate)):
    print(f'{list_alternatives[i]:70}{min(previosly_calculate[i])}')
    minim += [min(previosly_calculate[i])]

print(f'\n\nСамая лучшая альтернатива: {list_alternatives[minim.index(max(minim))]}')


