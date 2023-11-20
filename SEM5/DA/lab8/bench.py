# импортируем модуль для работы с файлами
import os

# создаем функцию для генерации случайных чисел
def generate_numbers(n):
  # импортируем модуль для работы со случайными числами
  import random
  # создаем пустой список для хранения чисел
  numbers = []
  # в цикле генерируем n случайных положительных целых чисел от 1 до 1000
  for i in range(n):
    numbers.append(random.randint(1, 1000))
  # возвращаем список чисел
  return numbers

# создаем функцию для записи тестов в файлы
def write_tests():
  # в цикле создаем 5 тестов
  for i in range(1, 6):
    # генерируем 5^i чисел
    numbers = generate_numbers(5**i)
    # создаем имя файла в формате test{i}.txt
    filename = f"test{i}.txt"
    # открываем файл для записи
    with open(filename, "w") as f:
      # в цикле записываем каждое число в файл с новой строки
      for number in numbers:
        f.write(str(number) + "\n")
    # закрываем файл
    f.close()

# создаем функцию для запуска программ main и test на тестах
def run_programs():
  # импортируем модуль для запуска команд в терминале
  import subprocess
  # в цикле запускаем программы на каждом тесте
  for i in range(1, 6):
    # создаем имя файла с тестом в формате test{i}.txt
    test_file = f"test{i}.txt"
    # создаем имя файла с результатом работы программы main в формате output_main.txt
    output_main_file = "output_main.txt"
    # создаем имя файла с результатом работы программы test в формате output_test.txt
    output_test_file = "output_test.txt"
    # запускаем программу main на тесте и записываем результат в файл output_main.txt с дополнением к существующему содержимому
    subprocess.run(f"./main < {test_file} >> {output_main_file}", shell=True)
    # запускаем программу test на тесте и записываем результат в файл output_test.txt с дополнением к существующему содержимому
    subprocess.run(f"./test < {test_file} >> {output_test_file}", shell=True)

# вызываем функцию для записи тестов в файлы
write_tests()
# вызываем функцию для запуска программ на тестах
run_programs()
