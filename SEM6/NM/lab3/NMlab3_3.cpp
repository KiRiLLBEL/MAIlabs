#include <iostream>
#include <vector>
#define WITHOUT_NUMPY
#include "matplotlibcpp.h"
#include "Polynoms.h"

using namespace std;
namespace plt = matplotlibcpp;

int main() {
    vector<double> X = {0, 1.7, 3.4, 5.1, 6.8, 8.5};
    vector<double> Y = {0.0, 1.3038, 1.8439, 2.2583, 2.6077, 2.9155};

    auto coefficients1 = leastSquares(X, Y, 1);
    auto coefficients2 = leastSquares(X, Y, 2);

    vector<double> Y_fit1, Y_fit2, X_cont;
    for (double x = *min_element(X.begin(), X.end()); x <= *max_element(X.begin(), X.end()); x += 0.1) {
        X_cont.push_back(x);
        Y_fit1.push_back(coefficients1[0][0] + coefficients1[1][0] * x);
        Y_fit2.push_back(coefficients2[0][0] + coefficients2[1][0] * x + coefficients2[2][0] * x * x);
    }

    plt::figure_size(1200, 780);
    plt::scatter(X, Y, 50);
    plt::plot(X_cont, Y_fit1, "--g");
    plt::plot(X_cont, Y_fit2, "--r");
    plt::title("Least Squares Polynomial Fit");
    plt::xlabel("X");
    plt::ylabel("Y");
    std::map<std::string, std::string> legend_keywords;
    legend_keywords["title"] = "Legend";
    plt::legend(legend_keywords);
    plt::show();

    return 0;
}