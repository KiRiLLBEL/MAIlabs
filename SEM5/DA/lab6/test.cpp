#include <iostream>
#include <gmp.h>
#include <chrono>

int main() {
    mpz_t a, b;
    char op;
    mpz_inits(a, b, NULL);

    auto start = std::chrono::high_resolution_clock::now();

    while(true) {
        if (gmp_scanf("%Zd", a) <= 0) break;
        if (gmp_scanf("%Zd", b) <= 0) break;

        std::cin >> op;
        if (std::cin.eof()) break;

        switch(op) {
            case '+':
                mpz_add(a, a, b);
                break;
            case '-':
                mpz_sub(a, a, b);
                break;
            case '*':
                mpz_mul(a, a, b);
                break;
            case '/':
                mpz_tdiv_q(a, a, b);
                break;
            case '^': {
                unsigned long int exp = mpz_get_ui(b);
                mpz_pow_ui(a, a, exp);
                break;
            }
            case '=':
                mpz_cmp(a, b);
                break;
            case '<':
                mpz_cmp(a, b);
                break;
            case '>':
                mpz_cmp(a, b);
                break;
            default:
                break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << duration.count() << std::endl;

    mpz_clears(a, b, NULL);

    return 0;
}
