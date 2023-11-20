#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector <vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < m; ++j)
            a[i][j] = str[j] - '0';
    }
    vector<int> dp(m, -1), dp_left(m), dp_right(m);
    int square = 0;
    auto start = high_resolution_clock::now();
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j)
            if(a[i][j] == 1)
                dp[j] = i;
        stack<int> st1, st2;
        for(int j = 0; j < m; ++j) {
            while(!st1.empty() && dp[st1.top()] <= dp[j])
                st1.pop();
            while(!st2.empty() && dp[st2.top()] <= dp[m - j - 1])
                st2.pop();
            dp_left[j] = (st1.empty()) ? -1 : st1.top();
            dp_right[m - j - 1] = (st2.empty()) ? m : st2.top();
            st1.push(j);
            st2.push(m - j - 1);
        }
        for(int j = 0; j < m; ++j) {
            square = max(square, (i - dp[j]) * (dp_right[j] - dp_left[j] - 1));
        }
    }
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << duration.count() << endl;
    return 0;
}