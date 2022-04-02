#include <iostream>
#include <math.h>
#include "vector"
using namespace std;
int main() {
    vector <double> v = {15, 15, 15, 15, 15};
    double sum = 0;
    for (int i = 0; i != 5; ++i) {
        sum += exp(v[i] - 15);
    }
    for (int i = 0; i != 5; ++i) {
        cout << exp(v[i] - 15) / sum <<"\n";
    }
//    1.523e-08
//    3.62514e-34
//    1.29958e-24
//    1
//    3.3057e-37
    return 0;
}
