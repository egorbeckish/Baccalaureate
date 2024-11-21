import re
import os
import time
from data import *

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

print('\n\n')    
print('\t','\t'.join(list_experts))
print('\n'.join(list_alternatives))
print('\n\n')

time.sleep(1)
os.system('cls')
print(
    'Выберети тип шкалы:\n\
    1. В процентах\n\
    2. Целочисленный тип\n\
    3. Дробный тип\n\n'
    )

choice = input('Введите номер шкалы, которую вы выбрали: ')
while int(choice) <= 0 or int(choice) > 3:
    choice = input()
    
match choice:
    case '1':
        print('%')
    case '2':
        print('\nВведите интервал шкалы')
        left = input('Левая граница: ')
        right = input('Правая граница: ')
        while left > right:
            print('\nЛевая граница не может быть больше правой! Введите границе интервала снова!!!')
            left = input('Левая граница: ')
            right = input('Правая граница: ')
    case '3':
        print('\nВведите интервал шкалы')
        left = input('Левая граница: ')
        right = input('Правая граница: ')
        while left > right:
            print('\nЛевая граница не может быть больше правой! Введите границе интервала снова!!!')
            left = input('Левая граница: ')
            right = input('Правая граница: ')