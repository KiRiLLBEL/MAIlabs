import subprocess
from time import time
from os import listdir
from os import path


EXECUTABLE_PATH = './build/src/main'
TESTS_DIR = './tests'


def check_time(test_path: str, executable: str) -> int:
    start_time = time()

    subprocess.run(f'cat {test_path} | {executable}', shell=True, capture_output=True)
    
    end_time = time()

    return end_time - start_time


def get_elements_amount(test_path: str) -> int:
    elements_amount = 0
    
    with open(test_path, 'r', encoding='utf8') as file:
        for _ in file:
            elements_amount += 1
    
    return elements_amount


def main():
    for test_path in listdir(TESTS_DIR):
        full_path = path.join(TESTS_DIR, test_path)
        work_time = check_time(full_path, EXECUTABLE_PATH)
        elements_amount = get_elements_amount(full_path)

        print(f'{elements_amount}\t{work_time}')


if __name__ == '__main__':
    main()