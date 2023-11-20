import numpy as np
import matplotlib.pyplot as plt

lstKMP = []
lstBOOST = []
with open("./output_main.txt") as f:
    for line in f:
        lstKMP.append(int(int(line)))
with open("./output_test.txt") as f:
    for line in f:
        lstBOOST.append(int(int(line)))

countKMP = [100*i for i in range(1, 101)]
countBOOST = [100*i for i in range(1, 101)]

fig, ax = plt.subplots()

ax.plot(countKMP, lstKMP, label="Implementation")
ax.plot(countBOOST, lstBOOST, label="GMP")
ax.grid()
ax.legend()
#  Добавляем подписи к осям:
ax.set_xlabel('Количество операций')
ax.set_ylabel('Время (мс)')

plt.show()