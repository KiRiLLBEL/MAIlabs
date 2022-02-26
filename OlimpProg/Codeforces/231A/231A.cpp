#include <iostream>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, a, b, c, s = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c;
		if (a + b + c > 1)
			s++;
	}
	cout << s << "\n";
}