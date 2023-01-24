#include <stdio.h>
#include <math.h>

int main(void) {
    double Epsillon = 1.0;
    double Taylor;
    int n;
    int k = 1000;
    double a = -0.2f;
    double b = 0.3f;
    double x;
    int Counter;

    while (1.0 + (Epsillon / 2.0) > 1.0) {
    Epsillon /= 2.0;
    }

    printf("Машинное эпсилон для типа double в системе VS Code = %e\n", Epsillon);
    printf("Число n:\n");
    scanf("%d", &n);
    printf("Число k:\n");
    scanf("%d", &k);
    printf("Таблица значений ряда Тейлора и стандартной функции для f(x) = (((-1)^(n + 1) * 2^n - 1)*x^n)/n\n");
    printf("________________________________________________________________________________________\n");
    printf("|   x   |           Тейлор             |             f(x)             | число итераций |\n");
    printf("________________________________________________________________________________________\n");

    x = -0.2f;
    for (int i = 0; i <= n; i++) {
        double function;
        function = log(1 + x - 2 * pow(x,2));
        Taylor = 0;
        Counter = 1;
        double Buffer = 1;
        while (fabs(Buffer) > Epsillon * k && Counter < 100) {
            Buffer = ((pow(-1, Counter + 1) * pow(2, Counter) - 1) * pow(x, Counter)) / Counter;
            Taylor += Buffer;
            Counter += 1;
        }
        if (x < 0) {
            if (Taylor < 0) {
                if (Counter >= 10) {
                    printf("| %.2f | %.25f | %.25f |       %d       |\n", x, Taylor, function, Counter);
                } else {
                   printf("| %.2f | %.25f | %.25f |        %d       |\n", x, Taylor, function, Counter); 
                }     
            } else {
                if (Counter >= 10) {
                    if (function > 0) {
                        printf("| %.2f |  %.25f |  %.25f |       %d       |\n", x, Taylor, function, Counter);
                    } else {
                        printf("| %.2f |  %.25f | %.25f |       %d       |\n", x, Taylor, function, Counter);
                    }
                } else {
                    if (function > 0) {
                        printf("| %.2f |  %.25f |  %.25f |        %d       |\n", x, Taylor, function, Counter);
                    } else {
                        printf("| %.2f |  %.25f | %.25f |        %d       |\n", x, Taylor, function, Counter);
                    }
                }
            }
        } else {
            if (Taylor < 0) {
                if (Counter >= 10) {
                    if (function > 0) {
                            printf("|  %.2f | %.25f |  %.25f |       %d       |\n", x, Taylor, function, Counter);
                        } else {
                            printf("|  %.2f | %.25f | %.25f |       %d       |\n", x, Taylor, function, Counter);
                        }
                } else {
                    if (function > 0) {
                            printf("|  %.2f | %.25f |  %.25f |        %d       |\n", x, Taylor, function, Counter);
                        } else {
                            printf("|  %.2f | %.25f | %.25f |        %d       |\n", x, Taylor, function, Counter);
                        }
                }
            } else {
                if (Counter >= 10) {
                    if (function > 0) {
                            printf("|  %.2f |  %.25f |  %.25f |       %d       |\n", x, Taylor, function, Counter);
                        } else {
                            printf("|  %.2f |  %.25f | %.25f |       %d       |\n", x, Taylor, function, Counter);
                        }
                } else {
                    if (function > 0) {
                            printf("|  %.2f |  %.25f |  %.25f |        %d       |\n", x, Taylor, function, Counter);
                        } else {
                            printf("|  %.2f |  %.25f | %.25f |        %d       |\n", x, Taylor, function, Counter);
                        }
                }
            }
        }
        printf("________________________________________________________________________________________\n");
        x += (b - a) / n;
    }
    return 0;
}