#include <iostream>
#include "Matrix.h"
using namespace std;
using namespace numeric;

int main() {
    Matrix<double> matrix = inputMatrix<double>("input1Matrix.txt");
    vector<double> b = inputVector<double>("input1Vector.txt");
    Matrix<double> LinearSystem(matrix.rows(), matrix.rows() + 1);
    Matrix<double> InverseSystem(matrix.rows(), matrix.rows() + matrix.rows());
    for(size_t i = 0; i < matrix.rows(); ++i) {
        for(size_t j = 0; j < matrix.cols(); ++j) {
            LinearSystem[i][j] = matrix[i][j];
            InverseSystem[i][j] = matrix[i][j];
        }
    }
    for(size_t i = 0; i < b.size(); ++i) {
        LinearSystem[i][LinearSystem.rows()] = b[i];
    }
    for(size_t i = 0; i < matrix.cols(); ++i) {
        InverseSystem[i][i + matrix.rows()] = 1;
    }
    LUMatrix<double> LinearSystemLU(LinearSystem);
    LUMatrix<double> LU(matrix);
    LUMatrix<double> InverseSystemLU(InverseSystem);
    cout << "\nSolving system:\n";
    printMatrix(LinearSystemLU.solve());
    cout << "\nDeterminant:\n";
    cout << LinearSystemLU.determinant();
    cout << "\nInverseMatrix:\n";
    printMatrix(InverseSystemLU.solve());
    cout << "\nU:\n";
    printMatrix(LU.U);
    cout << "\nL:\n";
    printMatrix(LU.L);
    cout << "\nMatrix:\n";
    printMatrix( LU.L * LU.U);
    return 0;
}
