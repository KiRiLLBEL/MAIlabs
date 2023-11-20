#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(3);
    int N;
    cin >> N;

    vector<double> a(N);
    for(double& i: a)
        cin >> i;

    sort(a.rbegin(), a.rend());

    double ans = 0;
    int x, y, z;
    if(N >= 3) {
        for(int i = 0; i < N - 2; ++i) {
            if(
                a[i] < a[i + 1] + a[i + 2] &&
                a[i + 1] < a[i] + a[i + 2] &&
                a[i + 2] < a[i] + a[i + 1]
            ) {
                double p = (a[i] + a[i+1] + a[i+2]) / 2;
                double current_square = sqrt(p * (p - a[i]) * (p - a[i + 1]) * (p - a[i + 2]));
                if(current_square > ans) {
                    x = a[i + 2];
                    y = a[i + 1];
                    z = a[i];
                    ans = current_square;
                }
            }
        }
    }
    if(ans != 0) {
        cout << fixed << ans << "\n";
        cout << x << " " << y << " " << z;
    } else {
        cout << ans << "\n";
    }
    return 0;
}