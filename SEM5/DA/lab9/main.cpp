#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

using Graph = vector<vector<int>>;
using ll = long long;
const ll INF = 1e18;


struct Node {
    int u, v;
    ll w;
};

ll ford_bellman(int start, int end, int n, const vector<Node>& g) {
    vector<ll> dp(n, INF);
    dp[start] = 0;
    for(int i = 0; i < n - 1; ++i) {
        bool change = false;
        for(size_t j = 0; j < g.size(); ++j) {
            if (dp[g[j].u] + g[j].w < dp[g[j].v]) {
                dp[g[j].v] = dp[g[j].u] + g[j].w;
                change = true;
            }
        }
        if(!change)
            break;
    }
    return dp[end];
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n, m, s, e;
    cin >> n >> m >> s >> e;
    vector<Node> g(m);
    for(int i = 0; i != m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u;
        --v;
        g[i] = {u, v, w};
    }

    auto start = high_resolution_clock::now();
    ll path = ford_bellman(--s, --e, n, g);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);

    cout << duration.count()  << endl;

    return 0;
}