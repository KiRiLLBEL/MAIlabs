#include <iostream>
#include "math.h"
using namespace std;

void solve() {
    int n, B, x, y;
    cin >> n >> B >> x >> y;
    long long sum = 0;
    int prev = 0;
    for (int i = 0; i != n; ++i) {
        if (prev + x <= B) {
            prev += x;
            sum += prev;
        }
        else {
            prev -= y;
            sum += prev;
        }
    }
    cout << sum << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n = 0;
    cin >> n;
    for (int i = 0; i != n; ++i) {
        solve();
    }
    return 0;
}
