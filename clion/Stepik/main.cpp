#include "iostream"
#include "algorithm"
class IntArray {
public:
    explicit IntArray(size_t size) : size_(size), data(new int[size]){
    for (int i = 0; i != size_; ++i)
        data[i] = 0;
    }
    IntArray(const IntArray & a) : size_(a.size_), data(new int[size_]){
        for (int i = 0; i != size_; ++i) {
            data[i] = a.data[i];
        }
    }
    void swap(IntArray & other) {
        std::swap(size_, other.size_);
        std::swap(data, other.data);
    }
    IntArray & operator=(const IntArray & other) {
        if (&other != this)
            IntArray(other).swap(*this);
        return *this;
    }
    ~IntArray() {
        delete [] data;
    }
    size_t size () const {
        return size_;
    }
    int & get (size_t i) {
        return data[i];
    }
    int get (size_t i) const {
        return data[i];
    }
    void resize (size_t nsize) {
        IntArray t(nsize);
        size_t n = size_ > nsize ? nsize : size_;
        for (int i = 0; i != n; ++i) {
            t.data[i] = data[i];
        }
        swap(t);
    }
private:
    size_t size_;
    int * data;
};
int main () {
    int n = 0;
    std::cin >> n;
    IntArray arr(n);
    for (int i = 0; i < )
    return 0;
}