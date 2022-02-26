#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int min = 0;
	int max = 0;
	int64_t MAX = 0;
	int64_t MIN = 1e19;
	int imax = 0;
	int imin = 0;
	vector <pair <int64_t, int64_t> > a(n);
	for (auto& v : a) {
		cin >> v.first;
		v.second = 0;
	}
	for (int i = 0; i < a.size(); ++i) {
		if (i != 0 && i != a.size() - 1) {
			if (a[i].first < a[i + 1].first && a[i].first < a[i - 1].first) {
				a[i].second = 1;
				min++;
			}
			else if (a[i].first > a[i + 1].first && a[i].first > a[i - 1].first) {
				a[i].second = 2;
				max++;
			}
		}
		else if (i == 0) {
			if (a[i].first < a[i + 1].first) {
				a[i].second = 1;
				min++;
			}
			else if (a[i].first > a[i + 1].first) {
				a[i].second = 2;
				max++;
			}
		}
		else if (i == a.size() - 1) {
			if (a[i].first < a[i - 1].first) {
				a[i].second = 1;
				min++;
			}
			else if (a[i].first > a[i - 1].first) {
				a[i].second = 2;
				max++;
			}
		}
	}
	cout << min;
	for (int i = 0; i < a.size(); ++i) {
		if (a[i].second == 1) {
			cout << " " << i + 1;
		}
	}
	cout << "\n";
	cout << max;
	for (int i = 0; i < a.size(); ++i) {
		if (a[i].first < MIN) {
			MIN = a[i].first;
			imin = i;
		}
		if (a[i].first > MAX) {
			MAX = a[i].first;
			imax = i;
		}
		if (a[i].second == 2) {
			cout << " " << i + 1;
			
		}
	}
	cout << "\n" << imin + 1 << " " << imax + 1<< "\n";
} 