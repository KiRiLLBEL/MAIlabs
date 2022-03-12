#include "iostream"
struct Cls {
    Cls(char c, double d, int i) : c(c), d(d), i(i) {

    };
    private:
    char c;
    double d;
    int i;
};

char &get_c(Cls &cls) {
    return *(char*)(&cls);
}
double &get_d(Cls &cls) {
    return *(double*)((char*)(&cls) + 8);
}

int &get_i(Cls &cls) {
    return *(int*)((char*)(&cls + 16));
}

int main() {
    char c = 'a';
    double d = 3.14;
    int i = 0;
    Cls a(c, d, i);
    std::cout << get_c(a) <<"\n";

    return 0;
}
