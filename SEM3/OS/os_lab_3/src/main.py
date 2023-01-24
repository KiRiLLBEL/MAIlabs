import random

f = open('input.txt', 'w')
for i in range(0, 10000000):
    a = random.randint(0, 10000000)
    f.write(str(a) + ' ')
f.close()