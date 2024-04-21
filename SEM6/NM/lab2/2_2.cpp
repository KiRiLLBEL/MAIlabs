#include "Solving_methods.h"
#include "../lab1/Matrix.h"
#include <iostream>
#include <valarray>
using namespace std;



int main() {

    vector<function<double(const std::vector<double>&)>> F(2);
    F[0] = [](const std::vector<double>& x) {
        return (x[0] * x[0] + 16) * x[1] - 64;
    };
    F[1] = [](const std::vector<double>& x) {
        return pow(x[0] - 2, 2) + pow(x[1] - 2, 2) - 16;
    };

    vector<function<double(const std::vector<double>&)>> PHI(2);
    PHI[0] = [](const std::vector<double>& x) {
        return 2 - sqrt(16 - pow(x[1] - 2, 2));
    };
    PHI[1] = [](const std::vector<double>& x) {
        return 64 / (x[0] * x[0] + 16);
    };

    Matrix<std::function<double(const std::vector<double>&)>> J(2, 2);
    J[0][0] = [](const std::vector<double>& x) {
        return 2 * x[0] * x[1];
    };

    J[0][1] = [](const std::vector<double>& x) {
        return x[0] * x[0] + 16;
    };

    J[1][0] = [](const std::vector<double>& x) {
        return 2 * x[0] - 4;
    };

    J[1][1] = [](const std::vector<double>& x) {
        return 2 * x[1] - 4;
    };

    Matrix<std::function<double(const std::vector<double>&)>> PHI_D(2, 2);
    PHI_D[1][0] = [](const std::vector<double>& x) {
        return -128*x[0]/pow(x[0] * x[0] + 16, 2);
    };

    PHI_D[1][1] = [](const std::vector<double>& x) {
        return 0;
    };

    PHI_D[0][0] = [](const std::vector<double>& x) {
        return 0;
    };

    PHI_D[0][1] = [](const std::vector<double>& x) {
        return (x[1] - 2) / sqrt(16 - pow(x[1] - 2, 2));
    };

    cout << "\nIteration method:\n";

    printVector(iterationMethodSystem(PHI, PHI_D, {-1, 3}, {-2, 1}, {1, 3.5}, 0.0001));

    cout << "\nNewton method:\n";

    printVector(newtonMethodLU(F, J,{-1, 3}, 0.001));
    return 0;
}