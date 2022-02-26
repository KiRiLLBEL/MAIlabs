#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	string S1, S2;
	cin >> S1 >> S2;
	transform(S1.begin(), S1.end(), S1.begin(), tolower);
	transform(S2.begin(), S2.end(), S2.begin(), tolower);
	if (S1 > S2) {
		cout << 1 << "\n";
	}
	else if (S1 == S2) {
		cout << 0 << "\n";
	}
	else {
		cout << -1 << "\n";
	}
	return 0;
}