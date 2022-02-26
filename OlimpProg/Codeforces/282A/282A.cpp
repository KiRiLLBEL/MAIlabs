#include <iostream>
#include <string>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,s = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string X;
		cin >> X;
		if (X == "X++" || X == "++X")
			s++;
		else
			s--;
	}
	cout << s << "\n";
}