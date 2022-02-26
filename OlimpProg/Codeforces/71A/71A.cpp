#include <iostream>
#include <string>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string S;
		cin >> S;
		if (S.size() > 10)
			cout << S[0] << S.size() - 2 << S[S.size() - 1] << "\n";
		else
			cout << S << "\n";
	}
}