#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

double square(int a, int b, int c) {
    vector<int> sides = {a, b, c};
    double p = 0;
    for (int side : sides) {
        p += side;
    }
    p /= 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

bool is_triangle(int a, int b, int c) {
    vector<int> sides = {a, b, c};
    sort(sides.begin(), sides.end());
    return sides[0] + sides[1] > sides[2];
}

pair<double, vector<int>> solution(vector<int> sides) {
    double max_square = -1;
    vector<int> max_triangle;

    for (int i = 0; i < sides.size(); i++) {
        for (int j = i + 1; j < sides.size(); j++) {
            for (int k = j + 1; k < sides.size(); k++) {
                int a = sides[i], b = sides[j], c = sides[k];
                if (is_triangle(a, b, c)) {
                    double s = square(a, b, c);

                    if (s > max_square) {
                        max_square = s;
                        max_triangle = {a, b, c};
                    }
                }
            }
        }
    }

    if (max_square > 0) {
        return {max_square, max_triangle};
    }

    return {};
}

int main() {
    int n;
    cin >> n;
    vector<int> sides(n);
    for (int i = 0; i < n; i++) {
        cin >> sides[i];
    }

    auto start = high_resolution_clock::now();
    auto result = solution(sides);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << duration.count() << endl;

    return 0;
}
