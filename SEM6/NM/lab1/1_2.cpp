#include <iostream>
#include "Matrix.h"
using namespace std;
using namespace numeric;

int main() {
    Matrix<double> matrix = inputMatrix<double>("input3Matrix.txt");
    vector<double> b = inputVector<double>("input3Vector.txt");
    cout << "\nMatrix:\n";
    printMatrix(matrix);
    cout << "\nVector b:\n";
    printVector(b);
    cout << "\nSolution of system:\n";
    printVector(tridiagonalSolve(matrix, b));
    return 0;
}
