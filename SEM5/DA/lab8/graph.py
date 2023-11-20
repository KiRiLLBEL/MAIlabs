import numpy as np
import matplotlib.pyplot as plt

lstKMP = []
lstBOOST = []
with open("./output_main.txt") as f:
    for line in f:
        lstKMP.append(int(int(line) / 1000))
with open("./output_test.txt") as f:
    for line in f:
        lstBOOST.append(int(int(line) / 1000))

countKMP = [2**i for i in range(1, 11)]
countBOOST = [2**i for i in range(1, 11)]

fig, ax = plt.subplots()

ax.plot(countKMP, lstKMP, label="Жадный алгоритм")
ax.plot(countBOOST, lstBOOST, label="Наивный")
ax.grid()
ax.legend()
#  Добавляем подписи к осям:
ax.set_xlabel('Количество элементов')
ax.set_ylabel('Время (мкс)')

plt.show()