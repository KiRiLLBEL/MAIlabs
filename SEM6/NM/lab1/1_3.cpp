#include <iostream>
#include "Matrix.h"
using namespace std;
using namespace numeric;

int main() {
    Matrix<double> matrix = inputMatrix<double>("input6Matrix.txt");
    vector<double> b = inputVector<double>("input6Vector.txt");
    cout << "\nMatrix:\n";
    printMatrix(matrix);
    cout << "\nVector b:\n";
    printVector(b);
    cout << "\nSolution of system by iterations\n";
    printVector(iterationSolve<double>(matrix, b, 0.001));
    cout << "\nSolution of system by Seidel\n";
    printVector(SeidelSolve<double>(matrix, b, 0.001));


    return 0;
}
