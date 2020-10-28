from math import sqrt
import numpy as np
import sys

#2
'''
gamma_0 = 5/3
p_0 = 1.694*10**(-4)
P_0 = 1.013*10**6
gamma_3 = 7/5
C_3 = 3.6537*10**4
P_3 = 1.6768*10**6
U_0 = 0
U_3 = 1.229*10**4 #3 roots
'''

#1
'''
gamma_0 = 5/3
p_0 = 1.694*10**(-4)
P_0 = 1.013*10**6
gamma_3 = 7/5
C_3 = 3.6537*10**4
P_3 = 1.6768*10**6
U_0 = 0
U_3 = 0 #3 roots
'''
#3
'''
gamma_0 = 5/3
p_0 = 10**(-5)
P_0 = 3.848*10**3
gamma_3 = 5/3
C_3 = 1.31478*10**4
P_3 = 1.17928*10**9
U_0 = 0
U_3 = 5*10**4 #1. fix
'''
#4
'''
gamma_0 = 7/5
p_0 = 1.694*10**(-4)
P_0 = 1.013*10**6
gamma_3 = 7/5
C_3 = 3.6537*10**4
P_3 = 1.6768*10**6
U_0 = 10^(-3) #3 roots
U_3 = 1.229*10**4
'''
#5
'''
gamma_0 = 7/5
p_0 = 10**(-5)
P_0 = 3.848*10**3
gamma_3 = 5/3
C_3 = 1.31478*10**4
P_3 = 1.17928*10**9
U_0 = 0
U_3 = 5*10**4 #1 roots fix 
'''
#6

gamma_0 = 5/3
p_0 = 1.694*10**(-4)
P_0 = 1.013*10**6
gamma_3 = 5/3
C_3 = 3.6537*10**4
P_3 = 1.6768*10**6
U_0 = -10**(-1)
U_3 = 0 #2 roots

#7
'''
gamma_0 = 5/3
p_0 = 10**(-5)
P_0 = 3.848*10**3
gamma_3 = 5/3
C_3 = 2.53248*10**4
P_3 = 3.04*10**9 #1 roots
U_0 = 0
U_3 = 0
'''
#8
'''
gamma_0 = 5/3
p_0 = 10**(-5)
P_0 = 3.848*10**3
gamma_3 = 7/5
C_3 = 2.53248*10**4
P_3 = 3.04*10**9 #1roots
U_0 = 0
U_3 = 0
'''
p_3 = gamma_3 * P_3 / C_3**2
#D_0 - ?

alpha_0 = (gamma_0 + 1)/(gamma_0 - 1)
n = 2*gamma_3/(gamma_3-1) #степень полинома, чекнуть приведение типов
mu = (U_3 - U_0)*sqrt(((gamma_0 - 1)*p_0)/(2*P_0))
nu = 2/(gamma_3 - 1)*sqrt((((gamma_0 - 1)*gamma_3)/2)*(P_3/P_0)*(p_0/p_3))
x = P_3/P_0
x = 0

n = round(n)
print('Степень полнома', n)
#выражение 32 стр 18
coefficient = [x**2] + [0] * (n - 3) + [-1 * alpha_0 * x * nu**2] \
+ [2 * alpha_0 * nu * (nu + mu) * x] + [(-2 - alpha_0 * (mu+nu)**2) * x] \
+ [0] * (n - 3) + [-1 * nu**2] + [2 * nu * (mu + nu)] + [1 - (mu + nu)**2]
#print(coefficient)
#7 -й и последний

#(12) cnh 9
#coefficient.reverse()
print('Mmmmmmmm')
print(np.roots(coefficient)) #Методом сопровождающей матрицы

'''
for first_not_zero_index, first_not_zero in enumerate(coefficient):
    if (first_not_zero != 0.0):
        break
print(first_not_zero_index, first_not_zero, coefficient[0])
sys.exit()
'''
print(coefficient)
i = 0
while coefficient[i] == 0.0:
    coefficient.pop(i)

print(coefficient)
#cтр 26
A = abs(max(coefficient[1:], key = abs)) 
B = abs(max(coefficient[:-1], key = abs))

circle_root = [-(1 + A/abs(coefficient[0])),-(abs(coefficient[-1])/(abs(coefficient[-1]+B)))] + [abs(coefficient[-1])/(abs(coefficient[-1]+B)), 1 + A/abs(coefficient[0])]
print(circle_root)
#------------[0]-----[1]---------0----------[2]-----[3]----------------

#Используем метод на стр 26-27
N = 0
count_subarea = 0
accuracy = 10**(-9)
lenght_step = 1000
# точность 10^-4
while (count_subarea not in [1, 2, 3]):
    count_subarea = 0
    N += 1000000
    lenght_roots = (circle_root[3] - circle_root[2]) * 2
    lenght_step = lenght_roots / N; #машинная точность
    value_on_interval = []
#----[0]---[1]------
# x = circle_root[0]
# prev_val_sgn = (np.polyval(coefficient, x) > 0.0) #polyval- возращает значение полинома в т. x
# prev_val = x
# while x <= circle_root[1]:
# x += lenght_step
# cur_val_sgn = (np.polyval(coefficient, x) > 0.0) 
# if (prev_val_sgn != cur_val_sgn):
# a = [prev_val, x]
# value_on_interval.append(a)
# count_subarea += 1
# prev_val_sgn = cur_val_sgn
# prev_val = x
# x = circle_root[2]
# prev_val_sgn = (np.polyval(coefficient, x) > 0.0)
# prev_val = x
    x = circle_root[2]

    prev_val_sgn = (np.polyval(coefficient, x) > 0.0) #polyval- возращает значение полинома в т. x
    prev_val = x
    while x <= circle_root[3]:
        x+=lenght_step
        cur_val_sgn = (np.polyval(coefficient, x) > 0.0) 
        if (prev_val_sgn != cur_val_sgn):
            a = [prev_val, x]
            value_on_interval.append(a)
            count_subarea += 1
        prev_val_sgn = cur_val_sgn
        prev_val = x
print('количество областей',count_subarea, 'lenght_step',lenght_step)
print(value_on_interval)

for string in value_on_interval:
    while (string[1] - string[0] > accuracy):
        x = (string[0] + string[1])/2
        if (bool(np.polyval(coefficient, x) > 0.0) == bool(np.polyval(coefficient, string[0]) > 0.0)):
            string[0] = x
        else:
            string[1] = x
    print('X', x)
    P_1 = P_3*x**(n)
    print('P_1', P_1)
    U_1 = U_3 + 2 * C_3 / (gamma_3 - 1) * (1 - (P_1 / P_3)**((gamma_3 - 1) / (2 * gamma_3)))
    print('U_1', U_1)
    p_1 = p_0 * ((gamma_0 - 1) + (gamma_0 + 1) * (P_1 / P_0)) / ((gamma_0 + 1) + (gamma_0 - 1) * (P_1/P_0))
    print('p_1', p_1)
    D_0 = (p_0 * U_0 - p_1 * U_1) / (p_0 - p_1)
    print('D_0', D_0)
