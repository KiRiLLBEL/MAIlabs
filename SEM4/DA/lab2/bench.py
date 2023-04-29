import numpy as np
import matplotlib.pyplot as plt

BTREE_PATH = "./test/result/btree/"
MAP_PATH = "./test/result/map/"

timeBTREE = []
timeMAP = []
countBTREE = []
countMAP = []

with open(BTREE_PATH + "search.txt") as f:
    for line in f:
        timeBTREE.append(int(int(line) / 1000))
with open(MAP_PATH + "search.txt") as f:
    for line in f:
        timeMAP.append(int(int(line) / 1000))

for i in range(100):
    countBTREE.append((i + 1) * 200)
    countMAP.append((i + 1) * 200)

fig, ax = plt.subplots()

print(timeBTREE)
print(timeMAP)

ax.plot(countBTREE, timeBTREE, label="b-tree")
ax.plot(countMAP, timeMAP, label='std::map')
ax.grid()
ax.legend()
#  Добавляем подписи к осям:
ax.set_xlabel('Количество элементов')
ax.set_ylabel('Время (мс)')

plt.show()
