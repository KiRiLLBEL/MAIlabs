#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cmath>
using namespace std;
using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;
struct Point {
    ll x, y;
};

struct fu {
    double f;
    int u;
};

bool operator < (const fu& lhs, const fu& rhs) {
     return lhs.f > rhs.f;
}

const double INF = 1e18;

double h(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double AStar(int start, int goal, const Graph& g, const vector<Point>& vertices) {
    vector<bool> visited(g.size(), false);
    vector<double> d(g.size(), INF);
    d[start] = 0;
    priority_queue<fu> pq;
    pq.push({d[start] + h(vertices[start], vertices[goal]), start});
    while(!pq.empty()) {
        fu cur = pq.top();
        if(cur.u == goal)
            return d[cur.u];
        pq.pop();
        visited[cur.u] = true;
        for(int v: g[cur.u]) {
            if(visited[v])
                continue;
            double tmp = d[cur.u] + h(vertices[cur.u], vertices[v]);
            if(tmp < d[v]) {
                d[v] = tmp;
                pq.push({d[v] + h(vertices[v], vertices[goal]), v});
            }
        }
    }
    return -1;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout.precision(7);
    int n, m;
    cin >> n >> m;
    vector<Point> vertices;
    for(int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        vertices.push_back({x, y});
    }
    Graph g(n);
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        cout << fixed << AStar(x, y, g, vertices) << "\n";
    }
    return 0;
}