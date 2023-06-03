import numpy as np
import matplotlib.pyplot as plt

lstKMP = []
lstBOOST = []
with open("./src/output.txt") as f:
    for line in f:
        lstKMP.append(int(int(line) / 1000))
with open("./src/outputb.txt") as f:
    for line in f:
        lstBOOST.append(int(int(line) / 1000))

countKMP = [i + 1 for i in range(10)]
countBOOST = [i + 1 for i in range(10)]
print(countKMP)

fig, ax = plt.subplots()

ax.plot(countKMP, lstKMP, label="KMP")
ax.plot(countBOOST, lstBOOST, label="KMP")
ax.grid()
ax.legend()
#  Добавляем подписи к осям:
ax.set_xlabel('Количество элементов')
ax.set_ylabel('Время (мс)')

plt.show()
