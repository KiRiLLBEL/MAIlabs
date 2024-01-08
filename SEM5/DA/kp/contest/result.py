import numpy as np
import matplotlib.pyplot as plt

lstKMP = []
lstBOOST = []
with open("./output_main.txt") as f:
    for line in f:
        lstKMP.append(int(line))
with open("./output_test.txt") as f:
    for line in f:
        lstBOOST.append(int(line))

countKMP = [i for i in range(1, 11)]
countBOOST = [i for i in range(1, 11)]

fig, ax = plt.subplots()

ax.plot(countKMP, lstKMP, label="A-star")
ax.plot(countBOOST, lstBOOST, label="Дейкстра")
ax.grid()
ax.legend()
#  Добавляем подписи к осям:
ax.set_xlabel('Номер теста')
ax.set_ylabel('Время (мкс)')

plt.show()