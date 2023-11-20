# Импортируем модуль для работы с файлами
import os
import random
# Создаем папку для хранения тестов
os.mkdir("tests")

# Для каждого номера теста от 1 до 500
for i in range(1, 501):
  # Создаем имя файла вида test_i.txt
  file_name = f"test_{i}.txt"
  # Открываем файл для записи
  file = open(os.path.join("tests", file_name), "w")
  # Записываем в первую строку размер матрицы i x i
  file.write(f"{i} {i}\n")
  # Для каждой строки матрицы
  for j in range(i):
    # Создаем строку из i случайных чисел 0 или 1 без пробелов
    row = "".join(str(random.randint(0, 1)) for k in range(i))
    # Записываем строку в файл с переносом строки
    file.write(row + "\n")
  # Закрываем файл
  file.close()