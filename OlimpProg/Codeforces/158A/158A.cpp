#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, k, t, s = 0;
	cin >> n >> k;
	vector <int> c(n);
	for (auto& v : c)
		cin >> v;
	t = c[k - 1];
	for (auto v : c)
		if (v >= t && v > 0)
			s++;
	cout << s << "\n";
			
} 