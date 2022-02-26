#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	transform(s.begin(), s.end(), s.begin(), tolower);
	for (auto& x : s) 
		if (x != 'a' && x != 'o' && x != 'y' && x != 'e' && x != 'u' && x != 'i')
			cout << '.' << x;
		
}