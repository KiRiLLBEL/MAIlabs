#include <iostream>
#include "Matrix.h"
using namespace std;
using namespace numeric;

int main() {
    Matrix<double> matrix = inputMatrix<double>("inputMatrix.txt");
    cout << "\nMatrix:\n";
    printMatrix(matrix);
    QRMatrix<double> QRDecomposition(matrix);
    cout << "\nEigen values:\n";
    auto res = findEigenvaluesAndEigenvectorsByQR(matrix, 0.001, 0.0001);
    for(auto c: res.eigenValues) {
        if(c.imag() == 0) {
            cout << c.real() << "\n";
        } else {
            cout << c.real() << " " << c.imag() << "i\n";
        }
    }
    return 0;
}
