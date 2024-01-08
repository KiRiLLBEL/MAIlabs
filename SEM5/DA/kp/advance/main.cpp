#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <queue>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

const double INF = 1e18;
const double EARTH_RADIUS = 6371e3;

struct Node {
    uint32_t id;
    double lat;
    double lon;
};

struct Edge {
    uint32_t from;
    uint32_t to;
};

struct Pointer {
    uint32_t id;
    uint32_t location;
};

bool operator< (const Node& lhs, const Node& rhs) {
    return lhs.id < rhs.id;
}

bool operator< (const Edge& lhs, const Edge& rhs) {
    if(lhs.from != rhs.from) {
        return lhs.from < rhs.from;
    } else {
        return lhs.to < rhs.to;
    }
}

struct fu {
    double f;
    uint32_t u;
};

bool operator < (const fu& lhs, const fu& rhs) {
    return lhs.f > rhs.f;
}

double to_radians(double angle) {
    return angle * M_PI / 180.0;
}

double h(const Node& p1, const Node& p2) {
    double phi = to_radians(p1.lon);
    double psi = to_radians(p2.lon);
    double delta = to_radians(p1.lat - p2.lat);
    double d = acos(sin(phi) * sin(psi) + cos(phi) * cos(psi) * cos(delta));
    return isnan(d) ? 0 : EARTH_RADIUS * d;
}

Node get_node(FILE* file, uint32_t index) {
    Node temp{};
    _fseeki64(file, index * sizeof(Node) + 3 * sizeof(uint32_t), SEEK_SET);
    fread(&temp, sizeof(Node), 1, file);
    return temp;
}

uint32_t get_index(uint32_t node, const vector<uint32_t>& nodes) {
    auto it = lower_bound(nodes.begin(), nodes.end(), node);
    if (it == nodes.end() || *it != node) {
        return -1;
    } else {
        return it - nodes.begin();
    }
}

vector<uint32_t> get_incident_node(FILE* file, uint32_t id, uint32_t node_count,  const vector<uint32_t>& nodes, const vector<int>& pointers) {
    uint32_t index = get_index(id, nodes);
    vector<uint32_t> ans;
    if(pointers[index] == -1) {
        return ans;
    }
    _fseeki64(file, node_count * sizeof(Node) + 3 * sizeof(uint32_t) + pointers[index] * sizeof(uint32_t), SEEK_SET);
    uint32_t cnt;
    fread(&cnt, sizeof(uint32_t), 1, file);
    for(uint32_t i = 0; i < cnt; ++i) {
        uint32_t node_id;
        fread(&node_id, sizeof(uint32_t), 1, file);
        ans.push_back(node_id);
    }
    return ans;
}

double AStar(FILE* file, uint32_t start, uint32_t goal, uint32_t node_count, const vector<uint32_t>& nodes, const vector<int>& pointers, vector<uint32_t>& p) {
    vector<bool> visited(node_count, false);
    vector<double> d(node_count, INF);
    uint32_t start_index = get_index(start, nodes);
    uint32_t goal_index =  get_index(goal, nodes);
    d[start_index] = 0;
    p[start_index] = start_index;
    priority_queue<fu> pq;
    Node start_node = get_node(file, start_index);
    Node goal_node = get_node(file, goal_index);
    pq.push({d[start_index] + h(start_node, goal_node), start});
    while(!pq.empty()) {
        fu cur = pq.top();
        uint32_t current_index = get_index(cur.u, nodes);
        if(cur.u == goal)
            return d[current_index];
        pq.pop();
        visited[current_index] = true;
        vector<uint32_t> incident = get_incident_node(file, cur.u, node_count, nodes, pointers);
        Node current = get_node(file, current_index);
        for(const auto& v: incident) {
            uint32_t v_index = get_index(v, nodes);
            if(visited[v_index])
                continue;
            Node v_node = get_node(file, v_index);
            double tmp = d[current_index] + h(current, v_node);
            if(tmp < d[v_index]) {
                d[v_index] = tmp;
                p[v_index] = current_index;
                pq.push({d[v_index] + h(v_node, goal_node), v});
            }
        }
    }
    return -1;
}

void read_nodes_for_preprocess(FILE* file, vector<Node>& nodes) {
    Node temp;
    while (fscanf(file, "%u %lf %lf", &temp.id, &temp.lat, &temp.lon) != EOF) {
        nodes.push_back(temp);
    }
    fclose(file);
    sort(nodes.begin(), nodes.end());
}

void read_edges_for_preprocess(FILE* file, vector<Edge>& edges) {
    uint32_t id_cnt = 0;
    while(fscanf(file, "%u", &id_cnt) != EOF) {
        uint32_t u;
        uint32_t v;
        fscanf(file, "%u", &u);
        for(uint32_t i = 1; i < id_cnt; ++i) {
            fscanf(file, "%u", &v);
            edges.emplace_back(u, v);
            edges.emplace_back(v, u);
            u = v;
        }
    }
    fclose(file);
    sort(edges.begin(), edges.end());
}

void write_graph(FILE* file, const vector<Node>& nodes, const vector<Edge>& edges) {
    uint32_t unique_node = 0;
    int64_t unique_id = -1;
    for(uint32_t i = 0; i < edges.size(); ++i) {
        if(edges[i].from != unique_id) {
            ++unique_node;
            unique_id = edges[i].from;
        }
    }
    uint32_t node_count = nodes.size();
    uint32_t edge_count = edges.size();

    fwrite(&node_count, sizeof(uint32_t), 1, file);
    fwrite(&edge_count, sizeof(uint32_t), 1, file);
    fwrite(&unique_node, sizeof(uint32_t), 1, file);
    for(const Node& node: nodes) {
        fwrite(&node, sizeof(Node), 1, file);
    }


    int64_t prev_id = -1;
    uint32_t written_cnt = 0;
    vector<Pointer> pointers;
    for(uint32_t i = 0; i < edges.size(); ++i) {
        if(prev_id != edges[i].from) {
            uint32_t cnt = 1;
            uint32_t j = i + 1;
            while(j < edge_count && edges[j].from == edges[i].from) {
                ++cnt;
                ++j;
            }
            fwrite(&cnt, sizeof(uint32_t), 1, file);
            prev_id = edges[i].from;
            pointers.emplace_back(prev_id, i + written_cnt);
            ++written_cnt;
        }
        fwrite(&edges[i].to, sizeof(uint32_t), 1, file);
    }
    for(const auto & pointer : pointers) {
        fwrite(&pointer, sizeof(Pointer), 1, file);
    }
    fclose(file);
}

void read_nodes_and_pointers(FILE* file, vector<uint32_t>& nodes, vector<int>& pointers, uint32_t node_count, uint32_t edge_count, uint32_t unique_count) {
    for(uint32_t i = 0; i < node_count; ++i) {
        Node temp{};
        fread(&temp, sizeof(Node), 1, file);
        nodes.push_back(temp.id);
    }
    _fseeki64(file, (unique_count + edge_count) * sizeof(uint32_t), SEEK_CUR);
    uint32_t node_pointer = 0;
    for(uint32_t i = 0; i < unique_count; ++i) {
        Pointer temp{};
        fread(&temp, sizeof(Pointer), 1, file);
        while(temp.id != nodes[node_pointer]) {
            pointers.push_back(-1);
            ++node_pointer;
        }
        pointers.push_back(temp.location);
        ++node_pointer;
    }

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: not enough args\n");
        return 1;
    }

    string command = argv[1];
    if (command == "preprocess") {
        if (argc < 7) {
            printf("Error: not enough args for preprocess\n");
            return 1;
        }
        string nodes_file = argv[3];
        string edges_file = argv[5];
        string output_file = argv[7];
        FILE* fin = fopen(nodes_file.c_str(), "r");
        FILE* fin_edge = fopen(edges_file.c_str(), "r");
        FILE* fout = fopen(output_file.c_str(), "wb");
        if (!fin) {
            printf("Error: Node file is not open\n");
            return 1;
        }
        if (!fin_edge) {
            printf("Error: Edge file is not open\n");
            return 1;
        }
        vector<Node> nodes;
        vector<Edge> edges;
        read_nodes_for_preprocess(fin, nodes);
        read_edges_for_preprocess(fin_edge, edges);
        write_graph(fout, nodes, edges);
    } else if (command == "search") {
        if (argc < 7 || argc > 9) {
            printf("Error: not enough args for search\n");
            return 1;
        }
        string graph_file = argv[3];
        string input_file = argv[5];
        string output_file = argv[7];
        bool full_output = false;
        if(argc > 8) {
            string output_check = argv[8];
            full_output = (output_check == "--full-output");
        }
        FILE* fin = fopen(graph_file.c_str(), "rb");
        FILE* fin_input = fopen(input_file.c_str(), "r");
        FILE* fout = fopen(output_file.c_str(), "w");
        if (!fin) {
            printf("Error: Graph file is not open\n");
            return 1;
        }
        if (!fin_input) {
            printf("Error: Input file is not open\n");
            return 1;
        }
        uint32_t node_count, edge_count, unique_count;
        fread(&node_count, sizeof(uint32_t), 1, fin);
        fread(&edge_count, sizeof(uint32_t), 1, fin);
        fread(&unique_count, sizeof(uint32_t), 1, fin);
        vector<uint32_t> nodes;
        vector<int> pointers;
        read_nodes_and_pointers(fin, nodes, pointers, node_count, edge_count, unique_count);

        uint32_t start, goal;
        auto start_time = high_resolution_clock::now();

        while (fscanf(fin_input, "%u %u", &start, &goal) != EOF) {
            vector<uint32_t> p(node_count);
            double ans = AStar(fin, start, goal, node_count, nodes, pointers, p);
            fprintf(fout, "%lf", ans);
            uint32_t index = get_index(goal, nodes);
            vector<uint32_t> path;
            if(full_output) {
                while(p[index] != index) {
                    path.push_back(get_node(fin, index).id);
                    index = p[index];
                }
                fprintf(fout, " %lu", path.size());
                for(int64_t i = path.size() - 1; i >= 0; --i) {
                    fprintf(fout, " %u", path[i]);
                }
            }
            fprintf(fout, "\n");
        }

        auto stop = high_resolution_clock::now();


        auto duration = duration_cast<milliseconds>(stop - start_time);

        printf("%lld", duration.count());
        fclose(fin);
        fclose(fin_input);
        fclose(fout);
    } else {
        printf("Error: unknown command\n");
        return 1;
    }

    return 0;
}