import subprocess
import time

def run_tests(num_tests):
    with open('time.txt', 'w') as time_file:
        for i in range(1, num_tests + 1):
            print(f'Running test {i}...')

            # Запуск программы предварительной обработки
            print(f'Test {i}: Preprocessing...')
            start_time = time.time()
            subprocess.run(['./advance.exe', 'preprocess', '--nodes', f'./test{i}.nodes', '--edges', f'./test{i}.edges', '--output', f'./test{i}.graph'])
            end_time = time.time()
            preprocess_time = (end_time - start_time) * 1000  # время в миллисекундах
            print(f'Test {i}: Preprocessing completed.')

            # Запуск программы поиска с таймаутом в 15 минут
            print(f'Test {i}: Searching...')
            try:
                search = subprocess.run(['./advance.exe', 'search', '--graph', f'./test{i}.graph', '--input', f'./test{i}.input', '--output', f'./test{i}.output'], timeout=900, capture_output=True, text=True)
                search_time = search.stdout.strip()
                print(f'Test {i}: Search completed.')
            except subprocess.TimeoutExpired:
                search_time = 'Search timed out after 15 minutes'
                print(f'Test {i}: {search_time}')

            # Запись времени выполнения в файл
            time_file.write(f'Test {i}: Preprocess time={preprocess_time} ms, Search time={search_time}\n')

run_tests(num_tests=10)
