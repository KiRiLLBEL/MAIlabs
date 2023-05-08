from random import randint
from itertools import starmap
from multiprocessing import Pool


KEY_RANGE = (0, 18_446_744_073_709_551_615) # Диапазон значений ключа
VALUE_LEN_RANGE = (1, 256) # Диапазон длины значения
TEST_FOLDER_INSERT = './test/insert' # путь к папке с тестами
TEST_FOLDER_DELETE = './test/delete' # путь к папке с тестами
TEST_FOLDER_SEARCH = './test/search' # путь к папке с тестами

INCREASE_COEF = 100000 # коэфециент, с которым будут расти элементы в тестах
TESTS_AMOUNT = 100 # кол-во тестов


def generate_key():
    return randint(*KEY_RANGE)


def generate_char():
    return chr(randint(ord('a'), ord('z')))


def generate_value():
    return ''.join(map(lambda x: generate_char(), range(randint(*VALUE_LEN_RANGE))))


def generate_file(i):
    values = [(generate_value(), generate_key()) for _ in range(INCREASE_COEF * i)]

    with open(f'{TEST_FOLDER_INSERT}/test{i}.txt', 'w', encoding='utf8') as file:
            file.write('\n'.join(starmap('+ {} {}'.format, values)))
    with open(f'{TEST_FOLDER_DELETE}/test{i}.txt', 'w', encoding='utf8') as file:
            file.write('\n'.join(starmap('- {} {}'.format, values)))
    with open(f'{TEST_FOLDER_SEARCH}/test{i}.txt', 'w', encoding='utf8') as file:
            file.write('\n'.join(starmap('{}'.format, values)))


def main():
    with Pool(10) as pool:
        pool.map(generate_file, tuple(range(1, TESTS_AMOUNT + 1)))
        

if __name__ == '__main__':
    main()