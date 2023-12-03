import random

def generate_graph_test(n_vertices, n_edges, file_name):
    # Генерация списка ребер
    edges = [(random.randint(1, n_vertices), random.randint(1, n_vertices), random.randint(1, 100)) for _ in range(n_edges)]

    # Выбор случайных начальной и конечной вершин
    start_vertex = random.randint(1, n_vertices)
    end_vertex = random.randint(1, n_vertices)
    while end_vertex == start_vertex:
        end_vertex = random.randint(1, n_vertices)

    # Запись информации о графе в файл
    with open(file_name, 'w') as f:
        f.write(f"{n_vertices} {n_edges} {start_vertex} {end_vertex}\n")
        for edge in edges:
            f.write(" ".join(map(str, edge)) + "\n")

# Пример использования функции
n_vertices = 1000
n_edges = 1000
for i in range(1, 101):
    generate_graph_test(n_vertices, n_edges, f"test{i}.txt")
    n_vertices = min(int(n_vertices * 1.1), 10**5)  # Увеличиваем количество вершин на 10%, но не более 10^5
    n_edges = min(int(n_edges * 1.1), n_vertices * (n_vertices - 1) // 2)  # Увеличиваем количество ребер на 10%, но не более максимально возможного количества ребер
