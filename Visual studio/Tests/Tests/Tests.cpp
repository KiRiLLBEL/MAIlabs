#include <iostream>
using namespace std;

void solve() {
	int A, B;
	cin >> A >> B;
	cout << A + B << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		solve();
	}
}