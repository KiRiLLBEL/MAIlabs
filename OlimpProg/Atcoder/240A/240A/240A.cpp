#include <iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	if (abs(a - b) == 1) {
		cout << "Yes" << "\n";
	}
	else if (abs(a - b) == 9) {
		cout << "Yes" << "\n";
	}
	else {
		cout << "No" << "\n";
	}
	return 0;
}