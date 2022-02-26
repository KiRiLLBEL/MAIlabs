#include <iostream>
#include <vector>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int a, b;
	vector <vector <int>> arr(5, vector <int>(5));
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) {
				a = i+1;
				b = j+1;
			}
		}
	cout << abs(3 - a) + abs(3 - b) << "\n";
}