import matplotlib.pyplot as plt
import re

def plot_times():
    with open('time.txt', 'r') as f:
        lines = f.readlines()

    test_nums = []
    preprocess_times = []
    search_times = []

    for line in lines:
        match = re.match(r'Test (\d+): Preprocess time=(\d+\.\d+), Search time=(\d+)', line.strip())
        if match:
            test_num, preprocess_time, search_time = match.groups()
            test_nums.append(int(test_num))
            preprocess_times.append(float(preprocess_time) / 1000)  # переводим в секунды
            search_times.append(float(search_time) / 1000)  # переводим в секунды

    plt.figure(figsize=(12, 6))

    plt.subplot(1, 2, 1)
    plt.plot(test_nums, preprocess_times, marker='o')
    plt.title('Зависимость времени предварительной обработки от номера теста')
    plt.xlabel('Номер теста')
    plt.ylabel('Время предварительной обработки (с)')

    plt.subplot(1, 2, 2)
    plt.plot(test_nums, search_times, marker='o')
    plt.title('Зависимость времени поиска от номера теста')
    plt.xlabel('Номер теста')
    plt.ylabel('Время поиска (с)')

    plt.tight_layout()
    plt.show()

plot_times()
