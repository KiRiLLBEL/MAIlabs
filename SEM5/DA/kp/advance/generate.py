import random


def generate_test_files(num_tests, max_nodes, max_edges):
    with open('test_parameters.txt', 'w') as param_file:
        for i in range(1, num_tests + 1):
            num_nodes = min(i * (max_nodes // num_tests), max_nodes)
            num_edges = min(i * (max_edges // num_tests), num_nodes * (num_nodes - 1) // 2)
            num_queries = 10

            param_file.write(f'Test {i}: Nodes={num_nodes}, Edges={num_edges}, Queries={num_queries}\n')

            with open(f'test{i}.nodes', 'w') as f:
                for node_id in range(num_nodes):
                    lat = random.uniform(0, 90)
                    lon = random.uniform(0, 180)
                    f.write(f'{node_id} {lat} {lon}\n')

            with open(f'test{i}.edges', 'w') as f:
                edges = set()
                while len(edges) < num_edges:
                    id1 = random.randint(0, num_nodes - 1)
                    id2 = random.randint(0, num_nodes - 1)
                    if id1 != id2 and (id1, id2) not in edges and (id2, id1) not in edges:
                        edges.add((id1, id2))
                for edge in edges:
                    f.write(f'2 {edge[0]} {edge[1]}\n')

            with open(f'test{i}.input', 'w') as f:
                for _ in range(num_queries):
                    id_start = random.randint(0, num_nodes - 1)
                    id_goal = random.randint(0, num_nodes - 1)
                    while id_goal == id_start:
                        id_goal = random.randint(0, num_nodes - 1)
                    f.write(f'{id_start} {id_goal}\n')


generate_test_files(num_tests=10, max_nodes=10 ** 7, max_edges=10 ** 7)
