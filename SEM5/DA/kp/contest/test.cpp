#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;
using ll = long long;

const ll INF = 1e18;

ll calculate_weight(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void dijkstra(int s, int t, vector<vector<pair<int, ll>>>& adj, vector<ll>& d) {
    d[s] = 0;
    priority_queue<pair<int, ll>, vector<pair<int, ll>>, greater<pair<int, ll>>> q;
    q.push({0, s});
    while (!q.empty()) {
        ll v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            ll len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.emplace(d[to], to);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> points(n);
    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        ll w = calculate_weight(points[u].first, points[u].second, points[v].first, points[v].second);
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<ll> d(n, INF);

    int s, t;
    cin >> s >> t;
    auto start = high_resolution_clock::now();
    dijkstra(s, t, adj, d);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << duration.count() << endl;

    return 0;
}
