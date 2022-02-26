#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string S;
	vector <int> a;
	cin >> S;
	for (int i = 0; i < S.length(); ++i) {
		if (S[i] != '+') {
			a.push_back(int(S[i]));
		}
	}
	sort(a.begin(), a.end());
	S = "";
	for (int i = 0; i < a.size(); ++i) {
		S += "+";
		S += char(a[i]);
	}
	cout << S.substr(1, S.size() - 1);
	return 0;
}