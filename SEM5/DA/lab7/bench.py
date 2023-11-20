def run_programs():
  # импортируем модуль для запуска команд в терминале
  import subprocess
  # в цикле запускаем программы на каждом тесте
  for i in range(1, 501):
    # создаем имя файла с тестом в формате test{i}.txt
    test_file = f"tests/test_{i}.txt"
    # создаем имя файла с результатом работы программы main в формате output_main.txt
    output_main_file = "output_main.txt"
    # создаем имя файла с результатом работы программы test в формате output_test.txt
    output_test_file = "output_test.txt"
    # запускаем программу main на тесте и записываем результат в файл output_main.txt с дополнением к существующему содержимому
    subprocess.run(f"./main < {test_file} >> {output_main_file}", shell=True)
    # запускаем программу test на тесте и записываем результат в файл output_test.txt с дополнением к существующему содержимому
    subprocess.run(f"./test < {test_file} >> {output_test_file}", shell=True)

run_programs()