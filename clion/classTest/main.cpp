#include <iostream>

class Test {
public:
    Test(int a, char b) : a_(a), b_(b){

    }
    int get_a() {
        return a_;
    }
    ~Test() {
        std::cout << "end of class" <<"\n";
    }
private:
    int a_;
    char b_;
};
int main() {
    Test t(10, 'c');
    std::cout << t.get_a() <<"\n";
    return 0;
}
