import random

def generate_test(n, m, test_number):
    with open(f'test{test_number}.txt', 'w') as file:
        file.write(f'{n} {m}\n')
        for _ in range(n):
            x = random.randint(-10**9, 10**9)
            y = random.randint(-10**9, 10**9)
            file.write(f'{x} {y}\n')
        for _ in range(m):
            u = random.randint(1, n)
            v = random.randint(1, n)
            file.write(f'{u} {v}\n')
        start_vertex = random.randint(1, n)
        end_vertex = random.randint(1, n)
        file.write(f'{start_vertex} {end_vertex}\n')

test_cases = [
    (100, 100),
    (100, 500),
    (100, 1000),
    (1000, 1000),
    (1000, 5000),
    (1000, 10000),
    (10000, 10000),
    (10000, 50000),
    (10000, 75000),
    (10000, 100000)
]

for i, (n, m) in enumerate(test_cases, start=1):
    generate_test(n, m, i)
