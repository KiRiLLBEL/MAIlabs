import os
import random

os.makedirs('tests', exist_ok=True)

operations = ['+', '-', '/', '*', '<', '>', '=']

for i in range(1, 101):
    with open(f'tests/test_{i}.txt', 'w') as f:
        for _ in range(100*i):
            num1 = random.randint(10**(i-1), 10**(i*10)-1)
            num2 = random.randint(10**(i-1), 10**(i*10)-1)

            op = random.choice(operations)

            f.write(f'{num1}\n{num2}\n{op}\n')
