#include <iostream>
#include "Matrix.h"
using namespace std;
using namespace numeric;

int main() {
    Matrix<double> matrix = inputMatrix<double>("inputMatrix.txt");
    cout << "\nMatrix:\n";
    printMatrix(matrix);
    cout << "\nEigen values\n";
    auto res = findEigenvaluesAndEigenvectors(matrix, 0.001);
    printVector(res.eigenValues);
    cout << "\nEigen vectors\n";
    for(const auto& x: res.eigenVectors) {
        printVector(x);
        cout << "\n";
    }
    return 0;
}


