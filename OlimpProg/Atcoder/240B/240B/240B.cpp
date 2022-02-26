#include <iostream>
#include <vector>
#include <stack>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	stack <int> q;
	int a;
	cin >> a;
	q.push(a);
	cout << q.size() << "\n";
	for (int i = 1; i < n; i++) {
		int x;
		cin >> x;
		if (x != q.top()) {
			q.push(x);
		}
		else {
			q.pop();
		}
		cout << q.size() << "\n";
	}
}